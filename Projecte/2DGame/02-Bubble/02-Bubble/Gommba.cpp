#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Gommba.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 2


enum GommbaAnims
{
	MOVE_L, MOVE_R, DEAD, DEAD_DOWN
};

void Gommba::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	alive = false;
	start = false;
	dieTime = 1000000.f;
	tam = glm::vec2(16, 16);
	acc = 1;
	esq = false;

	spritesheet.loadFromFile("images/enemics.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(tam, glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	
	sprite->setAnimationSpeed(MOVE_L, 8);
	sprite->addKeyframe(MOVE_L, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_L, glm::vec2(0.f, 0.25f));

	sprite->setAnimationSpeed(MOVE_R, 8);
	sprite->addKeyframe(MOVE_R, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_R, glm::vec2(0.f, 0.25f));
	
	sprite->setAnimationSpeed(DEAD, 8);
	sprite->addKeyframe(DEAD, glm::vec2(0.f, 0.5f));

	sprite->changeAnimation(MOVE_R);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGommba.x), float(tileMapDispl.y + posGommba.y)));


}

void Gommba::update(int deltaTime)
{
	sprite->update(deltaTime);
	//printf("g %d", posGommba.x);
	//MOVIMENTS
	
	/*
	posGommba.y += FALL_STEP;
	if (map->collisionMoveDown(posGommba, glm::ivec2(16, 16), &posGommba.y))
	{
		posGommba.y -= FALL_STEP;
	}
	*/

	if (sprite->animation() == MOVE_L && esq)  //SI VA CAP A L'ESQUERRA I XOCA CANVIA A DRETA
	{
		posGommba.x -= 1;
		if (map->collisionMoveLeft(posGommba, tam))
		{
			posGommba.x += 1;
			esq = false;
			sprite->changeAnimation(1);
		}
	}

	else if (sprite->animation() == MOVE_R && !esq) { //va cap a la dreta
		posGommba.x += 1;
		if (map->collisionMoveRight(posGommba, tam))
		{
			posGommba.x -= 1;
			esq = true;
			sprite->changeAnimation(0);
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGommba.x), float(tileMapDispl.y + posGommba.y)));
}

void Gommba::moviment(int pos, int vel, int deltaTime) 
{
		posGommba.x = pos + vel*deltaTime;
		sprite->setPosition(posGommba);
}

void Gommba::render()
{
	sprite->render();
}

void Gommba::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Gommba::setPosition(const glm::vec2 &pos)
{
	posGommba = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGommba.x), float(tileMapDispl.y + posGommba.y)));
}

float Gommba::getChange() {
	return change;
}

glm::vec2 Gommba::getPosition() {
	return posGommba;
}

void Gommba::achafat() {
	sprite->changeAnimation(DEAD);
}
glm::vec2 Gommba::getTam() {
	return tam;
}

void Gommba::achafatKoppa() {
	sprite->changeAnimation(DEAD);
	dieJumping = true;
	startY = posGommba.y;

	if (dieJumping) {
		if (dieJump < 90) {
			dieJump += JUMP_ANGLE_STEP;
			posGommba.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
		}
		else {
			++acc;
			posGommba.y += FALL_STEP + acc;
		}
	}
}

void Gommba::changeMov() {
	esq = !esq;

	if (sprite->animation() == MOVE_R) sprite->changeAnimation(MOVE_L);
	else if (sprite->animation() == MOVE_L) sprite->changeAnimation(MOVE_R);
}


int Gommba::hitted() {
	return hit;
}

void Gommba::isHit() {
	hit = 1;
}

