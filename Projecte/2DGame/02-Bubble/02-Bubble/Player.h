#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Bloc.h"



// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, string type);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	float getChange();
	void move();
	void moveLeft(int n);
	void moveRight(int n);
	void stopMoving();
	void jump();
	void handleJumpAndGravity();
	void death_animation();
	glm::vec2 getTam();
	glm::vec2 getPosition();
	int getVel();
	bool blocCollision();
	string getLife();
	string getState();
	void setState(string s);
	void mort();




private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	float change = 0.f;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	float velocitat = 0.0f, acceleracio = 0.1f, vMax = 2.f;
	bool dead = false, falling = false;
	glm::vec2 tam;
	ShaderProgram shader;
	int desviacio = 0;
	string state = "normal", life = "alive";
	Bloc *bloc;

};


#endif // _PLAYER_INCLUDE