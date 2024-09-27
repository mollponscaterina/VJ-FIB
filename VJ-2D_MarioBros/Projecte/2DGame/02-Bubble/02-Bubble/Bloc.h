#ifndef _BLOC_INCLUDE
#define _BLOC_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// BLOC is basically a Sprite that represents the BLOC.


class Bloc
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
	glm::ivec2 tileMapDispl, posBloc;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	string state = "notHit";


};


#endif // _BLOC_INCLUDE


