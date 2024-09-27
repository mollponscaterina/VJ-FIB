#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, DIE
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, string type)
{
	tileMapDispl = tileMapPos;
	shader = shaderProgram;
	state = type;

	if (type == "super") {
		desviacio = 16;
		tam = glm::vec2(16, 16);
		spritesheet.loadFromFile("images/supermario.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y - desviacio)));
		desviacio = 16;
	}
	else if (type == "star") {
		desviacio = 16;
		tam = glm::vec2(16, 16);
		spritesheet.loadFromFile("images/starmario.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y - desviacio)));

	}
	else
	{
		desviacio = 0;
		tam = glm::vec2(16, 16);
		spritesheet.loadFromFile("images/mario.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y - desviacio)));

	}
	bJumping = false;


	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	sprite->setNumberAnimations(7);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));


	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.5f));

	sprite->setAnimationSpeed(JUMP_LEFT, 8);
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.f, 0.75f));

	sprite->setAnimationSpeed(JUMP_RIGHT, 8);
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.25f, 0.75f));

	sprite->setAnimationSpeed(DIE, 8);
	sprite->addKeyframe(DIE, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(0);


}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getKey('z') || Game::instance().getKey('Z')) {

	}

	if (Game::instance().getKey('m') || Game::instance().getKey('M')) {
		init(tileMapDispl, shader, "super");
	}

	if (Game::instance().getKey('g') || Game::instance().getKey('G')) {
		init(tileMapDispl, shader, "star");
	}

	if (!bJumping && sprite->animation() == JUMP_LEFT) sprite->changeAnimation(STAND_LEFT);
	if (!bJumping && sprite->animation() == JUMP_RIGHT) sprite->changeAnimation(STAND_RIGHT);

	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (posPlayer.x > change) {
			if (Game::instance().getKey('z') || Game::instance().getKey('Z')) moveLeft(2);
			else moveLeft(1);
		}
		else {
			velocitat = 0;
		}
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (Game::instance().getKey('z') || Game::instance().getKey('Z')) moveRight(2);
		else moveRight(1);
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		if (sprite->animation() == STAND_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
		if (sprite->animation() == STAND_LEFT) sprite->changeAnimation(JUMP_LEFT);
	}

	else
	{
		if (posPlayer.x > change) {
			stopMoving();
		}
		else {
			velocitat = 0;
		}
	}

	if (bJumping)
	{
		jump();
	}

	else
	{
		handleJumpAndGravity();
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	if (posPlayer.y > 223)
	{
		// Reset Mario's position and camera
		// posPlayer = glm::vec2(float(64), float(192)); // Reset Mario's starting position
		// change = 0; // Reset the camera position
		//sprite->changeAnimation(DIE);
		life = "dead";
	}
}

void Player::moveLeft(int n) {
	if (n == 2 && acceleracio == 0.1f) {
		acceleracio = 0.2f;
		vMax = 3.f;
	}
	else if (n == 1 && acceleracio == 0.2f) {
		acceleracio = 0.1f;
		velocitat = 2.f;
		vMax = 2.f;
	}
	if (bJumping) sprite->changeAnimation(JUMP_LEFT);
	else if (sprite->animation() != MOVE_LEFT)
		sprite->changeAnimation(MOVE_LEFT);
	if (velocitat > -vMax) velocitat -= acceleracio;
	else velocitat = velocitat;
	if (map->collisionMoveLeft(posPlayer + glm::ivec2(-2, 0), glm::ivec2(16, 16)))
	{
		velocitat = 0;
		sprite->changeAnimation(STAND_LEFT);
	}
}

void Player::moveRight(int n) {
	//cambiar velocitat, acc, vmax
	if (n == 2 && acceleracio == 0.1f) {
		acceleracio = 0.2f;
		vMax = 3.f;
	}
	else if (n == 1 && acceleracio == 0.2f) {
		acceleracio = 0.1f;
		velocitat = 2.f;
		vMax = 2.f;
	}
	if ((change + 130) < posPlayer.x) change += velocitat;
	if (bJumping) sprite->changeAnimation(JUMP_RIGHT);
	else if (sprite->animation() != MOVE_RIGHT)
		sprite->changeAnimation(MOVE_RIGHT);
	if (velocitat < float(vMax)) velocitat += acceleracio;
	else velocitat = velocitat;
	if (map->collisionMoveRight(posPlayer + glm::ivec2(2, 0), glm::ivec2(16, 16)))
	{
		velocitat = 0;
		sprite->changeAnimation(STAND_RIGHT);
	}
}

void Player::stopMoving() {
	if (map->collisionMoveRight(posPlayer + glm::ivec2(2, 0), glm::ivec2(16, 16)) || map->collisionMoveLeft(posPlayer + glm::ivec2(-2, 0), glm::ivec2(16, 16)))
	{
		velocitat = 0;
	}

	if (velocitat > 0)
	{
		sprite->changeAnimation(STAND_RIGHT);
	}
	else if (velocitat < 0)
	{
		sprite->changeAnimation(STAND_LEFT);
	}


	if (abs(velocitat) < 0.1f)
	{
		velocitat = 0.0f;
	}
	else
	{
		if (velocitat > 0)
		{
			velocitat -= acceleracio;
		}
		else if (velocitat < 0)
		{
			velocitat += acceleracio;
		}
	}
}

void Player::jump() {
	if (sprite->animation() == STAND_LEFT) sprite->changeAnimation(JUMP_LEFT);
	if (sprite->animation() == STAND_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
	jumpAngle += JUMP_ANGLE_STEP;
	if (jumpAngle == 180)
	{
		bJumping = false;
		posPlayer.y = startY;
	}
	else
	{
		posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
		if (jumpAngle > 90)
			bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(16, 16), &posPlayer.y, desviacio);
		else if (jumpAngle <= 90)
			bJumping = !map->collisionMoveUp(posPlayer, glm::ivec2(16, 16), &posPlayer.y);
	}
}

void Player::handleJumpAndGravity() {
	posPlayer.y += FALL_STEP;
	if (map->collisionMoveDown(posPlayer, glm::ivec2(16, 16), &posPlayer.y, desviacio))
	{
		if (Game::instance().getSpecialKey(GLUT_KEY_UP))
		{
			bJumping = true;
			jumpAngle = 0;
			startY = posPlayer.y;
		}
	}
}

void Player::death_animation() {
	if (sprite->animation() != DIE) sprite->changeAnimation(DIE);

	if (!falling) {
		// Gradually make Mario rise
		if (posPlayer.y > 174.0f) {
			posPlayer.y -= 2.0f;
		}
		else {
			falling = true;
		}
	}
	else if (falling) {
		// Gradually make Mario descend
		posPlayer.y += 2.0f;
	}
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

float Player::getChange() {
	return change;
}

void Player::move() {
	posPlayer.x += velocitat;
}

glm::vec2 Player::getPosition() {
	return posPlayer;
}

int Player::getVel() {
	return velocitat;
}

glm::vec2 Player::getTam() {
	return tam;
}

string Player::getState() {
	return state;
}
bool Player::blocCollision() {
	return map->collisionMoveUp(posPlayer, glm::ivec2(16, 16), &posPlayer.y);
}

string Player::getLife() {
	return life;
}

void Player::mort() {
	sprite->changeAnimation(DIE);
	life = "dead";
}

void Player::setState(string s) {
	init(tileMapDispl, shader, s);
}