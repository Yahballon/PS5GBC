// (AI-assisted) GB/GBC cartridge header checks shared by file loader and core adapter.
#pragma once
#include <vector>
#include <cstdint>
namespace gbc {inline bool ValidRom(const std::vector<uint8_t>& rom){if(rom.size()<32768||rom.size()>(32u<<20))return false;uint8_t check=0;for(size_t i=0x134;i<=0x14c;++i)check=uint8_t(check-rom[i]-1);return rom[0x14d]==check&&rom[0x148]<=8&&rom[0x149]<=5;}}
