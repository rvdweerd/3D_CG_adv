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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
    ct(gfx),
    cam(ct)
{
    stars.emplace_back(Entity(Star::Make(100, 50, 7), { 0,0 }));
    stars.emplace_back(Entity(Star::Make(50, 15, 5), { 100,100 }));
    stars.emplace_back(Entity(Star::Make(25, 5, 3), { -100,100 }));
    stars.emplace_back(Entity(Star::Make(70, 15, 20), { -100,-100 }));
    stars.emplace_back(Entity(Star::Make(60, 45, 9), { 100,-100 }));
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
    while (!wnd.mouse.IsEmpty())
    {
        if (wnd.mouse.LeftIsPressed())
        {
            //const Vec2 pointerPos(float(wnd.mouse.GetPosX()), float(wnd.mouse.GetPosY()));
            stars[0].SetPos(Vec2{ (float)wnd.mouse.GetPosX() - Graphics::ScreenWidth / 2, Graphics::ScreenHeight / 2 - (float)wnd.mouse.GetPosY() });

        }
        auto e = wnd.mouse.Read();
        if (e.GetType() == Mouse::Event::Type::WheelUp) // enlarge
        {
            //stars[0].Scale(1.05f);
            cam.Scale(1.05f);
        }
        if (e.GetType() == Mouse::Event::Type::WheelDown) // shrink
        {
            //stars[0].Scale(0.95f);
            cam.Scale(0.95f);
        }
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
    if (wnd.kbd.KeyIsPressed(0x51))  // Q = accelerate
    {
        stars[0].Accelerate(1.05f);
    }
    if (wnd.kbd.KeyIsPressed(0x5A))  // Z = decelerate
    {
        stars[0].Accelerate(0.95f);
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
    //Vec2 v1{ 100,100 };
    //gfx.DrawLine(v1, Vec2{ (float)wnd.mouse.GetPosX(), (float)wnd.mouse.GetPosY() }, Colors::White);
    //std::vector<Vec2> vertices = Star::Make(175, 75, 7);
    //for (auto& v : vertices)
    //{
    //    v += {200, 200};
    //}
    for (const auto& e : stars)
    {
        cam.DrawClosedPolyline(e.GetPolyLine(), Colors::Red);
    }
    //gfx.DrawClosedPolyline(vertices, Colors::Red);
    
}
