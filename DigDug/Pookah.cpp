#include "pch.h"
#include "Pookah.h"
using namespace std;

Pookah::Pookah(shared_ptr<e::Scene> spScene, const string& name, const e::SPoint& position, const e::SVector& size)
{
	spScene->AddGameObject(name, {
		new e::TransformComponent(position.x, position.y, size.x, size.y),
		new e::TextureComponent(),
		new e::AnimationComponent("Pookah") });
}