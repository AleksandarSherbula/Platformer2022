#ifndef LEVEL_H
#define LEVEL_H

#include "olcPixelGameEngine.h"
#include "nlohmann/json.hpp"
#include "FileReading.h"

#include <array>

struct Collider
{
	int x;
	int y;
	int width;
	int height;
};

class JsonTileData
{
public:
	unsigned int id;
	bool isGround;
	std::vector<Collider> colliders;
public:
	JsonTileData();
	bool IsSolid();
	bool IsFullBlock();
};

class Tileset
{
private:
	nlohmann::json mJson;
	std::vector<JsonTileData> tileData;
public:
	Tileset();
	Tileset(const std::string& jsonFile);

	JsonTileData* GetTileData(unsigned int id);
};

class Tile
{
public:
	Tile(unsigned int id);
public:
	unsigned int id;
	olc::vf2d pos;
	bool H_Flip;
	bool V_Flip;
	bool D_Flip;
	bool R_Flip;
};

class Level
{
public:
	Level();

	void Load(const std::string& imageFile, const std::string& mapJsonFile, const std::string& tilesetJson);

	Tile* GetTile(const olc::vi2d& pos);
	Tile* GetTile(int mapIndex);
		
	void Update(float fElapsedTime);

	void Draw();
	void DrawColliders();
private:
	nlohmann::json mJson;
	std::vector<Tile> mData;
public:
	olc::Renderable spr;
	int width;
	int height;
	Tileset tileset;
};

#endif // LEVEL_H