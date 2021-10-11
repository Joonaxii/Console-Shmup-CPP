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

    while (true)
    {
        engine->update();

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

        rend->render(time->getTime());
    }
    delete engine;
}