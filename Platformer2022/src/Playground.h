#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "olcPixelGameEngine.h"
#include "Object.h"
#include "Level.h"

class Playground : public olc::PixelGameEngine
{
public:
	Playground();
	~Playground();	

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	float ToDegree(float radians);

	float angle;
	olc::vf2d mVelocity;
	olc::vf2d mPosition;
	std::unique_ptr<Level> level;
	AnchorPoint testPoint;

	void FindSurface(AnchorPoint& point);
};

#endif // !TEST_APP_H