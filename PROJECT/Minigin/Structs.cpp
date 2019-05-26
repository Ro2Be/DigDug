#include "MiniginPCH.h"
#include "Structs.h"

namespace e
{
	using namespace std;

	//FVECTOR
	//bool Vectorf::IsSet() const
	//{
	//	return !std::isnan(x) && !std::isnan(y);
	//}
	FVector FVector::operator+(const FVector& v) const
	{
		return { x + v.x, y + v.y };
	}
	FVector& FVector::operator+=(const FVector& v)
	{	
		x += v.x;
		y += v.y;
		return *this;		
	}
	FVector FVector::operator*(const float& f) const
	{
		return { x * f, y * f };
	}
	FVector& FVector::operator*=(const float& f)
	{
		x *= f;
		y *= f;
		return *this;
	}
	FPolarVector::FPolarVector(float radius, float angle) :
		radius{ radius },
		angle{ angle }
	{
	}
	//IVECTOR
	IVector IVector::operator+(const IVector& v) const
	{
		return { x + v.x, y + v.y };
	}
	IVector& IVector::operator+=(const IVector& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	IVector IVector::operator*(const int& i) const
	{
		return { x * i, y * i };
	}
	IVector& IVector::operator*=(const int& i)
	{
		x *= i;
		y *= i;
		return *this;
	}
	SVector::SVector() :
		x{ 0 },
		y{ 0 }
	{
	}
	SVector::SVector(short x, short y) : 
		x{ x }, 
		y{ y }
	{
	}
	SVector::SVector(FPolarVector fPolarVector) :
		x{ short(fPolarVector.radius * cos(fPolarVector.angle)) },
		y{ short(fPolarVector.radius * sin(fPolarVector.angle)) }
	{
	}
	float SVector::SqrRadius() const
	{
		const float fx{ float(x) };
		const float fy{ float(y) };
		return fx * fx + fy * fy;
	}
	float SVector::Radius() const
	{
		return sqrt(SqrRadius());
	}
	float SVector::Angle() const
	{
		return atan2(float(y), float(x));
	}
	//SVECTOR
	SVector SVector::operator+(const SVector& v) const
	{
		return { x + v.x, y + v.y };
	}
	SVector& SVector::operator+=(const SVector& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	SVector SVector::operator-(const SVector& v) const
	{
		return { x - v.x, y - v.y };
	}
	SVector& SVector::operator-=(const SVector& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	SVector SVector::operator*(const short& i) const
	{
		return { x * i, y * i };
	}
	SVector& SVector::operator*=(const short& i)
	{
		x *= i;
		y *= i;
		return *this;
	}

	//FPOINT
	//bool Pointf::IsSet() const
	//{
	//	return !std::isnan(x) && !std::isnan(y);
	//}
	FPoint FPoint::operator+(const FVector& v) const
	{
		return { x + v.x, y + v.y };
	}
	FPoint& FPoint::operator+=(const FVector& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	//IPOINT
	IPoint IPoint::operator+(const IVector& v) const
	{
		return {x + v.x, y + v.y };
	}
	IPoint& IPoint::operator+=(const IVector& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	//SPOINT
	SPoint SPoint::operator+(const SVector& v) const
	{
		return { x + v.x, y + v.y };
	}
	SPoint& SPoint::operator+=(const SVector& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	SPoint SPoint::operator-(const SVector& v) const
	{
		return { x - v.x, y - v.y };
	}
	SPoint& SPoint::operator-=(const SVector& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	SVector SPoint::operator-(const SPoint& p) const
	{
		return { x - p.x, y - p.y };
	}
}