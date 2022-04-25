#ifndef GAME_H
#define GAME_H

#include "olcPixelGameEngine.h"
#include "Level.h"
#include "Player.h"

struct Camera
{
public:
	olc::vf2d position;
	olc::vi2d viewPort;
	olc::vf2d offset;

public:
	Camera();

	void Update();
};

class Game : public olc::PixelGameEngine
{
public:
	Game();
	~Game();

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	int ToDegree(float radians);
public:
	std::unique_ptr<Level> level;
	std::unique_ptr<Player> player;
	std::unique_ptr<Camera> camera;
};

inline Game* game = new Game();

#endif // !GAME_H