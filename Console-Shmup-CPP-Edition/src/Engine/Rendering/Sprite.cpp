#include "../../Includes.h"
#include "windows.h"

Sprite::Sprite() : pivot(0, 0), resolution(0, 0) {
    pixels = new char[0];
}

Sprite::Sprite(const char* pix, Vector2Int reso, Vector2 pivot) :
    resolution(reso.x, reso.y),
    pivot(-pivot.x * reso.x,
          -pivot.y * reso.y) {

    const int resoP = reso.x * reso.y;
    pixels = new char[resoP] {0};
    memcpy(pixels, pix, resoP);
}

Sprite::~Sprite() {
    delete[] pixels;
}

void Sprite::draw(Transform* tr, char* buffer, unsigned int* depthBuffer, const unsigned int depth, const int bufferW, const int bufferH, const int yOffset, const bool flipX, const bool flipY) {

    const auto scal = tr->getScale(true);
    const auto posT = tr->getPosition(true);
    const auto mat = tr->getMatrix(true);

    const int w = (int)(resolution.x * scal.x);
    const int h = (int)(resolution.y * scal.y);

    const int oW = resolution.x - 1;
    const int oH = resolution.y - 1;

    const float lW = w < 2 ? 1 : w - 1.0f;
    const float lH = h < 2 ? 1 : h - 1.0f;

    const Vector2 piv(mat.scaleVector(pivot));

    const int offX = bufferW / 2;
    const int offY = bufferH / 2;

    for (signed int y = 0; y < h; y++)
    {
        int ogY = (int)roundf(oH * (y / lH));
        for (signed int x = 0; x < w; x++)
        {
            int ogX = (int)roundf(oW * (x / lW));

            Vector2 pos((x + piv.x), (y + piv.y));
            pos.set(mat.rotatePointRev(pos));
            pos.x += offX + posT.x;
            pos.y += offY - posT.y;

            int xX = (int)pos.x;
            int yY = (int)pos.y;

            if (xX < 0 || xX >= bufferW || yY < 0 || yY >= bufferH) { continue; }
            yY += yOffset;

            const int iO = ogY * resolution.x + ogX;
            const int bI = yY * bufferW + xX;

            if (depthBuffer[bI] > depth) { continue; }

            const char c = pixels[iO];
            if (c == '½') { continue; }

            buffer[bI] = c;
            depthBuffer[bI] = depth;
        }
    }
}
