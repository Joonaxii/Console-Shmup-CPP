#pragma once
#include "Includes.h"

class ResourceManager;
class Engine
{

public:
    Engine();
    ~Engine();

    void initialize();
    void update();

    Time* getTime();
    Rendering* getRendering();
    Inputs* getInputs();
    ResourceManager* getResourceManager();

    static Engine* getInstance();

private:

    static Engine* _instance;

    Time* _time;
    Rendering* _rendering;
    Inputs* _inputs;

    ResourceManager* _resourceManager;

};

