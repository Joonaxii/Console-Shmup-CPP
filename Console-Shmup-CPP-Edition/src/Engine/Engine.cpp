#include "Engine.h"
#include "../Includes.h"

bool Engine::_isFocused = true;

Engine::Engine() : _mainThread(nullptr), _renderThread(nullptr), _onUpdate(0) {

    _collisionSystem = new CollisionSystem();
    _rendering = new Rendering();
    _rendering->setup();

    _inputs = new Inputs();
    _resourceManager = new ResourceManager();

    _window = GetConsoleWindow();
}

Engine::~Engine() { }

Engine* Engine::getInstance() {

    if (_instance == nullptr) {

        _instance = new Engine();
    }
    return  _instance;
}

void Engine::triggerOnUpdate() {
    for (size_t i = 0; i < _onUpdate.size(); i++) {
        _onUpdate[i]();
    }
}

void Engine::initialize() {
    _mainThread = new SyncThread("Main", [this](Time* t) { update(); });
    _renderThread = new SyncThread("Render", [this](Time* t) { _rendering->render(); });

    _mainThread->setSyncThread(_renderThread);
}

void Engine::update() {

    _isFocused = _window == GetForegroundWindow();
    if (!_isFocused) { return; }

    _inputs->update();
    triggerOnUpdate();
    //_rendering->render();
}

const bool Engine::getFocus() {
    return _isFocused;
}

const Time* Engine::getTime(const EngineThreadType tType = EngineThreadType::Main) const{
    switch (tType) {
    default: return _mainThread->getTime();
    case EngineThreadType::Render:
        return _renderThread->getTime();
    }
}

const SyncThread* Engine::getThread(const EngineThreadType tType) const {
    switch (tType) {
    default: return _mainThread;
    case EngineThreadType::Render:
        return _renderThread;
    }
}

CollisionSystem* Engine::getCollisionSystem() {
    return _collisionSystem;
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

void Engine::addListener(std::function<void()> callback) {
    _onUpdate.push_back(callback);
}

void Engine::start() {
    _mainThread->start();
}

void Engine::stop() {
    _mainThread->stop();
}
