#include "Includes.h"
#include "Math.h"
#include "Engine/Collision/ColliderData.h"
#include "Game/Entities/Entity.h"
#include <sstream>
#include "../Transform.h"
#include "Engine/Math/Math.h"

Engine* Engine::_instance;

int main()
{
    Engine* engine = Engine::getInstance();

    engine->initialize();

    engine->getRendering()->setTitle("~~Joonaxii's Console-Shmup~~");
    engine->getRendering()->clearInfoRegion();

    std::ostringstream ss;

    std::string str("Size of ColliderData is '" + std::to_string(sizeof(ColliderData)) + "'");
    OutputDebugStringA(str.c_str());

    const auto time = engine->getTime();
    const auto rend = engine->getRendering();

    Transform* plrTransform = new Transform();
    Transform* plrRootTransform = new Transform();
    Transform* nmyTransform1 = new Transform();
    Transform* nmyTransform2 = new Transform();
    Transform* nmyTransform3 = new Transform();
    Transform* nmyTransform4 = new Transform();

    SpriteRenderer* renderer = new SpriteRenderer();
    renderer->setTransform(plrTransform);
    renderer->setActive(true);

    Sprite* sprt(nullptr);
    engine->getResourceManager()->tryGetSprite("Player", &sprt);
    renderer->setSprite(sprt);
    renderer->setLayer("Foreground");

    Vector2 pos(0, 0);

    SpriteRenderer* rendererBoss = new SpriteRenderer();
    SpriteRenderer* rendererBoss2 = new SpriteRenderer();
    SpriteRenderer* rendererBoss3 = new SpriteRenderer();
    SpriteRenderer* rendererBoss4 = new SpriteRenderer();
    rendererBoss->setTransform(nmyTransform1);
    rendererBoss->setActive(true);

    rendererBoss2->setTransform(nmyTransform2);
    rendererBoss2->setActive(true);

    rendererBoss3->setTransform(nmyTransform3);
    rendererBoss3->setActive(true);

    rendererBoss4->setTransform(nmyTransform4);
    rendererBoss4->setActive(true);

    Sprite* sprtB(nullptr);
    engine->getResourceManager()->tryGetSprite("Enemy_1", &sprtB);
    rendererBoss->setSprite(sprtB);
    rendererBoss->setLayer("Foreground");

    rendererBoss2->setSprite(sprtB);
    rendererBoss2->setLayer("Foreground");

    rendererBoss3->setSprite(sprtB);
    rendererBoss3->setLayer("Foreground");

    rendererBoss4->setSprite(sprtB);
    rendererBoss4->setLayer("Foreground");

    nmyTransform1->setPosition(Vector2(24.0f, 0), false);
    nmyTransform2->setPosition(Vector2(-24.0f, 0), false);
    nmyTransform3->setPosition(Vector2(0, 24), false);
    nmyTransform4->setPosition(Vector2(0, -24), false);

    nmyTransform2->setRotation(180, false);
    nmyTransform3->setRotation(90, false);
    nmyTransform4->setRotation(-90, false);

    plrTransform->addChild(plrRootTransform);

    plrRootTransform->addChild(nmyTransform1);
    plrRootTransform->addChild(nmyTransform2);
    plrRootTransform->addChild(nmyTransform3);
    plrRootTransform->addChild(nmyTransform4);

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

        const float t = time->getTime() * 25.0f;
        const float tS = lerp(0.5f, 2.0f, (sinf(t * DEG_2_RAD * 2.0f) + 1.0f) * 0.5f);

        plrTransform->setPosition(pos, true);
        plrTransform->setScale(Vector2(tS, tS), false);
        plrRootTransform->setRotation(t, false);

        //renderer->setPosition(plrTransform->getPosition(true));
        //rendererBoss->setPosition(nmyTransform->getPosition(true));

        renderer->setSortingOrder(     max( plrTransform->getPosition(true).y * 10, 0));
        rendererBoss->setSortingOrder( max(nmyTransform1->getPosition(true).y * 10, 0));
        rendererBoss2->setSortingOrder(max(nmyTransform2->getPosition(true).y * 10, 0));
        rendererBoss3->setSortingOrder(max(nmyTransform3->getPosition(true).y * 10, 0));
        rendererBoss4->setSortingOrder(max(nmyTransform4->getPosition(true).y * 10, 0));

        const auto frm = time->getFrames();
        if (frm % 1 == 0) {

            std::ostringstream().swap(ss);
            ss << "Fps: " << time->getFramerate() << "      ";
            rend->addInfoString(0, 0, ss.str().c_str());

            std::ostringstream().swap(ss);
            ss << "Time: " << time->getTime() << "       ";
            rend->addInfoString(0, 1, ss.str().c_str());

            std::ostringstream().swap(ss);
            ss << "Delta: " << time->getDeltaTime() << "     ";
            rend->addInfoString(0, 2, ss.str().c_str());

            std::ostringstream().swap(ss);
            ss << "Frames: " << frm << "     ";
            rend->addInfoString(0, 3, ss.str().c_str());
        }
    }
}