#include "Math.h"
#include <sstream>
#include "Includes.h"
#include "Engine/Math/Math.h"
#include "Game/Entities/Entity.h"
#include "Engine/Rendering/Animator.h"
#include "Engine/Components/Transform.h"
#include "Engine/Collision/ColliderData.h"

Engine* Engine::_instance;

int main()
{
    Engine* engine = Engine::getInstance();

    engine->initialize();

    engine->getRendering()->setTitle("~~Joonaxii's Console-Shmup~~");
    engine->getRendering()->clearInfoRegion();

    const auto time = engine->getTime();
    const auto rend = engine->getRendering();

    Transform* plrTransform = new Transform();
    Transform* plrRootTransform = new Transform();

    SpriteRenderer* renderer = new SpriteRenderer();
    renderer->setTransform(plrTransform);
    renderer->setActive(true);

    Animator* animator = new Animator(renderer);
    Animation* anim(nullptr);

    engine->getResourceManager()->tryGetAnimation("Boss Warning", &anim);
    animator->play(anim);

    Sprite* sprt(nullptr);
    engine->getResourceManager()->tryGetSprite("Player", &sprt);
    //renderer->setSprite(sprt);
    renderer->setLayer("Foreground");

    Vector2 pos(0, 0);

    Sprite* sprtB(nullptr);
    engine->getResourceManager()->tryGetSprite("Boss_Sword", &sprtB);

    const int swordCount = 16;
    Transform* swords[swordCount];
    SpriteRenderer* swordRenderers[swordCount];
    float swordAngles[swordCount];

    plrTransform->addChild(plrRootTransform);

    const float radPerI = (360.0f / swordCount);
    for (size_t i = 0; i < swordCount; i++)
    {
        float ang = radPerI * i;
        float rads = ang * DEG_2_RAD;

        auto tr = swords[i] = new Transform();
  
        plrRootTransform->addChild(tr);
        tr->setPosition(Vector2(cosf(rads) * 28.0f, sinf(rads) * 28.0f), false);
        tr->setRotation(ang, false);

        auto rend = swordRenderers[i] = new SpriteRenderer();
        rend->setTransform(tr);

        rend->setSprite(sprtB);
        rend->setLayer("Foreground");
        rend->setActive(true);

        swordAngles[i] = ang;
    }

    auto inputs = engine->getInputs();
    while (true)
    {
        engine->update();

        if (inputs->isKeyDown(Inputs::DEBUG_MODE)) {
            SpriteRenderer::DRAW_BOUNDS = !SpriteRenderer::DRAW_BOUNDS;
        }

        float delta = time->getDeltaTime();

        animator->update(delta);

        Vector2 dir(0, 0);

        dir.x += inputs->isKeyHeld(Inputs::MOVE_RIGHT);
        dir.x -= inputs->isKeyHeld(Inputs::MOVE_LEFT);

        dir.y += inputs->isKeyHeld(Inputs::MOVE_UP);
        dir.y -= inputs->isKeyHeld(Inputs::MOVE_DOWN);

        dir.x *= delta * 42.0f;
        dir.y *= delta * 42.0f;

        pos += dir;

        const float t = time->getTime() * 25.0f;
        const float tS = lerp(1, 1, (sinf(t * DEG_2_RAD * 2.0f) + 1.0f) * 0.5f);

        plrTransform->setPosition(pos, true);
        plrTransform->setScale(Vector2(tS, tS), false);
        plrRootTransform->setRotation(t * -2.0f, false);

        for (size_t i = 0; i < swordCount; i++)
        {
            auto tr = swords[i];
            const float val = swordAngles[i];
            tr->setRotation(val + t, false);

            swordRenderers[i]->setSortingOrder(max(tr->getPosition(true).y * 10, 0));
        }
        renderer->setSortingOrder(max( plrTransform->getPosition(true).y * 10, 0));

        const auto frm = time->getFrames();
        if (frm % 1 == 0) {
            rend->addInfoString(0, 0, ("Fps: " + std::to_string(time->getFramerate()) + "      ").c_str());
            rend->addInfoString(0, 1, ("Time: " + std::to_string(time->getTime()) + "      ").c_str());
            rend->addInfoString(0, 2, ("Delta: " + std::to_string(time->getDeltaTime()) + "     ").c_str());
            rend->addInfoString(0, 3, ("Frames: " + std::to_string(frm) + "     ").c_str());
        }
    }
}