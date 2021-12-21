#pragma once
#include <string>
#include "../Math/Vector2Int.h"

struct TextRegion {

    char* data;
    unsigned int depth;

    Vector2Int position;
    Vector2Int size;

    TextRegion(const unsigned int depth, const Vector2Int& pos, const Vector2Int& size) :
        depth(depth), position(pos), size(size), data(0) {
    }

    ~TextRegion() {
        delete[] data;
    }

    void setText(const std::string str, const Vector2Int textPos, const char bgChar = '\0') {
        data = new char[size.x * size.y];

        int p = 0;
        for (size_t y = 0; y < size.y; y++) {
            for (size_t x = 0; x < size.x; x++) {
                int i = y * size.x + x;
                this->data[i] = (y >= textPos.x && x >= textPos.x && p < str.length()) ? str[p++] : bgChar;
            }
        }
    }

    void writeToBuffer(char* buffer, unsigned int* depthBuffer, const int bufferW) {
        int p = 0;
        for (size_t y = 0; y < size.y; y++) {
            const int yPos = position.y + y;
            for (size_t x = 0; x < size.x; x++) {
                const auto c = data[p++];

                if (c == '\0') { continue; }

                const int xPos = position.x + x;
                int i = yPos * bufferW + xPos;
                if (depthBuffer[i] > depth) { continue; }

                depthBuffer[i] = depth;
                buffer[i] = c;
            }
        }
    }
};

