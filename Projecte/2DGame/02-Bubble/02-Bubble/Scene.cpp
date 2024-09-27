#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
//#include "Sound.h"
#include <GL/glew.h>
#include <GL/glut.h>

#define X_RATIO 256
#define Y_RATIO 240

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 12

#define INIT_GOMMBA_X_TILES 15
#define INIT_GOMMBA_Y_TILES 11


#define INIT_KOPPA_X_TILES 13
#define INIT_KOPPA_Y_TILES 11


Scene::Scene()
{
	map = NULL;
	player = NULL;
	col = NULL;
	gommba = NULL;
	map_g = NULL;
	text = NULL;
	koppa = NULL;
}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	if (gommba != NULL)
		delete gommba;
	if (col != NULL)
		delete col;
	if (text != NULL)
		delete text;
	if (koppa != NULL)
		delete koppa;
}



void Scene::init()
{
	 posCam = 0.f;
	initShaders();
	col = TileMap::createTileMap("levels/colisions.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	map2 = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	//enemics_k = TileMap::createTileMap("levels/enemics_k.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	//enemics_g = LoadEnemics::createMapEnemics("levels/enemics_g.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "normal");
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(col);

	screen1 = new Screen();
	screen1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 0);
	screen1->setPosition(glm::vec2(SCREEN_X * map->getTileSize(), SCREEN_Y * map->getTileSize()));
	screen1->setTileMap(col);

	screen2 = new Screen();
	screen2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	screen2->setPosition(glm::vec2(SCREEN_X * map->getTileSize(), SCREEN_Y * map->getTileSize()));
	screen2->setTileMap(col);

	screen3 = new Screen();
	screen3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 2);
	screen3->setPosition(glm::vec2(SCREEN_X * map->getTileSize(), SCREEN_Y * map->getTileSize()));
	screen3->setTileMap(col);

	screen4 = new Screen();
	screen4->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 3);
	screen4->setPosition(glm::vec2(SCREEN_X * map->getTileSize(), SCREEN_Y * map->getTileSize()));
	screen4->setTileMap(col);

	screen5 = new Screen();
	screen5->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 4);
	screen5->setPosition(glm::vec2(SCREEN_X * map->getTileSize(), SCREEN_Y * map->getTileSize()));
	screen5->setTileMap(col);

	screen6 = new Screen();
	screen6->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 5);
	screen6->setPosition(glm::vec2(SCREEN_X * map->getTileSize(), SCREEN_Y * map->getTileSize()));
	screen6->setTileMap(col);

	ini_text();

	ini_gommbas();

	ini_koppas();

	ini_blocs();
	
	ini_powerups();

	projection = glm::ortho(posCam, float(X_RATIO) + posCam, float(Y_RATIO), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{

	if ((Game::instance().getKey('r') || Game::instance().getKey('R'))) {
		reset();
	}

	if ((Game::instance().getKey('i') || Game::instance().getKey('I'))) {
		reset();
		gameState = "instr";
		render();
	}

	if ((Game::instance().getKey('c') || Game::instance().getKey('C'))) {
		reset();
		gameState = "cred";
		render();
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_UP) && gameState == "home2") {
		gameState = "home1";
		render();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && gameState == "home1") {
		gameState = "home2";
		render();
	}
	else if (((Game::instance().getKey('a') || Game::instance().getKey('A')) && gameState == "home1") || (Game::instance().getKey('1'))) {
		reset();
		gameState = "lvl1";
		render();
	}
	else if (((Game::instance().getKey('a') || Game::instance().getKey('A')) && gameState == "home2") || (Game::instance().getKey('2'))) {
		reset();
		gameState = "lvl2";
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map2->getTileSize(), INIT_PLAYER_Y_TILES * map2->getTileSize()));
		player->setTileMap(map2);
		render();
	}
	else if (gameState == "timeUp") {
		reset();
		gameState = "timeUp";
		render();
	}
	else if (gameState == "win" || gameState == "dead") {
		reset();
		gameState = "dead";
		render();
	}

	else if (gameState == "lvl1"){
		//Sound::instance().playLevel(1);
		if (player->getPosition().x == 3136) {
			if (player->getPosition().y < 80) score += 5000;
			else if (player->getPosition().y < 100) score += 2500;
			else if (player->getPosition().y < 120) score += 1250;
			else if (player->getPosition().y < 140) score += 625;
			gameState = "win";
		}
		currentTime += deltaTime;
		levelTime = 160 - currentTime / 1000;
		if (levelTime == 0) gameState = "timeUp";
		if (player->getLife() == "dead") gameState = "dead";
		

		projection = glm::ortho(player->getChange(), player->getChange() + float(X_RATIO), float(Y_RATIO), 0.f);
		player->update(deltaTime);
		player->move();

		for (int i = 0; i < posBlocs.size(); ++i) {
			if (rajo[i]->getPosition().x < player->getPosition().x && rajo[i]->getPosition().x + 16 > player->getPosition().x && (rajo[i]->getPosition().y + 57 == player->getPosition().y || rajo[i]->getPosition().y + 45 == player->getPosition().y) && player->getState() != "normal") {
				rajo[i]->setView(3);
			}
			rajo[i]->update(deltaTime);

		}

		for (int i = 0; i < posInte.size(); ++i) {
			if ((inte[i]->getPosition().x < player->getPosition().x) && (inte[i]->getPosition().x + 16 > player->getPosition().x) && (inte[i]->getPosition().y + 57 == player->getPosition().y || inte[i]->getPosition().y + 45 == player->getPosition().y)) {
				inte[i]->setView(2);
			}
			inte[i]->update(deltaTime);
		}

		for (int i = 0; i < posCoins.size(); ++i) {
			coin[i]->update(deltaTime);
			if (colisions(player->getPosition(), player->getTam(), coin[i]->getPosition(), glm::vec2(16, 16)) && coin[i]->getState() != "hit") {
				coins++;
				score += 200;
				coin[i]->setView(2);
			}
			
		}

		for (int i = 0; i < posStars.size(); ++i) {
			stars[i]->update(deltaTime);
			if (colisions(player->getPosition(), player->getTam(), stars[i]->getPosition(), glm::vec2(16, 16)) && stars[i]->getState() != "hit") {
				player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "star");
				score += 1000;
				stars[i]->setView(2);
			}

		}

		for (int i = 0; i < posMushs.size(); ++i) {
			if (colisions(player->getPosition(), player->getTam(), mushs[i]->getPosition(), glm::vec2(16, 16)) && mushs[i]->getState() != "hit") {
				player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "super");
				score += 1000;
				mushs[i]->setView(2);
			}
			mushs[i]->update(deltaTime);
		}

		//Text
		for (int i = 0; i < num_text; ++i) {
			interficie[i]->update(deltaTime);
			interficie[i]->setPosition(glm::vec2(posX_text[i] * 9 + player->getChange(), posY_text[i]));
		}

		if (levelTime > 0) {
			interficie_dinamica[interficie_dinamica.size() - 3]->setView((levelTime / 100) % 10 + 10);
			interficie_dinamica[interficie_dinamica.size() - 2]->setView((levelTime / 10) % 10 + 10);
			interficie_dinamica[interficie_dinamica.size() - 1]->setView((levelTime % 10) + 10);
		}
		else {
			interficie_dinamica[interficie_dinamica.size() - 3]->setView(10);
			interficie_dinamica[interficie_dinamica.size() - 2]->setView(10);
			interficie_dinamica[interficie_dinamica.size() - 1]->setView(10);
		}

		if (coins > 0) {
			interficie_dinamica[interficie_dinamica.size() - 6]->setView((coins % 10) + 10);
			interficie_dinamica[interficie_dinamica.size() - 7]->setView((coins / 10) % 10 + 10);
		}

		interficie_dinamica[interficie_dinamica.size() - 8]->setView((score % 10) + 10);
		interficie_dinamica[interficie_dinamica.size() - 9]->setView((score / 10) % 10 + 10);
		interficie_dinamica[interficie_dinamica.size() - 10]->setView((score / 100) % 10 + 10);
		interficie_dinamica[interficie_dinamica.size() - 11]->setView((score / 1000) % 10 + 10);
		interficie_dinamica[interficie_dinamica.size() - 12]->setView((score / 10000) % 10 + 10);
		interficie_dinamica[interficie_dinamica.size() - 13]->setView((score / 100000) % 10 + 10);
		
		check_enemic_pos(); //per fer que es començin a moure quan el mario esta aprop

							//GOMMBAS COLICIONS
		for (int i = 0; i < num_enemics; ++i) {
			if (gommbas[i] != NULL) {
				ckeck_colision_goomba();
			}
		}

		//GOOMBAS
		for (int i = 0; i < num_enemics; ++i) {
			if (gommbas[i]->alive) {
				gommbas[i]->update(deltaTime);
			}
		}

		//COLISIONS KOPPA AMB GOMMBA
		for (int i = 0; i < num_enemics; ++i) {
			for (int j = 0; j < num_koppas; ++j) {
				if (gommbas[i]->alive && colisions(koppas[j]->getPosition(), koppas[j]->getTam(), gommbas[i]->getPosition(), gommbas[i]->getTam())) {
					if (koppas[j]->shell) {
						gommbas[i]->achafatKoppa();
						gommbas[i]->dieTime = currentTime;
					}
					else {
						gommbas[i]->changeMov();
						koppas[j]->changeMov();
						printf("gombas koppa");
					}

				}
			}
		}





		//KOPPA
		for (int i = 0; i < num_koppas; ++i) {
			if (koppas[i]->alive && koppas[i] != NULL)
				ckeck_colision_koopa(); //KOPPA -MARIO COLISION
		}
		for (int i = 0; i < num_koppas; ++i) {
			if (koppas[i]->alive) {
				koppas[i]->update(deltaTime);
				//colisions_mario_enemic(player->getPosition(), 16, 16, koppa->getPosition(), 16, 24, -1);
			}
		}
	}

	else if (gameState == "lvl2") {
	//	Sound::instance().playLevel(2);
		currentTime += deltaTime;
		levelTime = 160 - currentTime / 1000;
		if (levelTime == 0) gameState = "timeUp";
		if (player->getLife() == "dead") gameState = "dead";

		projection = glm::ortho(player->getChange(), player->getChange() + float(X_RATIO), float(Y_RATIO), 0.f);
		player->update(deltaTime);
		player->move();

		//Text
		for (int i = 0; i < num_text; ++i) {
			interficie[i]->update(deltaTime);
			interficie[i]->setPosition(glm::vec2(posX_text[i] * 9 + player->getChange(), posY_text[i]));
		}

		if (levelTime > 0) {
			interficie_dinamica[interficie_dinamica.size() - 3]->setView((levelTime / 100) % 10 + 10);
			interficie_dinamica[interficie_dinamica.size() - 2]->setView((levelTime / 10) % 10 + 10);
			interficie_dinamica[interficie_dinamica.size() - 1]->setView((levelTime % 10) + 10);
		}
		else {
			interficie_dinamica[interficie_dinamica.size() - 3]->setView(10);
			interficie_dinamica[interficie_dinamica.size() - 2]->setView(10);
			interficie_dinamica[interficie_dinamica.size() - 1]->setView(10);
		}
		if (coins > 0) {
			interficie_dinamica[interficie_dinamica.size() - 6]->setView((coins % 10) + 10);
			interficie_dinamica[interficie_dinamica.size() - 7]->setView((coins / 10) % 10 + 10);
		}

		interficie_dinamica[interficie_dinamica.size() - 8]->setView((score % 10) + 10);
		interficie_dinamica[interficie_dinamica.size() - 9]->setView((score / 10) % 10 + 10);
		interficie_dinamica[interficie_dinamica.size() - 10]->setView((score / 100) % 10 + 10);
		interficie_dinamica[interficie_dinamica.size() - 11]->setView((score / 1000) % 10 + 10);
		interficie_dinamica[interficie_dinamica.size() - 12]->setView((score / 10000) % 10 + 10);
		interficie_dinamica[interficie_dinamica.size() - 13]->setView((score / 100000) % 10 + 10);
		//GOOMBAS
		check_enemic_pos(); //per fer que es començin a moure quan el mario esta aprop
		ckeck_colision_goomba();
		for (int i = 0; i < num_enemics; ++i) {
			if (gommbas[i]->alive) {
				gommbas[i]->update(deltaTime);
			}
		}

		//COLISIONS KOPPA AMB GOMMBA
		for (int i = 0; i < num_enemics; ++i) {
			for (int j = 0; j < num_koppas; ++j) {
				if (gommbas[i]->alive && colisions(koppas[j]->getPosition(), koppas[j]->getTam(), gommbas[i]->getPosition(), gommbas[i]->getTam())) {
					if (koppas[j]->shell) {
						gommbas[i]->achafatKoppa();
						gommbas[i]->dieTime = currentTime;
					}
					else {
						gommbas[i]->changeMov();
						koppas[j]->changeMov();
						printf("gombas koppa");
					}

				}
			}
		}

		//KOPPA
		ckeck_colision_koopa();

		for (int i = 0; i < num_koppas; ++i) {
			if (koppas[i]->alive) {
				koppas[i]->update(deltaTime);
			}
		}
	}
	
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	if (gameState == "home1") {
		screen1->render();
	}
	else if (gameState == "home2") {
		screen2->render();
	}
	else if  (gameState == "lvl1"){
		map->render();
		//col->render();
		player->render();


		for (int i = 0; i < num_enemics; ++i) {
			if (gommbas[i]->alive) {
				gommbas[i]->render();
			}
		}

		for (int i = 0; i < num_koppas; ++i) {
			if (koppas[i]->alive) {
				koppas[i]->render();
			}
		}

		for (int i = 0; i < posCoins.size(); ++i) {
			coin[i]->render();
		}

		for (int i = 0; i < posMushs.size(); ++i) {
			mushs[i]->render();
		}

		for (int i = 0; i < posBlocs.size(); ++i) {
			rajo[i]->render();
		}

		for (int i = 0; i < posInte.size(); ++i) {
			inte[i]->render();
		}

		for (int i = 0; i < posStars.size(); ++i) {
			stars[i]->render();
		}

		for (int i = 0; i < num_text; ++i) {
			interficie[i]->render();
		}
	}
	else if (gameState == "lvl2") {
		map2->render();
		//col->render();
		player->render();


		for (int i = 0; i < num_enemics; ++i) {
			if (gommbas[i]->alive) {
				gommbas[i]->render();
			}
		}

		for (int i = 0; i < num_koppas; ++i) {
			if (koppas[i]->alive) {
				koppas[i]->render();
			}
		}

		for (int i = 0; i < num_text; ++i) {
			interficie[i]->render();
		}
	}
	else if (gameState == "timeUp") {
		screen3->render();
	}
	else if (gameState == "dead" || gameState == "win") {
		screen4->render();
	}
	else if (gameState == "cred") {
		screen5->render();
	}
	else if (gameState == "instr") {
		screen6->render();
	}
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

