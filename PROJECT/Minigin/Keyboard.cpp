#include "MiniginPCH.h"
#include "Game.h"
#include "Keyboard.h"
#include "SDL.h"

namespace e
{	
	using namespace std;
	Keyboard::Keyboard() :
		InputDevice(),
		m_SDLEvent{}
	{
	}
	void Keyboard::HandleEvents()
	{
		while (SDL_PollEvent(&m_SDLEvent))
		{
			switch (m_SDLEvent.type)
			{
			case SDL_QUIT :
				Game::Quit();
				break;
			case SDL_KEYDOWN :
				{
					if (m_SDLEvent.key.repeat == 0)
					{
						auto it{ m_pCommandsByInputIndexOnDown.find(m_SDLEvent.key.keysym.sym) };
						if (it != m_pCommandsByInputIndexOnDown.end()) (*it).second->Execute();
					}
				}
				break;
			case SDL_KEYUP :
				{
					auto it{ m_pCommandsByInputIndexOnUp.find(m_SDLEvent.key.keysym.sym) };
					if (it != m_pCommandsByInputIndexOnUp.end()) (*it).second->Execute();
				}
				break;
			default : 
				break;
			}
		};
	}
	bool Keyboard::Get0DState(const InputIndex& key) const
	{
		return GetAsyncKeyState(key) & 0x0001;
	}
	SVector Keyboard::Get2DState(const InputIndex&) const
	{
		throw std::runtime_error("Engine doesn't support mouse input!"); //TODO: IMPLEMENT MOUSE
	}
}