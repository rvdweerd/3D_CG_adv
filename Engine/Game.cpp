/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include "Homework.h"
#include "Drawable.h"
#include <random>
#include "FrameTimer.h"
#include <algorithm>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
    ct(gfx),
    cam(ct),
    mouseCamCtrlr(wnd.mouse,cam)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> xDist(-worldWidth/2, worldWidth/2);
    std::uniform_real_distribution<float> yDist( - worldHeight / 2, worldHeight / 2);
    std::normal_distribution<float> radDist(meanStarRadius,devStarRadius);
    std::normal_distribution<float> ratDist(meanInnerRatio, devInnerRatio);
    std::normal_distribution<float> flareDist( meanFlares, devFlares);
    const Color colors[] = { Colors::Red,Colors::White,Colors::Blue,Colors::Cyan,Colors::Magenta,Colors::Yellow,Colors::Gray,Colors::Green };
    std::uniform_int_distribution<size_t> colorSampler(0, std::end(colors)-std::begin(colors));
    std::uniform_real_distribution<float> period(0.5f, 2.f);
    std::uniform_real_distribution<float> amp(1.0f, 1.5f);
    std::uniform_real_distribution<float> rot(minRotSpeed, maxRotSpeed);

    while (stars.size() < nStars)
    {
        Vec2 pos = { xDist(rng),yDist(rng) };
        const auto rad = std::clamp(radDist(rng), minStarRadius, maxStarRadius);
        if (std::any_of(stars.begin(), stars.end(), [&](StarBro& sb) { return (pos - sb.GetPos()).LenSq() < pow((rad + sb.GetRadius()), 2); }))
        {
            continue;
        }
        const float& innerRat = std::clamp(ratDist(rng), minInnerRatio, maxInnerRatio);
        const int nF = std::clamp((int)flareDist(rng), minFlares, maxFlares);
        const int& nFlares = std::clamp((int)flareDist(rng),minFlares,maxFlares);
        Color c = colors[colorSampler(rng)];
        stars.emplace_back(pos, rad, innerRat, nFlares, c,period(rng),amp(rng),rot(rng));
    }
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
    mouseCamCtrlr.Update();
    if (wnd.kbd.KeyIsPressed(0x51))  // Q = rotate cam anti clockwise
    {
        cam.SetAngle(cam.GetAngle()+0.01f);
    }
    if (wnd.kbd.KeyIsPressed(0x45))  // E = rotate cam clockwise
    {
        cam.SetAngle(cam.GetAngle() - 0.01f);
    }

    if (wnd.kbd.KeyIsPressed(0x41))  // A = left
    {
        stars[0].Translate({ -1,0 });
    }
    if (wnd.kbd.KeyIsPressed(0x44))  // D = right
    {
        stars[0].Translate({ 1,0 });
    }
    if (wnd.kbd.KeyIsPressed(0x57))  // W = up
    {
        stars[0].Translate({ 0,1 });
    }
    if (wnd.kbd.KeyIsPressed(0x53))  // S = down
    {
        stars[0].Translate({ 0,-1 });
    }
    if (wnd.kbd.KeyIsPressed(0x4A))  // J = cam left
    {
        cam.MoveBy({ -1,0 });
    }
    if (wnd.kbd.KeyIsPressed(0x4C))  // L = cam right
    {
        cam.MoveBy({ 1,0 });
    }
    if (wnd.kbd.KeyIsPressed(0x49))  // I = cam pan up
    {
        cam.MoveBy({ 0,1 });
    }
    if (wnd.kbd.KeyIsPressed(0x4B))  // K = cam pan down
    {
        cam.MoveBy({ 0,-1 });
    }

    //while (!wnd.kbd.KeyIsEmpty())
    //{
    //    // get an event from the queue
    //    const Keyboard::Event e = wnd.kbd.ReadKey();
    //    // check if it is a release event
    //    if (e.IsRelease())
    //    {
    //        // check if the event was for the space key
    //        if (e.GetCode() == 0x41) // A = left
    //        {
    //            star.Translate({ -10,0 });
    //        }
    //        if (e.GetCode() == 0x44) // D = right
    //        {
    //            star.Translate({ 10,0 });
    //        }
    //        if (e.GetCode() == 0x57) // W = up
    //        {
    //            star.Translate({ 0,10 });
    //        }
    //        if (e.GetCode() == 0x53) // S = down
    //        {
    //            star.Translate({ 0,-10 });
    //        }
    //    }
    //}

    
    
}

void Game::ComposeFrame()
{
    float dt = ft.Mark();
    for (Entity& e : stars)
    {
        e.Update(dt);
        cam.Draw(e.GetDrawable(dt));

    }
}
