// (AI-assisted) Upstream 0.10.5 libretro uses these declarations even with the GBA core disabled.
#pragma once
#if __has_include(<mgba/gba/interface.h>)
#include <mgba/gba/interface.h>
#endif
#ifndef SIZE_CART_FLASH1M
#define SIZE_CART_FLASH1M 0x20000
#endif
