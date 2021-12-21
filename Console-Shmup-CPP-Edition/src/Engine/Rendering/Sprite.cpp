#include "../../Includes.h"
#include "windows.h"

Sprite::Sprite() : _pivot(nullptr), _offsets(nullptr), _resolution(0, 0), _bounds() {
    _pixels = new char* [0];
}

Sprite::Sprite(const char* pix, const Vector2Int& reso, const Vector2& pivot, const char flip) :
    _resolution(reso.x, reso.y),
    _resMin(reso.x - 1, reso.y - 1) {

    _pivot = new Vector2[4]{
        Vector2(-pivot.x * reso.x + 0.5f, -pivot.y * reso.y + 0.5f),
        Vector2(-(1.0f - pivot.x) * reso.x + 0.5f, -pivot.y * reso.y + 0.5f),
        Vector2(-pivot.x * reso.x + 0.5f, -(1.0f - pivot.y) * reso.y + 0.5f),
        Vector2(-(1.0f - pivot.x) * reso.x + 0.5f, -(1.0f - pivot.y) * reso.y + 0.5f),
    };

    const Vector2 extents(reso.x * 0.5f, reso.y * 0.5f);
    const Vector2 diff = extents + _pivot[0];

    _bounds.setMinMax(-extents.x + diff.x, -extents.y + diff.y,
        extents.x + diff.x, extents.y + diff.y);

    _offsets = new Vector2[4]{
        Vector2(0, 0),
        _pivot[1] - _pivot[0],
        _pivot[2] - _pivot[0],
        _pivot[3] - _pivot[0],
    };

    const int resoP = reso.x * reso.y;
    _pixels = new char* [4]
    {
        new char[resoP] {0},
        nullptr,
        nullptr,
        nullptr,
    };

    memcpy(_pixels[0], pix, resoP);
    switch (flip) {
    case 0:
        for (size_t i = 1; i < 3; i++) {
            _pixels[i] = _pixels[0];
        }
        break;
    case 1:
        _pixels[1] = getFlipSprite(true, false);
        _pixels[2] = _pixels[0];
        _pixels[3] = _pixels[1];
        break;
    case 2:
        _pixels[1] = _pixels[0];
        _pixels[2] = getFlipSprite(false, true);
        _pixels[3] = _pixels[2];
        break;
    case 3:
        _pixels[1] = getFlipSprite(true, false);
        _pixels[2] = getFlipSprite(false, true);
        _pixels[3] = getFlipSprite(true, true);
        break;
    }
}

Sprite::~Sprite() {
    delete[] _pixels;
    delete[] _pivot;
    delete[] _offsets;
}

const Rect Sprite::getBounds(const bool flipX, const bool flipY) const {
    Rect rect(_bounds);
    const auto c = rect.getCenter() + _offsets[flipX + (flipY << 1)];
    rect.set(c, rect.getSize());
    return rect;
}

void Sprite::draw(Transform* tr, char* buffer, unsigned int* depthBuffer, const unsigned int depth, const int bufferW, const int bufferH, const int yOffset, const bool flipX, const bool flipY) {
    const char flipInd = flipX + (flipY << 1);
    const auto scal = tr->getScale(true);
    const auto posT = tr->getPosition(true);
    const auto mat = tr->getMatrix(true);

    const int w = (int)roundf(_resolution.x * scal.x);
    const int h = (int)roundf(_resolution.y * scal.y);

    const int hOne = h - 1;

    const Vector2 piv(mat.scaleVector(_pivot[flipInd]));

    const int offX = bufferW / 2;
    const int offY = bufferH / 2;
    const int bufH = bufferH - 1;

    const Vector2 camP(Rendering::MAIN_CAMERA->getPosition(true));

    const float xWorldOff = offX + posT.x - camP.x;
    const float yWorldOff = offY + posT.y - camP.y;

    const auto pix = _pixels[flipInd];

    const Vector2 resLen(w < 2 ? 1.0f : w - 1.0f, h < 2 ? 1.0f : h - 1.0f);

    Vector2 pos(0, 0);
    for (signed int y = 0; y < h; y++)
    {
        const int ogY = (int)roundf(_resMin.y * (float)(y / (float)resLen.y));

        pos.y = (hOne - y + piv.y);
        for (signed int x = 0; x < w; x++)
        {
            const int ogX = (int)roundf(_resMin.x * (x / resLen.x));

            pos.x = (x + piv.x);
            const Vector2 point(mat.rotatePointRev(pos));
            const int xX = (int)roundf(point.x + xWorldOff);
            int yY = bufH - (int)roundf(point.y + yWorldOff);

            if (xX < 0 || xX >= bufferW || yY < 0 || yY >= bufferH) { continue; }
            yY += yOffset;

            const int iO = ogY * _resolution.x + ogX;
            const int bI = yY * bufferW + xX;

            if (depthBuffer[bI] > depth) { continue; }

            const char c = pix[iO];
            if (c == '\0') { continue; }

            buffer[bI] = c;
            depthBuffer[bI] = depth;
        }
    }
}
void Sprite::draw(const Vector2& pos, char* buffer, unsigned int* depthBuffer, const unsigned int depth, const int bufferW, const int bufferH, const int yOffset, const bool flipX, const bool flipY) {
    const char flipInd = flipX + (flipY << 1);
    const int offX = bufferW / 2;
    const int offY = bufferH / 2;

    const Vector2 camP(Rendering::MAIN_CAMERA->getPosition(true));

    const Vector2Int off((int)round(pos.x + _pivot[flipInd].x + offX - camP.x),
        (int)round(-pos.y + _pivot[flipInd].y + offY + camP.y));

    const auto pix = _pixels[flipInd];
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

            const char c = pix[iC];
            if (c == '\0') { continue; }

            buffer[iB] = c;
            depthBuffer[iB] = depth;
        }
    }
}

char* Sprite::getFlipSprite(const bool flipX, const bool flipY) const {
    char* pix = new char[_resolution.x * _resolution.y];

    for (size_t y = 0; y < _resolution.y; y++) {
        const int yY = flipY ? _resolution.y - 1 - y : y;
        for (size_t x = 0; x < _resolution.x; x++) {
            const int xX = flipX ? _resolution.x - 1 - x : x;

            int i = y * _resolution.x + x;
            int iN = yY * _resolution.x + xX;

            pix[iN] = flipChar(_pixels[0][i], flipX, flipY);
        }
    }
    return pix;
}

const char Sprite::flipChar(const char c, const bool flipX, const bool flipY) const {

    bool flip = flipX | flipY;

    switch (c)
    {
    case 'A': return flipY ? 'V' : c;
    case 'V': return flipY ? 'A' : c;

    case '<': return flipX ? '>' : c;
    case '>': return flipX ? '<' : c;

    case 'E': return flipX ? '3' : c;
    case '3': return flipX ? 'E' : c;

    case '/': return flip ? '\\' : c;
    case '\\': return flip ? '/' : c;

    case '(': return flipX ? ')' : c;
    case ')': return flipX ? '(' : c;

    case '[': return flipX ? ']' : c;
    case ']': return flipX ? '[' : c;

    case '{': return flipX ? '}' : c;
    case '}': return flipX ? '{' : c;
    }

    return c;
}