bool Scene::colisions(glm::vec2 pos1, glm::vec2 size1, glm::vec2 pos2, glm::vec2 size2)
{
	int minXM = pos1.x;
	int maxXM = pos1.x + size1.x;
	int minYM = pos1.y;
	int maxYM = pos1.y + size1.x;

	int minXG = pos2.x;
	int maxXG = pos2.x + size2.x; //32
	int minYG = pos2.y;
	int maxYG = pos2.y + size2.x; //48

	if ((minXM < maxXG) && (minXG < maxXM) && (minYM <= maxYG) && (minYG <= maxYM))
	{
		/*if (minYM < minYG) { //s'hauria d afegir condicio que si esta com començant a saltar es mori que quan salta cap a dalt el mata

		//printf(" KOPPA ");
		if (num_goomba != -1) {//passem -1 quan es un koppa
		gommbas[num_goomba]->achafat();
		gommbas[num_goomba]->timeDie = currentTime;
		}
		else {
		koppa->achafat();
		koppa->timeDie = currentTime;
		}
		}
		else {
		printf(" MARIO MOR");
		player->death_animation();

		//s ha de cridar a gameOVer i fer que el joc pari i surti pantalla de menys una vida

		}
		*/

		return true;
	}
	return false;
}

void Scene::ini_gommbas() {
	//int num_enemics = 20;
	gommbas.clear();
	posX_gomba = { 7, 20, 37, 50, 53, 70, 76, 79, 100, 104, 106, 120, 130, 132, 148, 150, 160, 173, 190 };
	num_enemics = posX_gomba.size();
	posY_gomba = { 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11 };

	for (int i = 0; i < num_enemics; ++i) {
		gommba = new Gommba();
		gommba->init(glm::ivec2(0.f, 16.f), texProgram);
		gommba->setPosition(glm::vec2((posX_gomba[i])*map->getTileSize(), ((posY_gomba[i])*map->getTileSize())));
		gommba->setTileMap(col);
		gommbas.push_back(gommba);
	}
}

