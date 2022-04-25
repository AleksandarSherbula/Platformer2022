#include "Playground.h"

Playground::Playground()
{
	sAppName = "Testing Space";
	std::cout << "Playground called\n";
}

Playground::~Playground()
{
}

bool Playground::OnUserCreate()
{
	angle = 0.0f;

    level = std::make_unique<Level>();
    level->Load("data/images/Testing.png", "data/json/Testing.json", "data/json/GreenHill16x16Tiles.json");

    testPoint = AnchorPoint({ 0, -1 });
    testPoint.pos = { 32.0f, 32.0f };
    
	return true;
}

bool Playground::OnUserUpdate(float fElapsedTime)
{
	//mPosition = { std::sinf(angle) * 20.0f + ScreenWidth() / 2.0f, std::cosf(angle) * 20.0f + ScreenHeight() / 2.0f };

    if (GetKey(olc::LEFT).bHeld)
        testPoint.pos.x -= 6.0f * fElapsedTime;
    if (GetKey(olc::RIGHT).bHeld)
        testPoint.pos.x += 6.0f * fElapsedTime;
    if (GetKey(olc::UP).bHeld)
        testPoint.pos.y -= 6.0f * fElapsedTime;
    if (GetKey(olc::DOWN).bHeld)
        testPoint.pos.y += 6.0f * fElapsedTime;


	Clear(olc::BLACK);

    DrawDecal(olc::vf2d(0, 0), level->spr.Decal());

    FillRectDecal(testPoint.pos, olc::vi2d(1, 1));
    FindSurface(testPoint);

	return !GetKey(olc::ESCAPE).bPressed;
}

float Playground::ToDegree(float radians)
{
	return (radians / 3.14159) * 180.0f;
}

void Playground::FindSurface(AnchorPoint& point)
{
    bool search = true;
    olc::vf2d surfacePoint = point.pos;

    while (search)
    {
        Tile* mapTile = level->GetTile(surfacePoint / 16);
        JsonTileData* tileData = level->tileset.GetTileData(mapTile->id - 1);

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
    FillRectDecal(surfacePoint, olc::vi2d(1, 1), olc::BLUE);
}
