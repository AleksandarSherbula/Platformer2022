#include "Game.h"

Game::Game()
{
    sAppName = "Platformer2022";
}

Game::~Game()
{
}

bool Game::OnUserCreate()
{
    level = std::make_unique<Level>();    
    level->Load("data/images/GHZ1.png", "data/json/GHZ1_Proto.json", "data/json/GreenHill16x16Tiles.json");

    player = std::make_unique<Player>(olc::vf2d(70.0f, 181.0f), 9, 19);
    camera = std::make_unique<Camera>();

    return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{ 
    player->Movement(fElapsedTime);
    level->Update(fElapsedTime);
    camera->Update();    

    Clear(olc::DARK_CYAN);

    level->Draw();
    level->DrawColliders();
    player->DrawHitbox();

    game->DrawStringDecal(olc::vi2d(5, 5), std::to_string((int)player->Position().x) + " : " + std::to_string((int)player->Position().y));
    game->DrawStringDecal(olc::vi2d(5, 18), std::to_string(camera->offset.x) + " : " + std::to_string((int)player->Position().y));

    return !GetKey(olc::ESCAPE).bPressed;
}

int Game::ToDegree(float radians)
{
    return (radians / 3.14159) * 180.0f;
}

Camera::Camera()
{
}

void Camera::Update()
{
    position = game->player->Position() / 16;
    viewPort = { game->ScreenWidth() / 16, game->ScreenHeight() / 16 };

    offset = position - viewPort / 2.0f;

    if (position.x < 0.0f) position.x = 0.0f;
    if (position.x > game->level->width - 1) position.x = game->level->width - 1;

    if (offset.x < 0) offset.x = 0;
    if (offset.x > game->level->width - viewPort.x) offset.x = game->level->width - viewPort.x;
    if (offset.y < 0) offset.y = 0;
    if (offset.y > game->level->height - viewPort.y) offset.y = game->level->height - viewPort.y;
}