void Scene::check_enemic_pos() {

	for (int i = 0; i < num_enemics; ++i) {
		if (!gommbas[i]->start && ((gommbas[i]->getPosition().x) - (player->getPosition().x) <= 160)) {
			gommbas[i]->alive = true;
			gommbas[i]->start = true;
			printf(" comença gomba %d ", i);
		}
	}

	for (int i = 0; i < num_koppas; ++i) {

		if (!koppas[i]->start && ((koppas[i]->getPosition().x) - (player->getPosition().x) <= 160)) {
			koppas[i]->alive = true;
			koppas[i]->start = true;
		}

	}

}

void Scene::ckeck_colision_goomba() {

	for (int i = 0; i < num_enemics; ++i) {
		/// <summary>
		/// COLISIONS GOMMBA MARIO -> FALTA AFEGIR Q MARIO MORI
		/// </summary>
		if (gommbas[i]->alive && colisions(player->getPosition(), player->getTam(), gommbas[i]->getPosition(), gommbas[i]->getTam()) && gommbas[i]->hitted() == 0 && player->getState() != "star") { 	//comprovem col.lisions
			if (player->getPosition().y <= gommbas[i]->getPosition().y) {
				gommbas[i]->achafat();
				gommbas[i]->dieTime = currentTime;
				score += 2000;
				gommbas[i]->isHit();
				//printf("GOMBA %d MOOR ", i);
				//player->jump();
			}

			else {
				//mario mor
				if (player->getState() == "normal") player->mort();
				else {
					player->setState("normal");
				}
			}


		}

		/// <summary>
		/// COLISIONS GOMMBA - GOMMBA
		/// </summary>
		for (int j = 0; j < num_enemics; ++j) {
			if (i != j && gommbas[i]->alive && colisions(gommbas[j]->getPosition(), gommbas[j]->getTam(), gommbas[i]->getPosition(), gommbas[i]->getTam())) { 	//comprovem col.lisions
				gommbas[i]->changeMov();
				gommbas[j]->changeMov();
			}
		}

		if (gommbas[i]->alive && (currentTime - gommbas[i]->dieTime) > 150.f) //per fer que es desaparegui 2 segons més tard 
			gommbas[i]->alive = false;

	}

}


