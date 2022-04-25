#ifndef OBJECT_H
#define OBJECT_H

#include "olcPixelGameEngine.h"
#include "Level.h"

class AnchorPoint
{
public:
	olc::vf2d pos;
	olc::vi2d distance;
	olc::vi2d dir;
public:
	AnchorPoint();
	AnchorPoint(const olc::vi2d& dir);
};

class Object
{
protected:
	olc::vf2d mPosition;
	//olc::Renderable rend;
public:
	struct HitBox
	{
		int widthRad;
		int heightRad;
	} hitbox;
public:
	Object();
	Object(const olc::vf2d& position, int widthRad, int heightRad);

	olc::vf2d& Position();
	olc::vi2d PositionInt();

	virtual void Draw();
};

class MovingObject : public Object
{
protected:
	olc::vf2d mVelocity;
public:
	MovingObject();
	MovingObject(const olc::vf2d& position, int widthRad, int heightRad);

	virtual void Movement(float fElapsedTime);

	void FindSurface(AnchorPoint& point);
};

#endif // !OBJECT_H


