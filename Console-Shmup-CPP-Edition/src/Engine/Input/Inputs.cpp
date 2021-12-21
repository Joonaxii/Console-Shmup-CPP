#include "Inputs.h"
#include <string>
#include "windows.h"
#include "../Engine.h"

Inputs::Inputs() : _keys{ nullptr }, _previousKeys{ nullptr }, _keyLut(), _indexToKey { DEBUG_MODE, DEBUG_MODE_MISC, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, ENTER, ESC, KEY_Z, KEY_X, KEY_C }
{
    for (size_t i = 0; i < INPUTS; i++)
    {
        _keys[i] = new KeyState();
        _previousKeys[i] = new KeyState();

        _keyLut.insert(std::pair<int, int>(_indexToKey[i], i));
    }
}

Inputs::~Inputs() {
}

void Inputs::update()
{
    if (!Engine::getFocus()) { return; }
    for (size_t i = 0; i < 9; i++)
    {
        auto key = _keys[i];
        auto prev = _previousKeys[i];
        prev->copyFrom(key);

        bool curState = GetKeyState(_indexToKey[i]) & 0x8000;

        key->down = !prev->pressed && curState;
        key->held = prev->pressed && curState;
        key->up = prev->pressed && !curState;

        key->pressed = key->down || key->held;
    }
}

const bool Inputs::isKeyDown(const int key) const {
    if (!hasKey(key)) { return false; }

    const int index = _keyLut.at(key);
    auto v = _keys[index];
    return v->down;
}

const bool Inputs::isKeyUp(const int key) const {
    if (!hasKey(key)) { return false; }

    const int index = _keyLut.at(key);
    auto v = _keys[index];
    return v->up;
}

const bool Inputs::isKeyHeld(const int key) const {
    if (!hasKey(key)) { return false; }

    const int index = _keyLut.at(key);
    auto v = _keys[index]; 
    return v->held;
}

const bool Inputs::hasKey(const int key) const {

    auto a = _keyLut.find(key);
    return a != _keyLut.end();
}

