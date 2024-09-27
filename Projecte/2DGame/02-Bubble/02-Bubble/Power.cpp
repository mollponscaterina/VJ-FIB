#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Power.h"
#include "Game.h"


enum PowerAnims
{
	COIN, MUSH, HIT, STAR
};


void Power::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int c)
{
	spritesheet.loadFromFile("images/objects.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(COIN, 8);
	sprite->addKeyframe(COIN, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MUSH, 8);
	sprite->addKeyframe(MUSH, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(HIT, 8);
	sprite->addKeyframe(HIT, glm::vec2(0.75f, 0.f));
	
	sprite->setAnimationSpeed(STAR, 8);
	sprite->addKeyframe(STAR, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(c);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPower.x), float(tileMapDispl.y + posPower.y)));

}

void Power::update(int deltaTime)
{
	sprite->update(deltaTime);

}

void Power::render()
{
	sprite->render();
}

void Power::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Power::setPosition(const glm::vec2 &pos)
{
	posPower = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPower.x), float(tileMapDispl.y + posPower.y)));
}

glm::vec2 Power::getPosition() {
	return posPower;
}

void Power::setView(int view) {
	if (view == 2) state = "hit";
	sprite->changeAnimation(view);
}


string Power::getState() {
	return state;
}