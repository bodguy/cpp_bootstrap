#ifndef WAV_FILE_H
#define WAV_FILE_H

#include <al.h>
#include <alc.h>
#include <cstdint>
#include <vector>
#include <string>

struct wav_file_data {
  wav_file_data() = default;
  ~wav_file_data();

  ALenum format;
  void* buffer_data;
  ALsizei size;
  ALsizei sample_rate;
  ALsizei time_in_sec;
};

ALenum to_al_format(int16_t channels, int16_t samples);
size_t get_index_of_string(std::vector<uint8_t>& raw_data, const std::string& search);
int16_t convert_endian_two_bytes(std::vector<uint8_t>& raw_data, int start_index, bool endianess);
int32_t convert_endian_four_bytes(std::vector<uint8_t>& raw_data, int start_index, bool endianess);
bool read_wav(std::vector<uint8_t>& raw_data, wav_file_data* buffer);
void check_al_error();
void list_audio_devices(const ALchar* devices);

#endif
