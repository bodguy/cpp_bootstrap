#include <iostream>
#include <cstring>
#include <AL/al.h>
#include <AL/alc.h>

void list_audio_devices(const ALchar* devices) {
  const ALchar* device = devices, *next = devices + 1;
  size_t len = 0;

  std::cout << "Devices list:" << std::endl;
  std::cout << "=============" << std::endl;
  while (device && *device != '\0' && next && *next != '\0') {
    std::cout << device << std::endl;
    len = strlen(device);
    device += (len + 1);
    next += (len + 2);
  }
  std::cout << "=============" << std::endl;
}

int main() {
    ALCdevice* device = alcOpenDevice(NULL);
    ALboolean enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    if (enumeration == AL_FALSE) {
        std::cout << "Enumeration extension not support!" << std::endl;
        exit(EXIT_FAILURE);
    }
    list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

    return 0;
}
