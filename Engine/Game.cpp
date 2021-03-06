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
#include "ChiliMath.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
    ct(gfx),
    rng(std::random_device()()),
    velDistr(0.f,500.f),
    cam(ct),
    mouseCamCtrlr(wnd.mouse,cam),
    plank( Vec2{ 100.0f,200.0f } , -380.0f , -200.0f , 200.0f)
{
    //std::random_device rd;
    //std::mt19937 rng(rd());
    std::uniform_real_distribution<float> xDist(-worldWidth/2, worldWidth/2);
    std::uniform_real_distribution<float> yDist( - worldHeight / 2, worldHeight / 2);
    std::normal_distribution<float> radDist(meanStarRadius,devStarRadius);
    std::normal_distribution<float> ratDist(meanInnerRatio, devInnerRatio);
    std::normal_distribution<float> flareDist( meanFlares, devFlares);
    const Color colors[] = { Colors::Red,Colors::White,Colors::Blue,Colors::Cyan,Colors::Magenta,Colors::Yellow,Colors::Gray,Colors::Green };
    std::uniform_int_distribution<size_t> colorSampler(0, std::end(colors)-std::begin(colors));
    std::uniform_real_distribution<float> period(0.5f, 2.f);
    std::uniform_real_distribution<float> amp(1.0f, 1.5f);

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
        stars.emplace_back(pos, rad, innerRat, nFlares, c,period(rng),amp(rng));
    }
    stars.emplace_back(Vec2{ 0.0f,0.0f }, 5.0f, 2.0f, 5, Colors::Red, 3.141f/4, 1.0f,1.05f,true);
    stars.emplace_back(Vec2{ 0.0f,0.0f }, 250.0f, 1.0f, 15, Colors::Red);

    balls.emplace_back(Ball(10.f, { -50,-50 }, { -50,50 }, Colors::Red));
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
    //if (wnd.kbd.KeyIsPressed(0x41))  // A = left
    //{
    //    //stars[0].Translate({ -1,0 });
    //    //cam.MoveBy({ -1 * stars[0].GetSpeed() ,0 }); ///  cam.GetScale()/cam.GetSpeed()
    //    plank.Translate({ -1,0 });
    //}
    //if (wnd.kbd.KeyIsPressed(0x44))  // D = right
    //{
    //    //stars[0].Translate({ 1,0 });
    //    //cam.MoveTo(stars[0].GetPos());
    //    plank.Translate({ 1,0 });
    //}
    Freeze = false;
    if (wnd.kbd.KeyIsPressed(VK_SPACE))  // space = freeze
    {
        //stars[0].Translate({ 0,1 });
        //cam.MoveTo(stars[0].GetPos());
        Freeze = true;
    }
    if (wnd.kbd.KeyIsPressed(0x57))  // W = up
    {
        //stars[0].Translate({ 0,1 });
        //cam.MoveTo(stars[0].GetPos());
        plank.MoveFreeY(2.0f);
    }
    if (wnd.kbd.KeyIsPressed(0x53))  // S = down
    {
        //stars[0].Translate({ 0,-1 });
        //cam.MoveTo(stars[0].GetPos());
        plank.MoveFreeY(-2.0f);
    }
    //if (wnd.kbd.KeyIsPressed(0x51))  // Q = accelerate
    //{
    //    stars[0].Accelerate(1.05f);
    //}
    //if (wnd.kbd.KeyIsPressed(0x5A))  // Z = decelerate
    //{
    //    stars[0].Accelerate(0.95f);
    //}
    if (wnd.kbd.KeyIsPressed(0x4A))  // J = left
    {
        plank.TranslateBy({ -1, 0 });
    }
    if (wnd.kbd.KeyIsPressed(0x4C))  // L = right
    {
        plank.TranslateBy({ 1, 0 });
    }
    if (wnd.kbd.KeyIsPressed(0x49))  // I = up
    {
        plank.TranslateBy({ 0, 1 });
    }
    if (wnd.kbd.KeyIsPressed(0x4B))  // K = down
    {
        plank.TranslateBy({ 0, -1 });
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

    float dt = ft.Mark();
    time_elapsed += dt;
    if (time_elapsed > 0.5f)
    {
        if (!Freeze) balls.emplace_back(Ball(10.f, { -50,-50 }, { -velDistr(rng),velDistr(rng) }, Colors::Red));
        time_elapsed = 0.0f;
    }
    
    auto it = std::remove_if(balls.begin(), balls.end(), [&](Ball& b) { 
        float ballDist = b.GetPos().Len();
        float Range = stars[1].GetRadius();
        return (b.GetPos().LenSq() > std::pow(stars[1].GetRadius(),2) ); 
        } );
    balls.erase(it, balls.end());

    const auto plankPts = plank.GetPoints();
    //for (auto& b : balls)
    //{
    //    float dist = DistancePointLine(plankPts.first, plankPts.second, b.GetPos());
    //    if (dist < b.GetRadius())
    //    {
    //        collideSound.Play();
    //        const Vec2 w = plank.GetPlankSurfaceVector().GetNormalized();
    //        const Vec2 v = b.GetVelocityVector();
    //        Vec2 newvel = w * (v * w) * 2.0f - v;
    //        b.SetVel(newvel);
    //    }
    //    b.Update(dt);
    //}

    Vec2 barrier = plank.GetPlankSurfaceVector();
    Vec2 barrier_N = { barrier.y, -barrier.x };
    for (auto& b : balls)
    {
        //Work in plank model coordinates
        Vec2 ballPos_M = b.GetPos() - plank.GetPos();
        Vec2 p = barrier * ( barrier.Dot(ballPos_M) / (barrier*barrier) );
        Vec2 e = ballPos_M - p;
        //TEST//
        //float dist = e.Len();

        Vec2 ballVel_M = b.GetVelocityVector();
        float dot_collision = barrier_N.Dot(ballVel_M);
        if (e.LenSq() < b.GetRadius()*b.GetRadius() && dot_collision < 0)
        {
            //std::stringstream ss;
            //ss << "Distance from plank: "<<dist<<", dotprod: "<<dot_collision<<'\n';
            //OutputDebugStringA( ss.str().c_str() );
            
            Vec2 q = barrier * barrier.Dot(ballVel_M) / barrier.Dot(barrier);
            Vec2 f = ballVel_M - q;
            Vec2 newVel_M = q - f;
            b.SetVel(newVel_M);
        }
        if(!Freeze) b.Update(dt);
    }

    for (auto& s : stars)
    {
        s.Update(dt);
    }
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

    for (Entity& e : stars)
    {
        //cam.DrawClosedPolyline(e.GetPolyLine(), Colors::Red);
        cam.Draw(e.GetDrawable());
    }
    cam.Draw(plank.GetDrawable());
    //gfx.DrawClosedPolyline(vertices, Colors::Red);
    for (auto& b : balls)
    {
        cam.Draw(b.GetDrawable());
    }
    
}
