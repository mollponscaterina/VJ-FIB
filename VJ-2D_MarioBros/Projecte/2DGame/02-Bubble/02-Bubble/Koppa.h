#pragma once
#ifndef _KOPPA_INCLUDE
#define _KOPPA_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Koppa is basically a Sprite that represents the Koppa. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Koppa
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
	void achafat();
	bool alive, start, shell = false;
	float dieTime;

	glm::vec2 getTam();
	bool moveEsq;
	void movimentClosca(bool esq);
	void changeMov();
	void mortKoppa();
	bool isShell();



private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posKoppa;
	int jumpAngle, startY;
	float change = 0.f;
	Texture spritesheet;
	Texture spritesheetC;

	Sprite *sprite, *spriteK, *spriteC;
	TileMap *map;
	float velocitat = 0, vMax = 2, acceleracio = 0.4;
	glm::vec2 tam;

	bool esq;

};


#endif // _KOPPA_INCLUDE


