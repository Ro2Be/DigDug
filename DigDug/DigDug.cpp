#include "pch.h"
#include "../Minigin/Game.h"
#include "TaizoHoriComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "TileMapComponent.h"
using namespace std;

//main function defined at the bottom of this file
#pragma warning(push)
#pragma warning(disable : 4100)
#pragma warning(disable : 4251) 

class DigDug final : public e::Game
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
		resourceManager.AddTexture("TileMap",		"DigDug256x256(RippedByMisterMan).png");
		unsigned char tileMap[32][28]
		{
			{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
			{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
			{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
			{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
			{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
			{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
			{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
			{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
			{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
			{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
			{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
			{ 8, 8, 8, 8, 8, 8, 9,10,10, 9, 8, 9,10,11,12,12,13,12,11,10, 9,10,10, 9, 4, 9,10,11},
			{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
			{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
			{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
			{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
			{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
			{15,15,15,15,15,15,15,15,15,15,16,18,18,19,20,21,21,21,22,22,21,20,19,19,18,18,18,19},
			{23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23},
			{23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23},
			{23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23},
			{23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23},
			{23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23},
			{23,23,23,23,24,23,23,23,23,23,23,23,23,23,23,23,23,23,24,25,25,25,24,23,23,23,23,23},
			{28,29,29,30,31,31,31,30,29,28,28,27,27,27,28,29,29,30,31,31,31,31,31,31,31,31,31,31},
			{31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31},
			{31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31},
			{31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31},
			{31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31},
			{31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31},
			{31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31},
			{31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31}
		};

		//ADD GAMEOBJECTS
		shared_ptr<e::Scene> spScene = e::SceneManager::GetInstance().CreateScene("Demo");
		spScene->AddGameObject("BackGround", {
			new e::TransformComponent(50, 0, 1.9f),
			new e::TileMapComponent<32, 28>("TileMap", e::TileSet({ 0, 216 }, { 8, 8}, 40, 8), tileMap) });
		spScene->AddGameObject("Title", {
			new e::TransformComponent(60, 10),
			new e::TextureComponent(),
			new e::TextComponent("Programming 4 Assignment", "Emulogic.ttf", 10) });
		spScene->AddGameObject("FPSCounter", {
			new e::TransformComponent(420, 10),
			new e::TextureComponent(),
			new e::TextComponent("", "Emulogic.ttf", 15, e::colors::yellow),
			new e::FPSComponent() });
		//spScene->AddGameObject("Pookah", {
		//	new e::TransformComponent(20, 20, 3.f),
		//	new e::TextureComponent(),
		//	new e::AnimationComponent("Pookah") });
		spScene->AddGameObject("Fygar", {
			new e::TransformComponent(120, 20, 1.9f),
			new e::TextureComponent("TaizoHori"),
			new e::AnimatorComponent("Fygar"),
			new e::ColliderComponent("Enemy") });
		spScene->AddGameObject("TaizoHori", {
			new e::TransformComponent(120, 120, 1.9f),
			new e::TextureComponent("TaizoHori"),
			new e::AnimatorComponent("TaizoHori"),
			new e::ColliderComponent("Player"),
			new TaizoHoriComponent() });		
		spScene->AddGameObject("Rock", {
			new e::TransformComponent(240, 240, 1.9f),
			new e::TextureComponent("Rock"),
			new e::ColliderComponent("Rock") });
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