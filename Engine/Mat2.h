#pragma once
#include "Vec2.h"

template <typename T>
class _Mat2
{
public:
	_Vec2<T> operator*(const _Vec2<T>& v) const
	{
		_Vec2<T> w;
		w.x = cells[0][0] * v.x + cells[0][1] * v.y;
		w.y = cells[1][0] * v.x + cells[1][1] * v.y;
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
		return w;
	}
	_Mat2 operator*(const _Mat2& M) const
	{
		_Mat2 A_out;
		for (int row_L = 0; row_L < 2; row_L++)
		{
			for (int col_R = 0; col_R < 2; col_R++)
			{
				A_out.cells[row_L][col_R] = (T)0;
				for (int j = 0; j < 2; j++)
				{
					A_out.cells[row_L][col_R] += cells[row_L][j] * M.cells[j][col_R];
				}
			}
		}
		return A_out;
	}
	_Mat2& operator*=(const _Mat2& rhs)
	{
		return *this = (*this)* rhs;
	}
	static _Mat2<T> Scale(T factor)
	{
		return _Mat2<T>{
			factor	, (T)0, 
			(T)0	, factor
		};
	}
	static _Mat2<T> Identity() 
	{
		return Scale( (T)1 );
	}
	static _Mat2<T> FlipYAxis() 
	{
		return _Mat2<T>{
			(T)1	, (T)0,
			(T)0	, (T)-1
		};
	}
	static _Mat2<T> Rotate(T phi) 
	{
		const T cos_ = cos(phi);
		const T sin_ = sin(phi);
		return _Mat2<T>{
			cos_, -sin_,
			sin_,  cos_
		};
	}


public:
	// [row][col]
	T cells[2][2];
};

//typedef _Mat2<float> Mat2;
using Mat2 = _Mat2<float>;
using Mad2 = _Mat2<double>;