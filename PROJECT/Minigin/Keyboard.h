#pragma once
#include "Windows.h"
#include "Structs.h"
#include <SDL.h>
#include "InputDevice.h"

namespace e
{
	class Keyboard final : public InputDevice
	{
	public:
		enum class Key : char
		{
			A = 'a', B = 'b', C = 'c', D = 'd', E = 'e', F = 'f', G = 'g', H = 'h', I = 'i', J = 'j', K = 'k', L = 'l', M = 'm', N = 'n', O = 'o',	P = 'p', Q = 'q', R = 'r', S = 's', T = 't', U = 'u', V = 'v', W = 'w',	X = 'x', Y = 'y', Z = 'z'
		};
		Keyboard();
		virtual void HandleEvents() override;
		virtual bool Get0DState(const InputIndex& key) const override;
		virtual SVector Get2DState(const InputIndex&) const override;
	private:
		SDL_Event m_SDLEvent;
	};
};