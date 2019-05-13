#include "pch.h"
#include "../Minigin/Game.h"
#include "TaizoHoriComponent.h"
#include "Gameobject.h"

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
		//CONSTS
		const short playerSpeed{ 20 };

		//ADD RESOURCES
		e::ResourceManager& resourceManager{ e::ResourceManager::GetInstance() };
		resourceManager.AddAnimation("Fygar",		"DigDug256x256(RippedByMisterMan).png", 200.f, { { 0, 24, 16, 16 }, { 16, 24, 16, 16 } });
		resourceManager.AddAnimation("TaizoHori",	"DigDug256x256(RippedByMisterMan).png", 200.f, { { 0, 48, 16, 16 }, { 16, 48, 16, 16 } });
		resourceManager.AddTexture("Rock",			"DigDug256x256(RippedByMisterMan).png", { { 0, 80, 16, 16 } });

		//ADD GAMEOBJECTS
		shared_ptr<e::Scene> spScene = e::SceneManager::GetInstance().CreateScene("Demo");
		spScene->AddGameObject("Title", {
			new e::TransformComponent(80, 20),
			new e::TextureComponent(),
			new e::TextComponent("Programming 4 Assignment", "Lingua.otf", 36) });
		spScene->AddGameObject("FPSCounter", {
			new e::TransformComponent(20, 20),
			new e::TextureComponent(),
			new e::TextComponent("", "Lingua.otf", 36, e::colors::yellow),
			new e::FPSComponent() });
		//spScene->AddGameObject("Pookah", {
		//	new e::TransformComponent(20, 20, 3.f),
		//	new e::TextureComponent(),
		//	new e::AnimationComponent("Pookah") });
		spScene->AddGameObject("Fygar", {
			new e::TransformComponent(120, 20, 3.f),
			new e::TextureComponent("TaizoHori"),
			new e::AnimationComponent("Fygar") });
		spScene->AddGameObject("TaizoHori", {
			new e::TransformComponent(120, 120, 3.f),
			new e::TextureComponent("TaizoHori"),
			new e::AnimationComponent("TaizoHori"),
			new TaizoHoriComponent() });		
		spScene->AddGameObject("Rock", {
			new e::TransformComponent(240, 240, 3.f),
			new e::TextureComponent("Rock") });
		spScene->PrintGameObjectNames();

		//ADD CONTROLS
		e::InputManager& inputManager{ e::InputManager::GetInstance() };
		inputManager.GetKeyboard().AddCommand(DWORD(e::Keyboard::Key::A), true, spScene->GetGameObject("TaizoHori")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ -playerSpeed,  0 }));
		inputManager.GetKeyboard().AddCommand(DWORD(e::Keyboard::Key::S), true, spScene->GetGameObject("TaizoHori")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({  0, playerSpeed }));
		inputManager.GetKeyboard().AddCommand(DWORD(e::Keyboard::Key::D), true, spScene->GetGameObject("TaizoHori")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({  playerSpeed,  0 }));
		inputManager.GetKeyboard().AddCommand(DWORD(e::Keyboard::Key::W), true, spScene->GetGameObject("TaizoHori")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({  0, -playerSpeed }));
		inputManager.GetController(0).AddCommand(DWORD(e::Controller::Button::LEFT ), true, spScene->GetGameObject("TaizoHori")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ -playerSpeed,  0 }));
		inputManager.GetController(0).AddCommand(DWORD(e::Controller::Button::DOWN ), true, spScene->GetGameObject("TaizoHori")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ 0, playerSpeed }));
		inputManager.GetController(0).AddCommand(DWORD(e::Controller::Button::RIGHT), true, spScene->GetGameObject("TaizoHori")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ playerSpeed,  0 }));
		inputManager.GetController(0).AddCommand(DWORD(e::Controller::Button::UP   ), true, spScene->GetGameObject("TaizoHori")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ 0, -playerSpeed }));
	}
};

int main()
{
	#pragma warning( pop )
	const e::Game::Settings settings{ "DigDug", { 640, 480 }, 60.f };
	DigDug game{ settings };
	game.Run();
	return 0;
}