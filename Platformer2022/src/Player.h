#ifndef PLAYER_H
#define PLAYER_H

#include "olcPixelGameEngine.h"
#include "Object.h"

class Player : public MovingObject
{
public:
	Player();
	Player(const olc::vf2d& position, int widthRad, int heightRad);
	~Player();
private:
	float acc = 0.046875f * 48.0f;
	float frc = 0.046875f * 48.0f;
	float dec = 0.5f * 48.0f;
	float top = 6.0f * 48.0f;

	AnchorPoint pointA;
	AnchorPoint pointB;
	AnchorPoint pointC;
	AnchorPoint pointD;
	AnchorPoint pointE;
	AnchorPoint pointF;
public:
	void Movement(float fElapsedTime) override;

	void DrawHitbox();
};
#endif // !PLAYER_H