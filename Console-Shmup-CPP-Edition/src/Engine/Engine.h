#pragma once
#include "EngineThreadType.h"
#include "Core/SyncThread.h"
#include "Collision/CollisionSystem.h"
#include "Input/Inputs.h"
#include "Core/Time.h"
#include "Resources/ResourceManager.h"

class Rendering;
class ResourceManager;
class Engine
{

public:
    Engine();
    ~Engine();

    void initialize();
    void update();

    static const bool getFocus();
    const Time* getTime(const EngineThreadType tType) const;
    const SyncThread* getThread(const EngineThreadType tType) const;

    CollisionSystem* getCollisionSystem();
    Rendering* getRendering();
    Inputs* getInputs();
    ResourceManager* getResourceManager();

    void addListener(std::function<void()> callback);

    void start();
    void stop();

    static Engine* getInstance();

private:

    static Engine* _instance;
    static bool _isFocused;

    HWND _window;

    SyncThread* _mainThread;
    SyncThread* _renderThread;

    Rendering* _rendering;
    Inputs* _inputs;
    CollisionSystem* _collisionSystem;

    ResourceManager* _resourceManager;
    std::vector<std::function<void()>> _onUpdate;

    void triggerOnUpdate();
};

