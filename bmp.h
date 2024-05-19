#ifndef POTATO_RAYCASTING_BMP_H
#define POTATO_RAYCASTING_BMP_H

#include "MiniFB.h"
#include "MiniFB_enums.h"
#include "camera.h"
#include "player.h"
#include "screen.h"
#include <cstdint>
#include <vector>

namespace potato_raycasting {

void readBMPAndConvert(const std::string &filename,
                       std::vector<uint32_t> &out_pixels, int &width,
                       int &height);
} // namespace potato_raycasting

#endif
