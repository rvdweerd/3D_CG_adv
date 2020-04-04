    /****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
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

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "CoordinateTransformer.h"
#include "Entity.h"
#include "Camera.h"
#include "FrameTimer.h"
#include <random>
#include "StarBro.h"
#include "MouseCameraController.h"
#include "Plank.h"
#include "Ball.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */

    // World Gen parameters
    static constexpr float worldWidth = 10000.f;
    static constexpr float worldHeight = 6000.f;
    static constexpr int nStars = 0;
    static constexpr float meanStarRadius = 160.f;
    static constexpr float devStarRadius = 90.f;
    static constexpr float minStarRadius = 40.f;
    static constexpr float maxStarRadius = 300.f;
    static constexpr float meanInnerRatio = 0.4f;
    static constexpr float devInnerRatio = 0.25f;
    static constexpr float minInnerRatio = 0.15f;
    static constexpr float maxInnerRatio = 0.8f;
    static constexpr float meanFlares = 6.5f;
    static constexpr float devFlares = 2.0f;
    static constexpr int minFlares = 3;
    static constexpr int maxFlares = 10;

    // Game objects
    FrameTimer ft;
    CoordinateTransformer ct;
    std::mt19937 rng;
    std::uniform_real_distribution<float> velDistr;
   //std::vector<Entity> stars;
    Camera cam;
    MouseCameraController mouseCamCtrlr;
    std::vector<StarBro> stars;
    Plank plank;
    std::vector<Ball> balls;
    float time_elapsed = 0.f;
    /********************************/
};