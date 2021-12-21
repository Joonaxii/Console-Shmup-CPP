#include "Math.h"
#include <sstream>
#include "Includes.h"
#include "Engine/Math/Math.h"
#include "Game/Entities/GenericEntity.h"
#include "Engine/Rendering/Animator.h"
#include "Engine/Components/Transform.h"
#include "Engine/Collision/ColliderData.h"
#include "Game/Entities/Player/Player.h"
#include "Game/Game.h"

Engine* Engine::_instance;

int main()
{
	Engine* engine = Engine::getInstance();
	Game* game = new Game();

	engine->initialize();
	engine->getRendering()->setTitle("~~Joonaxii's Console-Shmup~~");
	engine->getRendering()->clearInfoRegion();

	engine->start();
}
