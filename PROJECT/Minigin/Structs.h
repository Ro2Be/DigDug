#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <vector>
//FVector, IVector, SVector
//FPoint, IPoint, SPoint
//Frame, Animation, TileSet

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
	struct FPolarVector
	{
		float radius;
		float angle;
		FPolarVector(float radius, float angle);
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
		short x;
		short y;
		SVector();
		SVector(short x, short y);
		SVector(FPolarVector fPolarVector);
		float SqrRadius() const;
		float Radius() const;
		float Angle() const;
		SVector operator+(const SVector& v) const;
		SVector& operator+=(const SVector& v);
		SVector operator-(const SVector& v) const;
		SVector& operator-=(const SVector& v);
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
		short x;
		short y;
		//SPoint(int x, int y) : x{ x }, y{ y } {}
		SPoint operator+(const SVector& v) const;
		SPoint& operator+=(const SVector& v);
		SPoint operator-(const SVector& v) const;
		SPoint& operator-=(const SVector& v);
		SVector operator-(const SPoint& p) const;
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
	struct TileSet
	{
		TileSet(const SPoint& start, const SVector& tileSize, char tileAmount, char columns = 1) :
			sources{ tileAmount }
		{
			for (char tileIndex{}; tileIndex < tileAmount; ++tileIndex)
			{
				sources[tileIndex].x = start.x + (tileIndex % columns) * tileSize.x;
				sources[tileIndex].y = start.y + (tileIndex / columns) * tileSize.y;
				sources[tileIndex].w = tileSize.x;
				sources[tileIndex].h = tileSize.y;
			}
		}
		std::vector<SDL_Rect> sources;
	};
}