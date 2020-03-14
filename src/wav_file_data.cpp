#include "wav_file_data.h"
#include <string>
#include <iostream>

wav_file_data::~wav_file_data() {
  delete[] static_cast<uint8_t*>(buffer_data);
}

ALenum to_al_format(int16_t channels, int16_t samples) {
  bool stereo = (channels > 1);

  switch (samples) {
    case 16:
      if (stereo)
        return AL_FORMAT_STEREO16;
      else
        return AL_FORMAT_MONO16;
    case 8:
      if (stereo)
        return AL_FORMAT_STEREO8;
      else
        return AL_FORMAT_MONO8;
    default:
      return -1;
  }
}

size_t get_index_of_string(std::vector<uint8_t>& raw_data, const std::string& search) {
  size_t index = -1;
  size_t len = search.length();

  for (size_t i = 0; i < raw_data.size() - len; i++) {
    std::string check(raw_data.begin() + i, raw_data.begin() + i + len);
    if (check == search) {
      index = i;
      break;
    }
  }

  return index;
}

int16_t convert_endian_two_bytes(std::vector<uint8_t>& raw_data, int start_index, bool endianess) {
  // endianess : TRUE -> Little
  //             FALSE -> Big
  if (endianess) {
    return (raw_data[start_index + 1] << 8) | raw_data[start_index];
  }

  return (raw_data[start_index] << 8) | raw_data[start_index + 1];
}

int32_t convert_endian_four_bytes(std::vector<uint8_t>& raw_data, int start_index, bool endianess) {
  // endianess : TRUE -> Little
  //             FALSE -> Big
  if (endianess) {
    return (raw_data[start_index + 3] << 24) | (raw_data[start_index + 2] << 16) | (raw_data[start_index + 1] << 8) | raw_data[start_index];
  }

  return (raw_data[start_index] << 24) | (raw_data[start_index + 1] << 16) | (raw_data[start_index + 2] << 8) | raw_data[start_index + 3];
}

bool read_wav(std::vector<uint8_t>& raw_data, wav_file_data* buffer) {
  // chunkId ("RIFF")
  std::string header_chunk_id(raw_data.begin(), raw_data.begin() + 4); // big
  //  int32_t chunk_size = convert_endian_four_bytes(raw_data, 4, true);
  // format ("WAVE")
  std::string format(raw_data.begin() + 8, raw_data.begin() + 12); // big
  int index_of_fmt = (int)get_index_of_string(raw_data, "fmt");
  int index_of_data = (int)get_index_of_string(raw_data, "data");

  if (index_of_fmt == -1 || index_of_data == -1 || header_chunk_id != "RIFF" || format != "WAVE") {
    std::cout << "invalid WAV file" << std::endl;
    return false;
  }

  // "FMT" chunk
  //  std::string sub_chunk_1_id(raw_data.begin() + index_of_fmt, raw_data.begin() + index_of_fmt + 4); // big
  //  int32_t sub_chunk_1_size = convert_endian_four_bytes(raw_data, index_of_fmt + 4, true);
  int16_t audio_format = convert_endian_two_bytes(raw_data, index_of_fmt + 8, true);
  int16_t num_channels = convert_endian_two_bytes(raw_data, index_of_fmt + 10, true);
  uint32_t sample_rate = (uint32_t)convert_endian_four_bytes(raw_data, index_of_fmt + 12, true);
  int32_t byte_rate = convert_endian_four_bytes(raw_data, index_of_fmt + 16, true);
  int16_t block_align = convert_endian_two_bytes(raw_data, index_of_fmt + 20, true);
  int16_t bits_per_sample = convert_endian_two_bytes(raw_data, index_of_fmt + 22, true);
  int num_bytes_per_sample = bits_per_sample / 8;

  if (audio_format != 1) {
    std::cout << "invalid audio format" << std::endl;
    return false;
  }

  if (num_channels < 1 || num_channels > 2) {
    std::cout << "invalid num channels" << std::endl;
    return false;
  }

  if ((byte_rate != (num_channels * sample_rate * bits_per_sample) / 8) || (block_align != (num_channels * num_bytes_per_sample))) {
    std::cout << "invalid bytes rate OR block align" << std::endl;
    return false;
  }

  if (bits_per_sample != 8 && bits_per_sample != 16 && bits_per_sample != 24) {
    std::cout << "invalid bits per sample" << std::endl;
    return false;
  }

  // DATA chunk
  // std::string sub_chunk_2_id(rawData.begin() + index_of_data, rawData.begin() + index_of_data + 4);
  int32_t sub_chunk_2_size = convert_endian_four_bytes(raw_data, index_of_data + 4, true);
  int sample_start_index = index_of_data + 8;

  uint8_t* data = new uint8_t [sub_chunk_2_size];
  memcpy(data, raw_data.data() + sample_start_index, sub_chunk_2_size);

  buffer->format = to_al_format(num_channels, bits_per_sample);
  buffer->buffer_data = static_cast<void*>(data);
  buffer->size = sub_chunk_2_size;
  buffer->sample_rate = sample_rate;
  buffer->time_in_sec = buffer->size / (buffer->sample_rate * num_channels * num_bytes_per_sample);

  return true;
}

void check_al_error() {
  ALCenum error = alGetError();
  if (error != AL_NO_ERROR) {
    std::cout << "Something wrong"  << std::endl;
    exit(EXIT_FAILURE);
  }
}

void list_audio_devices(const ALchar* devices) {
  const ALchar* device = devices, *next = devices + 1;
  size_t len = 0;

  std::cout << "Devices list:" << std::endl;
  while (device && *device != '\0' && next && *next != '\0') {
    std::cout << "- " << device << std::endl;
    len = strlen(device);
    device += (len + 1);
    next += (len + 2);
  }
}