void Scene::ckeck_colision_koopa() {
	/// <summary>

	/// </summary>
	for (int j = 0; j < num_koppas; ++j) {
		if (!koppas[j]->shell) {
			/// KOPPA (VIU) - MARIO
			if (colisions(player->getPosition(), player->getTam(), koppas[j]->getPosition(), koppas[j]->getTam()) && !koppas[j]->shell && player->getState() != "star") { 	//comprovem col.lisions
				if (player->getPosition().y <= koppas[j]->getPosition().y) { //xoquen mario per dalt
					koppas[j]->achafat();
					koppas[j]->dieTime = currentTime;
					player->setPosition(glm::vec2(player->getPosition().x, player->getPosition().y-16));
					score += 2000;
				}

				else {
					if (player->getState() == "normal") player->mort();
					else {
						player->setState("normal");
					}
				}

			}

		}

		else {
			if (koppas[j]->alive && colisions(player->getPosition(), player->getTam(), koppas[j]->getPosition(), glm::vec2(16, 8))) { 	//comprovem col.lisions
				if (player->getPosition().y + player->getTam().y / 2.f <= koppas[j]->getPosition().y) { //xoquen mario per dalt
					koppas[j]->movimentClosca(player->getPosition().x > koppas[j]->getPosition().x);

				}
				else if (player->getPosition().y > koppas[j]->getPosition().y) { // si xoca pel costat, suposem que el mata
					player->mort();
				}
			}
		}

		for (int k = 0; k < num_koppas; ++k) {
			if (koppas[k]->alive && k != j && colisions(koppas[j]->getPosition(), koppas[j]->getTam(), koppas[k]->getPosition(), koppas[k]->getTam())) { //comprovem col.lisions
				if (koppas[j]->shell && koppas[k]->shell || !koppas[j]->shell && !koppas[k]->shell) {
					koppas[k]->changeMov();
					koppas[j]->changeMov();
				}
				else if (koppas[j]->shell && !koppas[k]->shell) {
					koppas[k]->mortKoppa();
					koppas[j]->movimentClosca(koppas[k]->getPosition().x > koppas[j]->getPosition().x);
				}
			}

		}

	}





	//if ((currentTime - koppa->dieTime) > 160.f) //per fer que es desaparegui 2 segons més tard 
	//	koppa->alive = false;
}

