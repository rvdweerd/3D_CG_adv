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
                lastMousePos = (Vec2)e.GetPos();
                engaged = true;
                //LastCamPos = cam.GetPos();
            }
            if (e.GetType() == Mouse::Event::Type::LRelease)
            {
                engaged = false;
            }
            if (e.GetType() == Mouse::Event::Type::WheelUp) // enlarge
            {
                cam.Scale(zoomFactor);
            }
            if (e.GetType() == Mouse::Event::Type::WheelDown) // shrink
            {
                cam.Scale(1/zoomFactor);
            }
            if (engaged)
            {
                const Vec2 curMousePos = (Vec2)e.GetPos();
                Vec2 delta = curMousePos - lastMousePos;
                delta.x = -delta.x;
                cam.MoveBy(delta/cam.GetScale()/cam.GetSpeed());
                lastMousePos = curMousePos;
            }
        }
	}
private:
    static constexpr float zoomFactor = 1.05f;
    bool engaged = false;
	Mouse& mouse;
	Camera& cam;
	Vec2 lastMousePos = { 0,0 };
	//Vec2 lastCamPos = { 0,0 };
};
