#include "../../Includes.h"
#include "windows.h"

Sprite::Sprite() : _pivot(0, 0), _resolution(0, 0), _bounds() {
    _pixels = new char[0];
}

Sprite::Sprite(const char* pix, Vector2Int reso, Vector2 pivot) :
    _resolution(reso.x, reso.y),
    _pivot(-pivot.x * reso.x,
           -pivot.y * reso.y) {

    const Vector2 extents(reso.x * 0.5f, reso.y * 0.5f);
    const Vector2 diff = extents + _pivot;

    _bounds.setMinMax(-extents.x + diff.x, -extents.y + diff.y,
                       extents.x + diff.x,  extents.y + diff.y);

    const int resoP = reso.x * reso.y;
    _pixels = new char[resoP] {0};
    memcpy(_pixels, pix, resoP);
}

Sprite::~Sprite() {
    delete[] _pixels;
}

const Rect Sprite::getBounds() const {
    return _bounds;
}

void Sprite::draw(Transform* tr, char* buffer, unsigned int* depthBuffer, const unsigned int depth, const int bufferW, const int bufferH, const int yOffset, const bool flipX, const bool flipY) {

    const auto scal = tr->getScale(true);
    const auto posT = tr->getPosition(true);
    const auto mat = tr->getMatrix(true);

    const int w = (int)(_resolution.x * scal.x);
    const int h = (int)(_resolution.y * scal.y);

    const int oW = _resolution.x - 1;
    const int oH = _resolution.y - 1;

    const float lW = w < 2 ? 1 : w - 1.0f;
    const float lH = h < 2 ? 1 : h - 1.0f;

    const Vector2 piv(mat.scaleVector(_pivot));

    const int offX = bufferW / 2;
    const int offY = bufferH / 2;

    const float xWorldOff = offX + posT.x;
    const float yWorldOff = offY + posT.y;
    Vector2 pos(0, 0);
    for (signed int y = 0; y < h; y++)
    {
        int ogY = (int)roundf(oH * (y / lH));

        pos.y = (y + piv.y);
        for (signed int x = 0; x < w; x++)
        {
            int ogX = (int)roundf(oW * (x / lW));

            pos.x = (x + piv.x);
            Vector2 point(mat.rotatePointRev(pos));
            int xX = (int)(point.x + xWorldOff);
            int yY = bufferH - 1 - (int)(point.y + yWorldOff);

            if (xX < 0 || xX >= bufferW || yY < 0 || yY >= bufferH) { continue; }
            yY += yOffset;

            const int iO = ogY * _resolution.x + ogX;
            const int bI = yY * bufferW + xX;

            if (depthBuffer[bI] > depth) { continue; }

            const char c = _pixels[iO];
            if (c == '\0') { continue; }

            buffer[bI] = c;
            depthBuffer[bI] = depth;
        }
    }
}

void Sprite::draw(const Vector2& pos, char* buffer, unsigned int* depthBuffer, const unsigned int depth, const int bufferW, const int bufferH, const int yOffset, const bool flipX, const bool flipY) {

    const int offX = bufferW / 2;
    const int offY = bufferH / 2;

    const Vector2Int off((int)round(pos.x + _pivot.x + offX), (int)round(-pos.y + _pivot.y + offY));
    for (size_t y = 0; y < _resolution.y; y++)
    {
        int yY = y + off.y;
        if (yY < 0 || yY >= bufferH) { continue; }
        yY += yOffset;

        for (size_t x = 0; x < _resolution.x; x++)
        {
            int xX = x + off.x;
            if (xX < 0 || xX >= bufferW) { continue; }

            int iB = yY * bufferW + xX;
            if (depthBuffer[iB] > depth) { continue; }

            int iC = y * _resolution.x + x;

            const char c = _pixels[iC];
            if (c == '\0') { continue; }

            buffer[iB] = c;
            depthBuffer[iB] = depth;
        }
    }
}
