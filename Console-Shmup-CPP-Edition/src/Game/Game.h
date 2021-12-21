#pragma once
#include "../Engine/Engine.h"
#include "Entities/Player/Player.h"

class Transform;
class GenericEntity;
class Game
{
public:
    Game();
    ~Game();

private:
    const static int SWORD_COUNT;
    const static int CONFIG_COUNT;
    const static float _orientationConfigs[];
    const static float _bladeConfigs[];
    const static float _bladeSpeeds[];
    const static float _plrRotations[];

    const float _configDuration = 4.0f;
    const float _configTransitionDuration = 1.25f;

    Engine* _engine;
    Inputs* _inputs;
    Rendering* _rendering;

    Player* _player;
    Transform* _plrRootTransform;

    GenericEntity** _swords;
    float* _swordAngles;

    float _t;
    float _transitonSpeed;

    Transform* _camera;

    void update();
};

