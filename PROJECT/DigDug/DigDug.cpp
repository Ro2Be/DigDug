#include "pch.h"
#include "../Minigin/Game.h"
#include "GameObject.h"
#include "Components.h"
#include "DigDugComponents.h"

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
		//ADD RESOURCES
		e::ResourceManager& resourceManager{ e::ResourceManager::GetInstance() };
		resourceManager.AddAnimation("FygarDefault",		"DigDug256x256(RippedByMisterMan).png", 200.f, { { 00, 24, 16, 16 }, { 16, 24, 16, 16 } });
		resourceManager.AddAnimation("FygarGhost",			"DigDug256x256(RippedByMisterMan).png", 200.f, { { 80, 24, 16, 16 }, { 96, 24, 16, 16 } });
		resourceManager.AddAnimation("FygarDie",			"DigDug256x256(RippedByMisterMan).png", 200.f, { { 48, 24, 16, 16 }, { 64, 24, 16, 16 } });
		resourceManager.AddAnimation("FygarWeapon",			"DigDug256x256(RippedByMisterMan).png", 200.f, { { 160, 144, 16, 16 }, { 176, 144, 32, 16 }, { 208, 144, 48, 16 }, { 208, 144, 48, 16 }, { 208, 144, 48, 16 } }); //TODO REMOVE LAST TWO FRAMES (JUST A COPY TO STRETCH TIME)
		resourceManager.AddAnimation("PookahDefault",		"DigDug256x256(RippedByMisterMan).png", 200.f, { { 00, 00, 16, 16 }, { 16, 00, 16, 16 } });
		resourceManager.AddAnimation("PookahGhost",			"DigDug256x256(RippedByMisterMan).png", 200.f, { { 80, 00, 16, 16 }, { 96, 00, 16, 16 } });
		resourceManager.AddAnimation("PookahDie",			"DigDug256x256(RippedByMisterMan).png", 200.f, { { 48, 00, 16, 16 }, { 64, 00, 16, 16 } });
		resourceManager.AddAnimation("TaizoHoriDefault",	"DigDug256x256(RippedByMisterMan).png", 200.f, { { 00, 48, 16, 16 }, { 16, 48, 16, 16 } });
		resourceManager.AddAnimation("TaizoHoriDie",		"DigDug256x256(RippedByMisterMan).png", 200.f, { { 48, 48, 16, 16 }, { 64, 48, 16, 16 }, { 80, 48, 16, 16 }, { 96, 48, 16, 16 } });
		resourceManager.AddAnimation("TaizoHoriWeapon",		"DigDug256x256(RippedByMisterMan).png", 200.f, { { 208, 160, 16, 16 }, { 192, 160, 32, 16 }, { 176, 160, 48, 16 }, { 176, 160, 48, 16 }, { 176, 160, 48, 16 } }); //TODO REMOVE LAST TWO FRAMES (JUST A COPY TO STRETCH TIME)
		resourceManager.AddTexture("Rock",					"DigDug256x256(RippedByMisterMan).png", { { 0, 80, 16, 16 } });
		resourceManager.AddTexture("TileMap",				"DigDug256x256(RippedByMisterMan).png");
		resourceManager.AddTexture("HealthDisplay",			"DigDug256x256(RippedByMisterMan).png");

		
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
		unsigned char healthDisplay[1][5]{ { 1, 1, 1, 0, 0 } };

		//ADD GAMEOBJECTS
		shared_ptr<e::Scene> spGameScene = e::SceneManager::GetInstance().CreateScene("Game");
		spGameScene->AddGameObject("BackGround", {
			new e::TransformComponent(50, 0, 1.9f),
			new e::TileMapComponent<32, 28>("TileMap", e::TileSet({ 0, 216 }, { 8, 8 }, 40, 8), tileMap) });
		spGameScene->AddGameObject("HealthDisplay", {
			new e::TransformComponent(480, 100, 1.9f),
			new e::TileMapComponent<1, 5>("HealthDisplay", e::TileSet({ 240, 32 }, { 16, 16 }, 2, 1), healthDisplay ),
			new HealthDisplayComponent() });
		spGameScene->AddGameObject("Title", {
			new e::TransformComponent(60, 10),
			new e::TextureComponent(),
			new e::TextComponent("Programming 4 Assignment", "Emulogic.ttf", 10) });
		spGameScene->AddGameObject("FPSCounter", {
			new e::TransformComponent(420, 10),
			new e::TextureComponent(),
			new e::TextComponent("", "Emulogic.ttf", 15, e::colors::yellow),
			new e::FPSComponent() });
		LoadLevel0(spGameScene, resourceManager);

		//shared_ptr<e::Scene> spMenuScene = e::SceneManager::GetInstance().CreateScene("Menu");
	}

	static void LoadLevel0(const shared_ptr<e::Scene>& spScene, e::ResourceManager& resourceManager)
	{
		//CONSTS
		const short playerSpeed{ 20 };
		//ADD GAMEOBJECTS
		spScene->AddGameObject("Pookah", {
			new e::TransformComponent(220, 40, 1.9f),
			new e::TextureComponent("PookahDefault"),
			new e::AnimatorComponent(),
			new e::ColliderComponent("Enemy"),
			new PookahComponent(),
			new Character::DefaultStateComponent(resourceManager.GetpAnimation("PookahDefault")),
			new Character::GhostStateComponent(resourceManager.GetpAnimation("PookahGhost")),
			new Character::DieStateComponent(resourceManager.GetpAnimation("PookahDie")) });
		spScene->AddGameObject("FygarWeapon", {
			new e::TransformComponent(),
			new e::TextureComponent("FygarWeapon"),
			new e::AnimatorComponent("FygarWeapon"),
			new e::ColliderComponent("Enemy"),
			new WeaponComponent() });
		spScene->AddGameObject("Fygar", {
			new e::TransformComponent(120, 20, 1.9f),
			new e::TextureComponent("FygarDefault"),
			new e::AnimatorComponent(),
			new e::ColliderComponent("Enemy"),
			//new FygarComponent(),
			new Character::DefaultStateComponent(resourceManager.GetpAnimation("FygarDefault")),
			new Character::AttackStateComponent("FygarWeapon"),
			new Character::GhostStateComponent(resourceManager.GetpAnimation("FygarGhost")),
			new Character::DieStateComponent(resourceManager.GetpAnimation("FygarDie")) });
		spScene->AddGameObject("TaizoHoriWeapon", {
			new e::TransformComponent(),
			new e::TextureComponent("TaizoHoriWeapon"),
			new e::AnimatorComponent("TaizoHoriWeapon"),
			new e::ColliderComponent("Friend"),
			new WeaponComponent() });
		spScene->AddGameObject("TaizoHori", {
			new e::TransformComponent(120, 120, 1.9f),
			new e::TextureComponent("TaizoHoriDefault"),
			new e::AnimatorComponent(),
			new e::ColliderComponent("Player"),
			new TaizoHoriComponent(),
			new Character::DefaultStateComponent(resourceManager.GetpAnimation("TaizoHoriDefault")),
			new Character::AttackStateComponent("TaizoHoriWeapon"),
			new Character::DieStateComponent(resourceManager.GetpAnimation("TaizoHoriDie")) });
		spScene->AddGameObject("Rock", {
			new e::TransformComponent(240, 240, 1.9f),
			new e::TextureComponent("Rock"),
			new e::ColliderComponent("Rock") });
		//ADD CONTROLS
		e::InputManager& inputManager{ e::InputManager::GetInstance() };
		inputManager.GetKeyboard().AddCommand(DWORD(e::Keyboard::Key::A), true, spScene->GetGameObject("Fygar")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ -playerSpeed,  0 }));
		inputManager.GetKeyboard().AddCommand(DWORD(e::Keyboard::Key::S), true, spScene->GetGameObject("Fygar")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ 0, playerSpeed }));
		inputManager.GetKeyboard().AddCommand(DWORD(e::Keyboard::Key::D), true, spScene->GetGameObject("Fygar")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ playerSpeed,  0 }));
		inputManager.GetKeyboard().AddCommand(DWORD(e::Keyboard::Key::W), true, spScene->GetGameObject("Fygar")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ 0, -playerSpeed }));
		inputManager.GetKeyboard().AddCommand(DWORD(e::Keyboard::Key::E), true, new Character::AttackCommand(spScene->GetGameObject("Fygar")));
		inputManager.GetController(0).AddCommand(DWORD(e::Controller::Button::LEFT),	true, spScene->GetGameObject("TaizoHori")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ -playerSpeed,  0 }));
		inputManager.GetController(0).AddCommand(DWORD(e::Controller::Button::DOWN),	true, spScene->GetGameObject("TaizoHori")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ 0, playerSpeed }));
		inputManager.GetController(0).AddCommand(DWORD(e::Controller::Button::RIGHT),	true, spScene->GetGameObject("TaizoHori")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ playerSpeed,  0 }));
		inputManager.GetController(0).AddCommand(DWORD(e::Controller::Button::UP),		true, spScene->GetGameObject("TaizoHori")->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ 0, -playerSpeed }));
		inputManager.GetController(0).AddCommand(DWORD(e::Controller::Button::A),		true, new Character::AttackCommand(spScene->GetGameObject("TaizoHori")));
	}
};

int main()
{
	#pragma warning( pop )
	const e::Game::Settings settings{ "DigDug", { 640, 480 }, 60.f };
	const DigDug game{ settings };
	game.Run();
	return 0;
}