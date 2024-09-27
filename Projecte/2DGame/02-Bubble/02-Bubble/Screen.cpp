#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Screen.h"
#include "Game.h"


enum ScreenAnims
{
	SCREEN1, SCREEN2, SCREEN3, SCREEN4, SCREEN5, SCREEN6
};


void Screen::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int c)
{
	spritesheet.loadFromFile("images/screens.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(256, 240), glm::vec2(0.5f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(SCREEN1, 8);
	sprite->addKeyframe(SCREEN1, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(SCREEN2, 8);
	sprite->addKeyframe(SCREEN2, glm::vec2(0.f, 0.25f));

	sprite->setAnimationSpeed(SCREEN3, 8);
	sprite->addKeyframe(SCREEN3, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(SCREEN4, 8);
	sprite->addKeyframe(SCREEN4, glm::vec2(0.5f, 0.25f));

	sprite->setAnimationSpeed(SCREEN5, 8);
	sprite->addKeyframe(SCREEN5, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(SCREEN6, 8);
	sprite->addKeyframe(SCREEN6, glm::vec2(0.f, 0.75f));

	sprite->changeAnimation(c);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posScreen.x), float(tileMapDispl.y + posScreen.y)));

}

void Screen::update(int deltaTime)
{
	sprite->update(deltaTime);

}

void Screen::render()
{
	sprite->render();
}

void Screen::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Screen::setPosition(const glm::vec2 &pos)
{
	posScreen = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posScreen.x), float(tileMapDispl.y + posScreen.y)));
}

glm::vec2 Screen::getPosition() {
	return posScreen;
}

void Screen::setView(int view) {
	sprite->changeAnimation(view);
}


