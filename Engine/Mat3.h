#pragma once
#include "Vec3.h"

template <typename T>
class _Mat3
{
public:
	_Vec2<T> operator*(const _Vec2<T>& rhs) const
	{
		return _Vec2<T>(*this * _Vec3<T>(rhs));
	}
	
	_Vec3<T> operator*(const _Vec3<T>& rhs) const
	{
		_Vec3<T> vec_out;
		vec_out.x = cells[0][0] * rhs.x + cells[0][1] * rhs.y + cells[0][2] * rhs.w;
		vec_out.y = cells[1][0] * rhs.x + cells[1][1] * rhs.y + cells[1][2] * rhs.w;
		vec_out.w = cells[2][0] * rhs.x + cells[2][1] * rhs.y + cells[2][2] * rhs.w;
		// BELOW JUST FOR FUN
		// NO TYPE CASTING ALLOWED (UB)
		//for (int row = 0; row < 2; row++)
		//{
		//	T sum = 0;
		//	for (int col = 0; col < 2; col++)
		//	{
		//		sum += cells[row][col] * ((T*)(&v))[col];
		//	}
		//	((T*)(&w))[row] = sum;
		//}
		return vec_out;
	}
	_Mat3 operator*(const _Mat3& M) const
	{
		_Mat3 A_out;
		for (int row_L = 0; row_L < 3; row_L++)
		{
			for (int col_R = 0; col_R < 3; col_R++)
			{
				A_out.cells[row_L][col_R] = (T)0;
				for (int j = 0; j < 3; j++)
				{
					A_out.cells[row_L][col_R] += cells[row_L][j] * M.cells[j][col_R];
				}
			}
		}
		return A_out;
	}
	static _Mat3<T> Scale(T factor)
	{
		return _Mat3<T>{
			factor,	(T)0,	(T)0,
			(T)0,	factor,	(T)0,
			(T)0,	(T)0,	(T)1
		};
	}
	static _Mat3<T> ScaleXY(T factorX, T factorY)
	{
		return _Mat3<T>{
			factorX,(T)0,	(T)0,
			(T)0,	factorY,(T)0,
			(T)0,	(T)0,	(T)1
		};
	}
	static _Mat3<T> Identity() 
	{
		return Scale( (T)1 );
	}
	static _Mat3<T> FlipYAxis() 
	{
		return _Mat3<T>{
			(T)1,	(T)0,	(T)0,
			(T)0,	(T)-1,	(T)0,
			(T)0,	(T)0,	(T)1
		};
	}
	static _Mat3<T> Rotate(T phi) 
	{
		const T cos_ = cos(phi);
		const T sin_ = sin(phi);
		return _Mat3<T>{
			cos_,	-sin_,	(T)0,
			sin_,	 cos_,	(T)0,
			T(0),	(T)0,	(T)1
		};
	}
	static _Mat3<T> Translate(T dx, T dy)
	{
		return _Mat3<T>{
			(T)1,	(T)0,	dx,
			(T)0,	(T)1,	dy,
			(T)0,	(T)0,	(T)1
		};
	}
public:
	// [row][col]
	T cells[3][3];
};

//typedef _Mat3<float> Mat3;
using Mat3 = _Mat3<float>;
using Mad3 = _Mat3<double>;