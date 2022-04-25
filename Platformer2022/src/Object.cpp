#include "Object.h"
#include "Game.h"

Object::Object()
{
}

Object::Object(const olc::vf2d& position, int widthRad, int heightRad)
{
	mPosition = position;
	hitbox.widthRad = widthRad;
	hitbox.heightRad = heightRad;
}

olc::vf2d& Object::Position()
{
	return mPosition;
}

olc::vi2d Object::PositionInt()
{
	return olc::vi2d(mPosition);
}

void Object::Draw()
{
	game->FillRectDecal(olc::vf2d((mPosition.x - hitbox.widthRad), mPosition.y - hitbox.heightRad), olc::vi2d(2 * hitbox.widthRad + 1, 2 * hitbox.heightRad + 1),
		olc::Pixel(255, 0, 255, 128));
	game->FillRectDecal(olc::vi2d((mPosition.x - 1), mPosition.y), olc::vi2d(1, 1));
	game->FillRectDecal(olc::vi2d((mPosition.x + 1), mPosition.y), olc::vi2d(1, 1));
	game->FillRectDecal(olc::vi2d(mPosition.x, mPosition.y - 1), olc::vi2d(1, 1));
	game->FillRectDecal(olc::vi2d(mPosition.x, mPosition.y + 1), olc::vi2d(1, 1));
}

MovingObject::MovingObject() : Object()
{
    mVelocity = { 0.0f, 0.0f };
}

MovingObject::MovingObject(const olc::vf2d& position, int widthRad, int heightRad)
	: Object(position, widthRad, heightRad)
{
    mVelocity = { 0.0f, 0.0f };
}

void MovingObject::Movement(float fElapsedTime)
{
    
}

void MovingObject::FindSurface(AnchorPoint& point)
{
    /*bool search = true;
    olc::vf2d testPoint = point.pos;
    olc::vf2d surfacePoint = point.pos;

    while (search)
    {
        Tile* mapTile = game->level->GetTile(testPoint / 16);
        JsonTileData* tileData = game->level->tileset.GetTileData(mapTile->id - 1);

        if (tileData == nullptr || !tileData->IsSolid())
        {
            if (point.pos.y >= mapTile->pos.y * 16 && point.pos.y < mapTile->pos.y * 16 + 16)
            {
                if (point.dir.y != 0)
                    testPoint = surfacePoint = { point.pos.x, (mapTile->pos.y + 1) * 16};
                else if (point.dir.x != 0)
                    testPoint = surfacePoint = { (mapTile->pos.y + 1) * 16, point.pos.y };
            }
            else
            {
                if (point.dir.y != 0)
                    surfacePoint.y = mapTile->pos.y * 16 + 15;
                else if (point.dir.x != 0)
                    surfacePoint.x = mapTile->pos.x * 16 + 15;
                search = false;
            }

        }
        else
        {
            if (tileData->IsFullBlock()) // Tile is a full block
            {
                if (point.pos.x >= mapTile->pos.x * 16 && point.pos.x < mapTile->pos.x * 16 + 16 &&
                    point.pos.y >= mapTile->pos.y * 16 && point.pos.y < mapTile->pos.y * 16 + 16)
                {
                    testPoint = surfacePoint = { point.pos.x, mapTile->pos.y * 16 - 16 };
                }
                else
                {                
                    surfacePoint = { point.pos.x, mapTile->pos.y * 16 - 1 };
                    search = false;
                }
            }
            else
            {
                int tileHeightIndex;
                if (mapTile->H_Flip)
                    tileHeightIndex = (mapTile->pos.x * 16 + 15) - point.pos.x;
                else
                    tileHeightIndex = point.pos.x - mapTile->pos.x * 16;

                //int colX = solidTile->colliders[tileHeightIndex].x;
                int colY = tileData->colliders[tileHeightIndex].y;
                //colWidth = solidTile->colliders[tileHeightIndex].width;
                //colHeight = solidTile->colliders[tileHeightIndex].height;


                surfacePoint = { point.pos.x, mapTile->pos.y * 16 + colY - 1 };
                search = false;             
            }
        }
    }

    point.distance = surfacePoint - point.pos;*/

    bool search = true;
    olc::vf2d surfacePoint = point.pos;

    while (search)
    {
        Tile* mapTile = game->level->GetTile(surfacePoint / 16);
        JsonTileData* tileData = game->level->tileset.GetTileData(mapTile->id - 1);

        if (tileData == nullptr || !tileData->IsSolid())
        {
            if (point.pos.x >= mapTile->pos.x * 16 && point.pos.x < mapTile->pos.x * 16 + 16 &&
                point.pos.y >= mapTile->pos.y * 16 && point.pos.y < mapTile->pos.y * 16 + 16)
            {
                if (point.dir.y != 0)
                    surfacePoint = { point.pos.x, (mapTile->pos.y + point.dir.y) * 16 };
                else if (point.dir.x != 0)
                    surfacePoint = { (mapTile->pos.x + point.dir.x) * 16, point.pos.y };
            }
            else
            {
                // in - 1 dirs, no changes to surface point is happening, hence no check for it 

                if (point.dir.x == 1)
                    surfacePoint.x = mapTile->pos.x * 16 + 15;
                else if (point.dir.y == 1)
                    surfacePoint.y = mapTile->pos.y * 16 + 15;
                search = false;
            }

        }
        else
        {
            if (tileData->IsFullBlock()) // Tile is a full block 
            {
                if (point.dir.x == -1)
                    surfacePoint = { (mapTile->pos.x + 1) * 16, point.pos.y };
                else if (point.dir.x == 1)
                    surfacePoint = { mapTile->pos.x * 16 - 1, point.pos.y };
                else if (point.dir.y == -1)
                    surfacePoint = { point.pos.x, (mapTile->pos.y + 1) * 16 };
                else if (point.dir.y == 1)
                    surfacePoint = { point.pos.x, mapTile->pos.y * 16 - 1 };

                if (point.pos.x >= mapTile->pos.x * 16 && point.pos.x < (mapTile->pos.x + 1) * 16 &&
                    point.pos.y >= mapTile->pos.y * 16 && point.pos.y < (mapTile->pos.y + 1) * 16)
                {
                    continue;
                }
                search = false;
            }
            else
            {
                if (point.dir.y == 1)
                {
                    int tileHeightIndex;
                    if (mapTile->H_Flip)
                        tileHeightIndex = (mapTile->pos.x * 16 + 15) - point.pos.x;
                    else
                        tileHeightIndex = point.pos.x - mapTile->pos.x * 16;

                    int colY = tileData->colliders[tileHeightIndex].y;
                    surfacePoint = { point.pos.x, mapTile->pos.y * 16 + colY - 1 };
                }
                else if (point.dir.y == -1)
                    surfacePoint = { point.pos.x, (mapTile->pos.y + 1) * 16 };

                search = false;
            }
        }
    }

    point.distance = surfacePoint - point.pos;
}

AnchorPoint::AnchorPoint()
{

}

AnchorPoint::AnchorPoint(const olc::vi2d& dir)
{
    this->dir = dir;
}