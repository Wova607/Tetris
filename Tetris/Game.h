#pragma once
#include"Field.h"
#include"Tetroids.h"


class Game
{
	BaseFigure *tetroid;
	int speed;
	int level;
	int score;
	int nextLevel;  //�-��� ���� ��� ���������� ������
	string playerName;
	bool start; //��� ����������� ���������� �������� �������
	multimap<int,string> tablChemp;
	bool loadGame; //���� ��� ����������� � �������
	char newField[25][40]; //���� �������� ��� �� �������� �� ����

public:
	Game();
	void StartGame();  //������� ������ �������
	int Menu();
	int Pause();
	void SaveGame(Field);
	void LoadGame();
	void TableChampion();  //�������� �������� �������� �������
	void TableChampionShow();
	int GetLevel();
	int GetScore();
	void SetScore(int);
	string UsersMenu(set<string>);  //���� ��������� ���
	~Game();
};
