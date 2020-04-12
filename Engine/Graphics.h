/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once
#include "ChiliWin.h"
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"
#include "Vec2.h"
#include <vector>
#include <iterator>
#include <algorithm>

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel( int x,int y,Color c );
	void DrawLine(Vec2 v1, Vec2 v2, Color c)
	{
		float m = 0;
		if (v1.x != v2.x)
		{
			m = (v2.y - v1.y) / (v2.x - v1.x);
		}
		if (v1.x != v2.x && std::abs(m) <= 1.f)
		{
			if (v1.x > v2.x) std::swap(v1, v2);
			for (int x = (int)v1.x; x <= (int)v2.x; ++x)
			{
				const float y = v1.y + m * (x-v1.x);
				if (x > 0 && x < Graphics::ScreenWidth && y>0 && y < Graphics::ScreenHeight)
				{
					PutPixel(x, (int)y, c);
				}
			}
		}
		else
		{
			if (v1.y > v2.y) std::swap(v1, v2);
			float w = (v2.x - v1.x) / (v2.y - v1.y);
			for (int y = (int)v1.y; y <= (int)v2.y; ++y)
			{
				const float x = v1.x + w * (y - v1.y);
				if (x > 0 && x < Graphics::ScreenWidth && y>0 && y < Graphics::ScreenHeight)
				{
					PutPixel((int)x, y, c);
				}
			}
		}
	}
	static bool OnScreen(const Vec2& p) 
	{
		return (p.x > 0 && p.x < Graphics::ScreenWidth&& p.y>0 && p.y < Graphics::ScreenHeight);
	}
	void DrawClosedPolyline(std::vector<Vec2>& vert, Color c)
	{
		for (auto it = vert.begin(); it != std::prev(vert.end()); it++)
		{
			DrawLine(*it, *std::next(it), c);
		}
		DrawLine(vert.back(), vert.front(), c);
	}
	void DrawClosedPolyline(const std::vector<Vec2>& verts, Vec2 translation, float scale_X, float scale_Y, float angle, Color c) 
	{
		const float sin_ = sin(angle); const float cos_ = cos(angle);
		const auto Transform = [&](Vec2 v) -> Vec2 
		{ 
			//v.Rotate(angle);
			const float x_new = cos_ * v.x - sin_ * v.y;
			v.y = sin_ * v.x + cos_ * v.y;
			v.x = x_new;

			v.x *= scale_X;
			v.y *= scale_Y;
			v += translation;
			return v;
		};

		if (std::any_of(verts.begin(), verts.end(), [&Transform](const Vec2& v) { return Graphics::OnScreen( Transform(v) );}))
		{
			const Vec2 front = Transform(verts.front());
			Vec2 cur = front;
			for (auto it = verts.begin(); it != std::prev(verts.end()); ++it)
			{
				const Vec2 next = Transform(*std::next(it));
				DrawLine(cur, next, c);
				cur = next;
			}
			DrawLine(front,cur,c);
		}
	}
	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;
public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
};