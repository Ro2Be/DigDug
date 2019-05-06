#include "pch.h"
#include "../Minigin/Game.h"
#include "../Minigin/Minigin.h"
#include "Pookah.h"

using namespace std;

//main function defined at the bottom of this file
#pragma warning(push)
#pragma warning(disable : 4100)
#pragma warning(disable : 4251) 

class DigDug : public e::Game
{
public:
	DigDug(const Settings& settings) : e::Game(settings) {};
	virtual void Load() const override
	{
		//ADD RESOURCES
		e::ResourceManager& resourceManager{ e::ResourceManager::GetInstance() }; 
		resourceManager.AddAnimation("Pookah",		"DigDug256x256(RippedByMisterMan).png", 200.f, { {  0,  0, 16, 16 }, { 16,  0, 16, 16 } });
		resourceManager.AddAnimation("Fygar",		"DigDug256x256(RippedByMisterMan).png", 200.f, { {  0, 24, 16, 16 }, { 16, 24, 16, 16 } });
		resourceManager.AddAnimation("TaizoHori",	"DigDug256x256(RippedByMisterMan).png", 200.f, { {  0, 48, 16, 16 }, { 16, 48, 16, 16 } });
		resourceManager.AddTexture("Rock",			"DigDug256x256(RippedByMisterMan).png", { { 0, 80, 16, 16 } });

		//ADD GAMEOBJECTS
		shared_ptr<e::Scene> spScene = e::SceneManager::GetInstance().CreateScene("Demo");
		spScene->AddGameObject("Title", {
			new e::TransformComponent(80, 20, 0, 0),
			new e::TextureComponent(),
			new e::TextComponent("Programming 4 Assignment", "Lingua.otf", 36) });
		spScene->AddGameObject("FPSCounter", {
			new e::TransformComponent(20, 20, 0, 0),
			new e::TextureComponent(),
			new e::TextComponent("", "Lingua.otf", 36, e::colors::yellow),
			new e::FPSComponent() });
		//m_pPookah1 = new Pookah(spScene, "Pookah1", { 0, 0 }, { 64, 64 });
		spScene->AddGameObject("Fygar", {
			new e::TransformComponent(120, 20, 64, 64),
			new e::TextureComponent(),
			new e::AnimationComponent("Fygar") });
		spScene->AddGameObject("TaizoHori", {
			new e::TransformComponent(120, 120, 64, 64),
			new e::TextureComponent(),
			new e::AnimationComponent("TaizoHori") });
		spScene->AddGameObject("Rock", {
			new e::TransformComponent(240, 240, 64, 64),
			new e::TextureComponent("Rock") });
	}
};

int main()
{
#pragma warning( pop )
	e::Game::Settings settings{ "DigDug", { 640, 480 } };
	e::Minigin::Run(DigDug(settings));
	return 0;
}