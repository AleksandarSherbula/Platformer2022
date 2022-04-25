#include "Player.h"
#include "Game.h"

Player::Player() : MovingObject()
{
}

Player::Player(const olc::vf2d& position, int widthRad, int heightRad)
    : MovingObject(position, widthRad, heightRad)
{
    pointA = AnchorPoint({ 0,  1});
    pointB = AnchorPoint({ 0,  1});
    pointC = AnchorPoint({ 0, -1});
    pointD = AnchorPoint({ 0, -1});
    pointE = AnchorPoint({-1,  0});
    pointF = AnchorPoint({ 1,  0});
}

Player::~Player()
{
}

void Player::Movement(float fElapsedTime)
{
    if (game->GetKey(olc::LEFT).bHeld == game->GetKey(olc::RIGHT).bHeld)
    {
    	mVelocity.x -= std::min(std::fabs(mVelocity.x), frc) * (mVelocity.x < 0.0f ? -1 : 1);
    }
    else
    {
    	if (game->GetKey(olc::LEFT).bHeld)
    	{
    		if (mVelocity.x > 0.0f)
    		{
    			mVelocity.x -= dec;
    			if (mVelocity.x <= 0)
    				mVelocity.x = -0.5f;
    		}
    		else if (mVelocity.x > -top)
    		{
    			mVelocity.x -= acc;
    			if (mVelocity.x <= -top)
    				mVelocity.x = -top;
    		}
    	}
    	if (game->GetKey(olc::RIGHT).bHeld)
    	{
    		if (mVelocity.x < 0.0f)
    		{
    			mVelocity.x += dec;
    			if (mVelocity.x >= 0)
    				mVelocity.x = 0.5f;
    		}
    		else if (mVelocity.x < top)
    		{
    			mVelocity.x += acc;
    			if (mVelocity.x >= top)
    				mVelocity.x = top;
    		}
    	}
    }

    mPosition.x += mVelocity.x * fElapsedTime;    
    mPosition.y += mVelocity.y * fElapsedTime;    

    pointA.pos = { mPosition.x - hitbox.widthRad, mPosition.y + hitbox.heightRad};
    pointB.pos = { mPosition.x + hitbox.widthRad, mPosition.y + hitbox.heightRad};

    pointC.pos = { mPosition.x - hitbox.widthRad, mPosition.y - hitbox.heightRad };
    pointD.pos = { mPosition.x + hitbox.widthRad, mPosition.y - hitbox.heightRad };

    pointE.pos = { mPosition.x - hitbox.widthRad - 1, mPosition.y };
    pointF.pos = { mPosition.x + hitbox.widthRad + 1, mPosition.y };

    FindSurface(pointA);
    FindSurface(pointB);    
    FindSurface(pointC);    
    FindSurface(pointD);    

    float winningDistance = std::min(pointA.distance.y, pointB.distance.y);
    float winningDistance2 = std::min(pointC.distance.y, pointD.distance.y);
    
    if (winningDistance > -16.0f && winningDistance < std::min(std::abs(mVelocity.x) + 4, 16.0f))
    {
        mPosition.y += winningDistance;
    }

    if (winningDistance2 > -16.0f && winningDistance2 < std::min(std::abs(mVelocity.x) + 4, 16.0f))
    {
        mPosition.y += winningDistance2;
    }
}

void Player::DrawHitbox()
{
    // Hitbox
    game->FillRectDecal(olc::vf2d(pointC.pos.x - game->camera->offset.x * 16, pointC.pos.y), olc::vi2d(hitbox.widthRad * 2 + 1, hitbox.heightRad * 2 + 1), olc::Pixel(255, 0, 255, 128));

    // Sensor A line and point
    game->FillRectDecal(olc::vf2d(pointA.pos.x - game->camera->offset.x * 16, pointA.pos.y - hitbox.heightRad), olc::vi2d(1, hitbox.heightRad), olc::Pixel(0, 240, 0));
    game->FillRectDecal(olc::vf2d(pointA.pos.x - game->camera->offset.x * 16, pointA.pos.y), olc::vi2d(1, 1));

    // Sensor B line and point
    game->FillRectDecal(olc::vf2d(pointB.pos.x - game->camera->offset.x * 16, pointB.pos.y - hitbox.heightRad), olc::vi2d(1, hitbox.heightRad), olc::Pixel(56, 255, 162));
    game->FillRectDecal(olc::vf2d(pointB.pos.x - game->camera->offset.x * 16, pointB.pos.y), olc::vi2d(1, 1));

    // Sensor C line and point
    game->FillRectDecal(olc::vf2d(pointC.pos.x - game->camera->offset.x * 16, pointC.pos.y), olc::vi2d(1, hitbox.heightRad), olc::Pixel(0, 174, 239));
    game->FillRectDecal(olc::vf2d(pointC.pos.x - game->camera->offset.x * 16, pointC.pos.y), olc::vi2d(1, 1));

    // Sensor D line and point
    game->FillRectDecal(olc::vf2d(pointD.pos.x - game->camera->offset.x * 16, pointD.pos.y), olc::vi2d(1, hitbox.heightRad), olc::Pixel(255, 242, 56));
    game->FillRectDecal(olc::vf2d(pointD.pos.x - game->camera->offset.x * 16, pointD.pos.y), olc::vi2d(1, 1));

    // Sensor E line and point
    game->FillRectDecal(olc::vf2d((pointE.pos.x + 1) - game->camera->offset.x * 16, pointE.pos.y), olc::vi2d(hitbox.widthRad, 1), olc::Pixel(255, 56, 255));
    game->FillRectDecal(olc::vf2d(pointE.pos.x - game->camera->offset.x * 16, pointE.pos.y), olc::vi2d(1, 1));

    // Sensor F line and point
    game->FillRectDecal(olc::vf2d((mPosition.x + 1) - game->camera->offset.x * 16, mPosition.y), olc::vi2d(hitbox.widthRad, 1), olc::Pixel(255, 84, 84));
    game->FillRectDecal(olc::vf2d(pointF.pos.x - game->camera->offset.x * 16, pointF.pos.y), olc::vi2d(1, 1));

    // Position point
    game->FillRectDecal(olc::vf2d((mPosition.x - 1) - game->camera->offset.x * 16, mPosition.y), olc::vi2d(1, 1));
    game->FillRectDecal(olc::vf2d((mPosition.x + 1) - game->camera->offset.x * 16, mPosition.y), olc::vi2d(1, 1));
    game->FillRectDecal(olc::vf2d(mPosition.x - game->camera->offset.x * 16, mPosition.y - 1), olc::vi2d(1, 1));
    game->FillRectDecal(olc::vf2d(mPosition.x - game->camera->offset.x * 16, mPosition.y + 1), olc::vi2d(1, 1));
    game->FillRectDecal(olc::vf2d(mPosition.x - game->camera->offset.x * 16, mPosition.y), olc::vi2d(1, 1), olc::BLACK);

    // Surfaces
    //game->FillRectDecal(pointA.pos + pointA.distance, olc::vi2d(1, 1), olc::RED);
    //game->FillRectDecal(pointB.pos + pointB.distance, olc::vi2d(1, 1), olc::RED);
}
