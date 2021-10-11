#include "Inputs.h"
#include "windows.h"

Inputs::Inputs() : _keys{ KeyState() }, _previousKeys{ KeyState() }, _keyLut(), _indexToKey { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, ENTER, ESC, KEY_Z, KEY_X, KEY_C }
{
    for (size_t i = 0; i < 9; i++)
    {
        _keyLut.insert(std::pair<int, int>(i, _indexToKey[i]));
    }
}

Inputs::~Inputs()
{
}

void Inputs::update()
{
    for (size_t i = 0; i < 9; i++)
    {
        auto key = _keys[i];
        auto prev = _previousKeys[i];
        prev.copyFrom(key);

        bool curState = GetKeyState(_indexToKey[i]) & 0x8000;

        key.down = !prev.pressed && curState;
        key.held = prev.pressed && curState;
        key.up = prev.pressed && !curState;

        key.pressed = key.down || key.held;
    }
}

