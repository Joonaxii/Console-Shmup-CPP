#include "Engine.h"
#include "../Includes.h"

Engine::Engine() {

    _time = new Time();
    _rendering = new Rendering();
    _inputs = new Inputs();
    _resourceManager = new ResourceManager();

    for (size_t i = 0; i < 5; i++)
    {
        const std::string str = _rendering->indexToLayerName(i);
        OutputDebugStringA(str.c_str());
    }
}

Engine::~Engine() { }

Engine* Engine::getInstance() {

    if (_instance == nullptr) {

        _instance = new Engine();
    }
    return  _instance;
}

void Engine::initialize() {

    _rendering->setup();
}

void Engine::update() {

    _inputs->update();
    _time->tick();
    _rendering->render();
}

Time* Engine::getTime() {
    return _time;
}

Rendering* Engine::getRendering() {
    return _rendering;
}

Inputs* Engine::getInputs() {
    return _inputs;
}

ResourceManager* Engine::getResourceManager() {
    return _resourceManager;
}
