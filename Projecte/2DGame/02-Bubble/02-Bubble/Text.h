#ifndef _TEXT_INCLUDE
#define _TEXT_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Text is basically a Sprite that represents the Text.


class Text
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
	glm::ivec2 tileMapDispl, posText;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;


};


#endif // _TEXT_INCLUDE


