#ifndef _POWER_INCLUDE
#define _POWER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Power is basically a Sprite that represents the Power.


class Power
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int c);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setView(int view);
	glm::vec2 getPosition();
	string getState();



private:
	glm::ivec2 tileMapDispl, posPower;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	string state = "notHit";


};


#endif // _POWER_INCLUDE