void Scene::ini_koppas() {
	koppas.clear();
	posX_koppa = { 13, 162, 83 };
	posY_koppa = { 11.5, 11.5, 11.5 };
	num_koppas = 3;
	for (int i = 0; i < num_koppas; ++i) {
		koppa = new Koppa();
		koppa->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		koppa->setPosition(glm::vec2((posX_koppa[i])*map->getTileSize(), (posY_koppa[i])*map->getTileSize()));
		koppa->setTileMap(col);
		koppas.push_back(koppa);
	}

}

void Scene::ini_text() {
	interficie.clear();
	interficie_dinamica.clear();
	posX_text = {1, 2, 3, 4, 5, 6 + 10, 7 + 10, 8 + 10, 9 + 10, 10 + 10,  11 + 12, 12 + 12, 13 + 12, 14 + 12, 1, 2, 3, 4, 5, 6, 6 + 3, 7 + 3, 8 + 3, 9 + 3,  6 + 10, 7 + 10, 8 + 10,  12 + 12, 13 + 12, 14 + 12 };
	num_text = posX_text.size();
	posY_text = {-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
	contenido = {0, 1, 2, 3, 4, 5, 4, 2, 7, 8, 9, 3, 0, 6, 10, 10, 10, 10, 10, 10, 21, 22, 10, 10, 11, 20, 11, 10, 10, 10};


	for (int i = 0; i < num_text; ++i) {
		text = new Text();
		text->init(glm::ivec2(0.f, 16.f), texProgram, contenido[i]);
		text->setPosition(glm::vec2(posX_text[i]*9, posY_text[i]));
		text->setTileMap(col);
		interficie.push_back(text);
		if (i > 13 && i != 20 && i != 21 && i != 25) interficie_dinamica.push_back(text);
	}
}

void Scene::ini_blocs() {
	rajo.clear();
	inte.clear();

	posInte = { { 11,9 },{ 26,6 },{ 50,6 },{ 79,2 },{ 90,5 },{ 110,9 },{ 119, 9 },{ 122, 6 },{ 124, 9 },{ 133, 2 },{ 178, 9 } };
	posBlocs = { { 11,9 },{ 14,9 },{ 15,9 },{ 16,9 },{ 19,9 },{ 20,9 },{ 21,9 },{ 23,6 },{ 24,6 },{ 25,6 },{ 46,9 },{ 47,9 },{ 48,9 } ,{ 49,9 },{ 64,10 },{ 65,10 },{ 66,10 },{ 69,8 },{ 70,8 },{ 71,8 },{ 72,8 },{ 73,5 },{ 74,4 },{ 75,4 },{ 76,4 },{ 74,5 },{ 75,5 },{ 76,5 },{ 77,5 },{ 78,5 },{ 79,5 },{ 80,5 },{ 81,5 },{ 82,5 },{ 86,5 },{ 87,5 },{ 88,5 },{ 89,5 },{ 102,10 },{ 103,10 },{ 104,10 },{ 105,10 },{ 106,10 },{ 122, 9 },{ 128, 9 },{ 131, 6 },{ 132, 6 },{ 133, 6 },{ 134, 6 },{ 135, 6 } ,{ 136, 6 },{ 177, 9 } };


	for (int i = 0; i < posBlocs.size(); ++i) {
		bloc = new Bloc();
		bloc->init(glm::ivec2(16.f, 16.f), texProgram, 0);
		bloc->setPosition(glm::vec2((posBlocs[i].first-1) *map->getTileSize(), (posBlocs[i].second-1)*map->getTileSize()));
		bloc->setTileMap(col);
		rajo.push_back(bloc);
	}

	for (int i = 0; i < posInte.size(); ++i) {
		bloc = new Bloc();
		bloc->init(glm::ivec2(16.f, 16.f), texProgram, 1);
		bloc->setPosition(glm::vec2((posInte[i].first-1)*map->getTileSize(), (posInte[i].second-1)*map->getTileSize()));
		bloc->setTileMap(col);
		inte.push_back(bloc);
	}
}

void Scene::ini_powerups() {
	coin.clear();
	mushs.clear();
	stars.clear();

	posCoins = { { 14,8},{ 50,5 } ,{ 90,4 } ,{ 106,9 } ,{ 121,8 } };
	posMushs = { { 79,1},{ 124,8 }};
	posStars = { { 16,8},{ 106,9 } };

	for (int i = 0; i < posCoins.size(); ++i) {
		power = new Power();
		power->init(glm::ivec2(16.f, 16.f), texProgram, 1);
		power->setPosition(glm::vec2((posCoins[i].first - 1) *map->getTileSize(), (posCoins[i].second - 1)*map->getTileSize()));
		power->setTileMap(col);
		coin.push_back(power);
	}

	for (int i = 0; i < posMushs.size(); ++i) {
		power = new Power();
		power->init(glm::ivec2(16.f, 16.f), texProgram, 0);
		power->setPosition(glm::vec2((posMushs[i].first - 1)*map->getTileSize(), (posMushs[i].second - 1)*map->getTileSize()));
		power->setTileMap(col);
		mushs.push_back(power);
	}

	for (int i = 0; i < posStars.size(); ++i) {
		power = new Power();
		power->init(glm::ivec2(16.f, 16.f), texProgram, 3);
		power->setPosition(glm::vec2((posStars[i].first - 1)*map->getTileSize(), (posStars[i].second - 1)*map->getTileSize()));
		power->setTileMap(col);
		stars.push_back(power);
	}
}

void Scene::reset() {
	gameState = "home1";
	coins = 0;
	score = 0;
	currentTime = 0;
	init();
}