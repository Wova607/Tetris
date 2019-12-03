#pragma once
#include"Field.h"
#include"Tetroids.h"


class Game
{
	BaseFigure *tetroid;
	int speed;
	int level;
	int score;
	int nextLevel;  //к-сть очок для наступного левела
	string playerName;
	bool start; //для початкового зчитування таблички чемпіонів
	multimap<int,string> tablChemp;
	bool loadGame; //якщо гра загружається з файлика
	char newField[25][40]; //якщо зберігаємо гру то запишемо це поле

public:
	Game();
	void StartGame();  //основна ігрова функція
	int Menu();
	int Pause();
	void SaveGame(Field);
	void LoadGame();
	void TableChampion();  //загрузка вигрузка таблички чемпіонів
	void TableChampionShow();
	int GetLevel();
	int GetScore();
	void SetScore(int);
	string UsersMenu(set<string>);  //вибір збереженої гри
	~Game();
};
