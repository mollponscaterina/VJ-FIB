#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Text.h"
#include "Game.h"


enum TextAnims
{
	M, A, R, I, O, W, E, L, D, T, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, LINE, BIG, SMALL
};


void Text::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int c)
{
	spritesheet.loadFromFile("images/fonts.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(0.125, 0.125), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(23);

	sprite->setAnimationSpeed(M, 8);
	sprite->addKeyframe(M, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(A, 8);
	sprite->addKeyframe(A, glm::vec2(0.f, 0.125f));

	sprite->setAnimationSpeed(R, 8);
	sprite->addKeyframe(R, glm::vec2(0.f, 0.25f));

	sprite->setAnimationSpeed(I, 8);
	sprite->addKeyframe(I, glm::vec2(0.f, 0.375f));

	sprite->setAnimationSpeed(O, 8);
	sprite->addKeyframe(O, glm::vec2(0.125f, 0.f));

	sprite->setAnimationSpeed(W, 8);
	sprite->addKeyframe(W, glm::vec2(0.125f, 0.125f));

	sprite->setAnimationSpeed(E, 8);
	sprite->addKeyframe(E, glm::vec2(0.125f, 0.375f));

	sprite->setAnimationSpeed(L, 8);
	sprite->addKeyframe(L, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(D, 8);
	sprite->addKeyframe(D, glm::vec2(0.25f, 0.125f));

	sprite->setAnimationSpeed(T, 8);
	sprite->addKeyframe(T, glm::vec2(0.25f, 0.25f));

	sprite->setAnimationSpeed(ZERO, 8);
	sprite->addKeyframe(ZERO, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(ONE, 8);
	sprite->addKeyframe(ONE, glm::vec2(0.125f, 0.5f));

	sprite->setAnimationSpeed(TWO, 8);
	sprite->addKeyframe(TWO, glm::vec2(0.25f, 0.5f));

	sprite->setAnimationSpeed(THREE, 8);
	sprite->addKeyframe(THREE, glm::vec2(0.375f, 0.5f));

	sprite->setAnimationSpeed(FOUR, 8);
	sprite->addKeyframe(FOUR, glm::vec2(0.5f, 0.5f));

	sprite->setAnimationSpeed(FIVE, 8);
	sprite->addKeyframe(FIVE, glm::vec2(0.625f, 0.5f));

	sprite->setAnimationSpeed(SIX, 8);
	sprite->addKeyframe(SIX, glm::vec2(0.75f, 0.5f));

	sprite->setAnimationSpeed(SEVEN, 8);
	sprite->addKeyframe(SEVEN, glm::vec2(0.875f, 0.5f));

	sprite->setAnimationSpeed(SIX, 8);
	sprite->addKeyframe(SIX, glm::vec2(0.75f, 0.5f));

	sprite->setAnimationSpeed(SEVEN, 8);
	sprite->addKeyframe(SEVEN, glm::vec2(0.875f, 0.5f));

	sprite->setAnimationSpeed(EIGHT, 8);
	sprite->addKeyframe(EIGHT, glm::vec2(0.f, 0.625f));

	sprite->setAnimationSpeed(NINE, 8);
	sprite->addKeyframe(NINE, glm::vec2(0.125f, 0.625f));

	sprite->setAnimationSpeed(LINE, 8);
	sprite->addKeyframe(LINE, glm::vec2(0.25f, 0.625f));

	sprite->setAnimationSpeed(BIG, 8);
	sprite->addKeyframe(BIG, glm::vec2(0.375f, 0.625f));

	sprite->setAnimationSpeed(SMALL, 8);
	sprite->addKeyframe(SMALL, glm::vec2(0.5f, 0.625f));

	sprite->changeAnimation(c);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posText.x), float(tileMapDispl.y + posText.y)));

}

void Text::update(int deltaTime)
{
	sprite->update(deltaTime);
	
}

void Text::render()
{
	sprite->render();
}

void Text::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Text::setPosition(const glm::vec2 &pos)
{
	posText = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posText.x), float(tileMapDispl.y + posText.y)));
}

glm::vec2 Text::getPosition() {
	return posText;
}

void Text::setView(int view) {
	sprite->changeAnimation(view);
}


