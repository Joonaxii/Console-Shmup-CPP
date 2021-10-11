#pragma once
#include <vector>
#include <unordered_map>
#include "windows.h"

class Inputs
{
public:

    static const int MOVE_LEFT = VK_LEFT;
    static const int MOVE_RIGHT = VK_RIGHT;
    static const int MOVE_UP = VK_UP;
    static const int MOVE_DOWN = VK_DOWN;

    static const int ENTER = VK_RETURN;
    static const int ESC = VK_ESCAPE;

    static const int KEY_Z = 0x5A;
    static const int KEY_X = 0x58;
    static const int KEY_C = 0x43;

    Inputs();
    ~Inputs();

    void update();

    const bool isKeyDown(const int key) const;
    const bool isKeyUp(const int key) const;
    const bool isKeyHeld(const int key) const;

private:

    struct KeyState {

        bool down;
        bool held;
        bool up;
        bool pressed;

    public:
        KeyState() : down(false), held(false), up(false), pressed(false) {}

        void copyFrom(const KeyState& other) {

            down = other.down;
            held = other.held;
            up = other.up;
            pressed = other.pressed;
        }
    };

    const int _indexToKey[9];

    std::unordered_map<int, int> _keyLut;
    KeyState _keys[9];
    KeyState _previousKeys[9];

};

