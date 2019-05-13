#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
//FVector, IVector, SVector
//FPoint, IPoint, SPoint
//Frame, Animation

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
		Frame() = default;
		Frame(int x, int y, int w, int h) :
			source{ x, y, w, h }
		{
			center.x = source.w / 2;
			center.y = source.h / 2;
		}
		Frame(SDL_Rect source) : 
			source{ source }
		{
			center.x = source.w / 2; 
			center.y = source.h / 2;
		}
		Frame(SDL_Rect source, SDL_Point center) :
			source{ source },
			center{ center }
		{
		}
		SDL_Rect  source;
		SDL_Point center;
	};
	struct Animation
	{
		float msPerFrame;
		std::vector<Frame> frames;
	};
}