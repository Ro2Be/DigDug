#pragma once
#include <SDL.h>
//FVector, IVector, SVector
//FPoint, IPoint, SPoint
//Frame, Texture, Animation

namespace e
{
	struct FVector
	{
		float x; // = std::nanf(nullptr);
		float y; // = std::nanf(nullptr);
		//FVector(float x, float y) : x{ x }, y{ y } {}
		//bool IsSet() const;
		FVector operator+(const FVector& v) const;
		FVector& operator+=(const FVector& v);
		FVector operator*(const float& f) const;
		FVector& operator*=(const float& f);
	};
	struct IVector
	{
		int x;
		int y;
		//IVector(int x, int y) : x{ x }, y{ y } {}
		IVector operator+(const IVector& v) const;
		IVector& operator+=(const IVector& v);
		IVector operator*(const int& i) const;
		IVector& operator*=(const int& i);
	};
	struct SVector
	{
		short int x;
		short int y;
		//SVector(int x, int y) : x{ x }, y{ y } {}
		SVector operator+(const SVector& v) const;
		SVector& operator+=(const SVector& v);
		SVector operator*(const short& i) const;
		SVector& operator*=(const short& i);
	};
	struct FPoint
	{
		float x; // = std::nanf(nullptr);
		float y; // = std::nanf(nullptr);
		//FPoint(float x, float y) : x{ x }, y{ y } {}
		//bool IsSet() const;
		FPoint operator+(const FVector& v) const;
		FPoint& operator+=(const FVector& v);
	};
	struct IPoint
	{
		int x;
		int y;
		//IPoint(int x, int y) : x{ x }, y{ y } {}
		IPoint operator+(const IVector& v) const;
		IPoint& operator+=(const IVector& v);
	};
	struct SPoint
	{
		short int x;
		short int y;
		//SPoint(int x, int y) : x{ x }, y{ y } {}
		SPoint operator+(const SVector& v) const;
		SPoint& operator+=(const SVector& v);
	};
	struct Frame
	{
		SDL_Point center;
		SDL_Rect source;
		Frame(int x, int y, int w, int h) :
			source{ x, y, w, h },
			center{ w / 2, h / 2 }
		{}
		Frame(const SDL_Rect& source):
			source{ source },
			center{ source.w / 2, source.h / 2 }
		{}
		Frame(const SDL_Rect& source, const SDL_Point& center) :
			source{ source },
			center{ center }
		{}
	};
	struct Texture
	{
		virtual void RenderCopy(SDL_Renderer* pRenderer, const SDL_Rect& destination, SDL_RendererFlip rendererFlip = SDL_RendererFlip::SDL_FLIP_NONE) = 0;
	};
	struct SimpleTexture final : public Texture
	{
		SDL_Texture* pSDLTexture;
		SDL_Rect source;
		virtual void RenderCopy(SDL_Renderer* pRenderer, const SDL_Rect& destination, SDL_RendererFlip) override
		{
			SDL_RenderCopy(pRenderer, pSDLTexture, &source, &destination);
		}
	};
	struct ExtraTexture final : public Texture
	{
		SDL_Texture* pSDLTexture;
		SDL_Rect source;
		SDL_Point center;
		ExtraTexture():
			Texture(),
			pSDLTexture{},
			source{},
			center{}
		{}
		ExtraTexture(SDL_Texture* pSDLTexture, const SDL_Rect& source, const SDL_Point& center):
			Texture(),
			pSDLTexture{ std::move(pSDLTexture) },
			source{ std::move(source) },
			center{ std::move(center) }
		{}
		ExtraTexture(SDL_Texture* pSDLTexture, const Frame& frame) :
			pSDLTexture{ std::move(pSDLTexture) },
			source{ std::move(frame.source) },
			center{ std::move(frame.center) }
		{}
		virtual void RenderCopy(SDL_Renderer* pRenderer, const SDL_Rect& destination, SDL_RendererFlip rendererFlip = SDL_RendererFlip::SDL_FLIP_NONE) override
		{
			SDL_RenderCopyEx(pRenderer, pSDLTexture, &source, &destination, NULL, &center, rendererFlip);
		}
	};
	struct Animation
	{
		float msPerFrame;
		std::vector<ExtraTexture> frames;
	};
}