#pragma once
#include "Mouse.h"
#include "Camera.h"

class MouseCameraController
{
public:
	MouseCameraController(Mouse& ms, Camera& c)
		:
		mouse(ms),
		cam(c)
	{}
	void Update()
	{
        while (!mouse.IsEmpty())
        {
            const auto e = mouse.Read();
            if (e.GetType() == Mouse::Event::Type::LPress)
            {
                LastMousePos = { -(float)e.GetPosX(),(float)e.GetPosY() };
                LastCamPos = cam.GetPos();
            }
            if (mouse.LeftIsPressed())
            {
                Vec2 screenMovement = (Vec2{ -(float)mouse.GetPosX(),(float)mouse.GetPosY() } -LastMousePos);
                cam.MoveTo(LastCamPos + screenMovement / cam.GetScale());
            }
            if (e.GetType() == Mouse::Event::Type::WheelUp) // enlarge
            {
                cam.Scale(1.05f);
            }
            if (e.GetType() == Mouse::Event::Type::WheelDown) // shrink
            {
                cam.Scale(0.95f);
            }
        }
	}
private:
	Mouse& mouse;
	Camera& cam;
	Vec2 LastMousePos = { 0,0 };
	Vec2 LastCamPos = { 0,0 };
};
