#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bloc.h"
#include "Game.h"


enum BlocAnims
{
	RAJ, INTE, INTE_HIT, RAJO_HIT
};


void Bloc::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int c)
{
	spritesheet.loadFromFile("images/blocs.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(RAJ, 8);
	sprite->addKeyframe(RAJ, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(RAJO_HIT, 8);
	sprite->addKeyframe(RAJO_HIT, glm::vec2(0.5f, 0.5f));

	sprite->setAnimationSpeed(INTE, 8);
	sprite->addKeyframe(INTE, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(INTE_HIT, 8);
	sprite->addKeyframe(INTE_HIT, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(c);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBloc.x), float(tileMapDispl.y + posBloc.y)));

}

void Bloc::update(int deltaTime)
{
	sprite->update(deltaTime);

}

void Bloc::render()
{
	sprite->render();
}

void Bloc::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Bloc::setPosition(const glm::vec2 &pos)
{
	posBloc = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBloc.x), float(tileMapDispl.y + posBloc.y)));
}

glm::vec2 Bloc::getPosition() {
	return posBloc;
}

void Bloc::setView(int view) {
	if (view == 2) state = "hit";
	sprite->changeAnimation(view);
}


string Bloc::getState() {
	return state;
}