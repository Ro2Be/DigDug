#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "Minigin.h"

namespace e
{
	using namespace std;
	void FPSComponent::Update(const GameObject* parent)
	{
		parent->GetpComponent<TextComponent>()->SetText(to_string(int(1000 / Minigin::dt)));
	}
}