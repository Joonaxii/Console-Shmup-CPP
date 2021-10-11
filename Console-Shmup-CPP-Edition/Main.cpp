#include "Includes.h"
#include <sstream>

Engine* Engine::_instance;

int main()
{
    Engine* engine = Engine::getInstance();

    engine->initialize();

    engine->getRendering()->setTitle("~~Joonaxii's Console-Shmup~~");
    engine->getRendering()->clearInfoRegion();

    std::ostringstream ss;

    const auto time = engine->getTime();
    const auto rend = engine->getRendering();

    Sprite* sprite = new Sprite("----|  ||  |----", Vector2Int(4, 4), Vector2(0, 0));

    SpriteRenderer* renderer = new SpriteRenderer();
    renderer->setPosition(Vector2(0, 0));
    renderer->setActive(true);

    Sprite* sprt(nullptr);
    engine->getResourceManager()->tryGetSprite("Player", &sprt);
    renderer->setSprite(sprt);

    Vector2 pos(0, 0);

    auto inputs = engine->getInputs();
    while (true)
    {
        engine->update();

        float delta = time->getDeltaTime();
        Vector2 dir(0, 0);

        dir.x += inputs->isKeyHeld(Inputs::MOVE_RIGHT);
        dir.x -= inputs->isKeyHeld(Inputs::MOVE_LEFT);

        dir.y += inputs->isKeyHeld(Inputs::MOVE_UP);
        dir.y -= inputs->isKeyHeld(Inputs::MOVE_DOWN);

        dir.x *= delta * 42.0f;
        dir.y *= delta * 32.0f;

        pos += dir;
        renderer->setPosition(pos);

        const auto frm = time->getFrames();
        if (frm % 1 == 0) {

            std::ostringstream().swap(ss);
            ss << "Fps: " << time->getFramerate() << "      ";
            rend->addInfoString(0, 0, ss.str().c_str());

            //std::ostringstream().swap(ss);
            //ss << "Time: " << time->getTime() << "       ";
            //rend->addInfoString(0, 1, ss.str().c_str());

            //std::ostringstream().swap(ss);
            //ss << "Delta: " << time->getDeltaTime() << "     ";
            //rend->addInfoString(0, 2, ss.str().c_str());

            //std::ostringstream().swap(ss);
            //ss << "Frames: " << frm << "     ";
            //rend->addInfoString(0, 3, ss.str().c_str());
        }
    }
    delete engine;
}