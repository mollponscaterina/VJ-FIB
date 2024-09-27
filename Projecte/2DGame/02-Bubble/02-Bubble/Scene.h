#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "LoadEnemics.h"
#include "Player.h"
#include "Gommba.h"
#include "Koppa.h"
#include "Text.h"
#include "Bloc.h"
#include "Screen.h"
#include "Power.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	bool colisions(glm::vec2 pos1, glm::vec2 size1, glm::vec2 pos2, glm::vec2 size2);

	void ini_gommbas();
	void ini_koppas();
	void ini_text();
	void ini_blocs();
	void ini_powerups();
	void check_enemic_pos();
	void ckeck_colision_goomba();
	void ckeck_colision_koopa();
	void newLevel();
	void reset();

private:
	void initShaders();

private:
	TileMap *map;
	TileMap *map2;
	TileMap *col;
	LoadEnemics *enemics_g;
	TileMap *enemics_k;
	LoadEnemics *map_g;
	Player *player;
	Screen *screen1;
	Screen *screen2;
	Screen *screen3;
	Screen *screen4;
	Screen *screen5;
	Screen *screen6;
	Gommba *gommba;
	Power *power;
	Koppa *koppa;
	Text *text;
	Bloc *bloc;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	float posCam;
	

	int levelTime;
	int num_enemics;
	int num_text;
	int num_koppas;
	vector<Gommba*> gommbas;
	vector<Koppa*> koppas;
	vector<Text*> interficie;
	vector<Text*> interficie_dinamica;
	vector<int> posX_text;
	vector<int> posY_text;
	vector<int> posX_gomba;
	vector<int> posY_gomba;
	vector<int> posX_koppa;
	vector<float> posY_koppa;
	vector<int> contenido;
	vector<pair<int,int>> posBlocs;
	vector<pair<int, int>> posInte;
	vector<pair<int, int>> posCoins;
	vector<pair<int, int>> posMushs;
	vector<pair<int, int>> posStars;
	vector<Bloc*> inte;
	vector<Bloc*> rajo;
	vector<Power*> coin;
	vector<Power*> stars;
	vector<Power*> mushs;
	string gameState = "home1";
	int score = 0;
	int coins = 0;

};


#endif // _SCENE_INCLUDE

