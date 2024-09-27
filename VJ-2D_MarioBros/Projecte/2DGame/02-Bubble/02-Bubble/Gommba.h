#ifndef _GOMMBA_INCLUDE
#define _GOMMBA_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Gommba is basically a Sprite that represents the Gommba. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Gommba
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	float getChange();

	void moviment(int pos, int vel, int deltaTime);
	glm::vec2 getPosition();
	glm::vec2 getTam();
	void achafat();
	bool alive;
	bool start;
	float dieTime;
	void achafatKoppa();
	void changeMov();
	int hitted();
	void isHit();


private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posGommba;
	int jumpAngle, startY;
	float change = 0.f;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	float velocitat = 0, vMax = 2, acceleracio = 0.4;
	glm::vec2 tam;
	bool dieJumping, esq;
	int acc, dieJump; 
	int hit = 0;



};


#endif // _GOMMBA_INCLUDE


