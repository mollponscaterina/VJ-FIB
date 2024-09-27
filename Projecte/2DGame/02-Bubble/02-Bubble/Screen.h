#ifndef _SCREEN_INCLUDE
#define _SCREEN_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Screen is basically a Sprite that represents the Screen.


class Screen
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int c);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setView(int view);
	glm::vec2 getPosition();



private:
	glm::ivec2 tileMapDispl, posScreen;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;


};


#endif // _SCREEN_INCLUDE


