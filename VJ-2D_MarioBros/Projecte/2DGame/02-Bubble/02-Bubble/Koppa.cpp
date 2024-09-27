#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Koppa.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum KoppaAnims
{
	MOVE_L, MOVE_R, DEAD, NONE
};


void Koppa::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	alive = start = shell = false;
	dieTime = 1000000;
	tam = glm::vec2(16, 24);
	esq = true;

	spritesheet.loadFromFile("images/newKoppa.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(16, 24), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);


	sprite->setAnimationSpeed(MOVE_L, 8);
	sprite->addKeyframe(MOVE_L, glm::vec2(0.0f, 0.f));
	sprite->addKeyframe(MOVE_L, glm::vec2(0.25f, 0.f));


	sprite->setAnimationSpeed(MOVE_R, 8);
	sprite->addKeyframe(MOVE_R, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(MOVE_R, glm::vec2(0.25f, 0.5f));

	sprite->setAnimationSpeed(DEAD, 8);
	sprite->addKeyframe(DEAD, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(DEAD, glm::vec2(0.75f, 0.f));



	spritesheetC.loadFromFile("images/closca.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheetC.setMinFilter(GL_NEAREST);
	spritesheetC.setMagFilter(GL_NEAREST);
	spriteC = Sprite::createSprite(glm::ivec2(16, 8), glm::vec2(0.5, 1), &spritesheetC, &shaderProgram);
	spriteC->setNumberAnimations(2);

	spriteC->setAnimationSpeed(DEAD, 8);
	spriteC->addKeyframe(DEAD, glm::vec2(0.f, 0.f));
	spriteC->addKeyframe(DEAD, glm::vec2(0.5f, 0.f));


	/*
	spritesheetC.loadFromFile("images/closca.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheetC.setMinFilter(GL_NEAREST);
	spritesheetC.setMagFilter(GL_NEAREST);
	closca = Sprite::createSprite(glm::ivec2(32, 16), glm::vec2(0.5, 0.5), &spritesheetC, &shaderProgram);


	closca->setAnimationSpeed(DEAD, 8);
	closca->addKeyframe(DEAD, glm::vec2(0.f, 0.f));
	closca->addKeyframe(DEAD, glm::vec2(0.5f, 0.f));



	closca->changeAnimation(2);
	*/

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posKoppa.x), float(tileMapDispl.y + posKoppa.y)));
}

void Koppa::update(int deltaTime)
{
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posKoppa.x), float(tileMapDispl.y + posKoppa.y)));
	//printf("g %d", posKoppa.x);
	//MOVIMENTS TORTUGA
	if (alive) {
		if (sprite->animation() == MOVE_L && esq)  //SI VA CAP A L'ESQUERRA I XOCA CANVIA A DRETA
		{
			posKoppa.x -= 1;
			if (map->collisionMoveLeft(posKoppa, tam))
			{
				posKoppa.x += 1;
				esq = false;
				sprite->changeAnimation(1);
			}
		}

		else if (sprite->animation() == MOVE_R && !esq) { //va cap a la dreta
			posKoppa.x += 1.;
			if (map->collisionMoveRight(posKoppa, tam))
			{
				posKoppa.x -= 1.;
				esq = true;
				sprite->changeAnimation(0);
			}

		}
		else if (sprite->animation() == DEAD) {
			movimentClosca(moveEsq);
		}
	}

}

void Koppa::moviment(int pos, int vel, int deltaTime)
{
	posKoppa.x = pos + vel*deltaTime;
	sprite->setPosition(posKoppa);
}



void Koppa::render()
{
	sprite->render();
}

void Koppa::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Koppa::setPosition(const glm::vec2 &pos)
{
	posKoppa = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posKoppa.x), float(tileMapDispl.y + posKoppa.y)));
}

float Koppa::getChange() {
	return change;
}

glm::vec2 Koppa::getPosition() {
	return posKoppa;
}

void Koppa::achafat() {
	/*
	sprite->changeAnimation(NONE);
	spriteC->changeAnimation(DEAD);
	spriteC->setPosition(glm::vec2(float(tileMapDispl.x + posKoppa.x), float(tileMapDispl.y + posKoppa.y + 16)));
	sprite = spriteC;
	//posKoppa.y += 48;
	alive = false;
	shell = true;
	/*spriteC = sprite;
	spriteC->changeAnimation(2);
	//spriteC->changeAnimation(DEAD);
	//posKoppa.y += 16;
	//spriteC->setPosition(glm::vec2(float(tileMapDispl.x + posKoppa.x), float(tileMapDispl.y + posKoppa.y)));
	//sprite = spriteC;
	//tam = glm::vec2(16, 8);
	shell = true;
	//posKoppa.y += 48;
	//alive = false;
	*/
	

	sprite->changeAnimation(DEAD);
	//posKoppa = glm::vec2(posKoppa.x, posKoppa.y);
	tam = glm::vec2(16, 9);
	shell = true;
	


}

glm::vec2 Koppa::getTam() {
	return tam;
}

void Koppa::movimentClosca(bool esq) {
	moveEsq = esq;
	if (moveEsq)
	{
		posKoppa.x -= 2;
		if (map->collisionMoveLeft(posKoppa, tam) || posKoppa.x <= 0) {
			moveEsq = false;
		}
	}
	else {
		posKoppa.x += 2;
		if (map->collisionMoveRight(posKoppa, tam)) {
			moveEsq = true;
		}
	}

}

void Koppa::changeMov() {
	esq = !esq;
	if (sprite->animation() == MOVE_R) sprite->changeAnimation(MOVE_L);
	else if (sprite->animation() == MOVE_L) sprite->changeAnimation(MOVE_R);
}

void Koppa::mortKoppa() {
	sprite->changeAnimation(DEAD);
	alive = false;
}

bool Koppa::isShell() {
	return shell;
}
