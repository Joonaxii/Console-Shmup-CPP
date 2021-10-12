#include "../../Includes.h"
#include "windows.h"

Sprite::Sprite() : pivot(0, 0), resolution(0, 0) {
    pixels = new char[0];
}

Sprite::Sprite(const char* pix, Vector2Int reso, Vector2 pivot) :
    resolution(reso.x, reso.y),
    pivot(pivot.x - (reso.x <= 1 ? 0 : reso.x % 2 == 0 ? reso.x / 2 : (reso.x - 1) / 2),
          pivot.y - (reso.y <= 1 ? 0 : reso.y % 2 == 0 ? reso.y / 2 : (reso.y - 1) / 2)) {

    const int resoP = reso.x * reso.y;
    pixels = new char[resoP] {0};
    memcpy(pixels, pix, resoP);
}

Sprite::~Sprite() {

    delete pixels;
}
