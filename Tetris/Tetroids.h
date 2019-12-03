#pragma once
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<string>
#include<map>
#include<fstream>
#include<iterator>
#include<set>



using namespace std;

void SetColor(int textColor, int bgColor);
void SetCoord(int x, int y);

class BaseFigure
{
public:
	enum {size=8};
	char **figure;
	int posRotation;  //варіант позиції фігури
		
	virtual void ShowFigure(int , int);
	virtual void ClearFigure(); //очищає фігуру
	virtual void DrowFigure() = 0; //заповнює фігуру
	virtual void CreateFigure();  //створює динамічний масив для фігури
	virtual void DestroyFigure(); //знищує масив
	
};



class Strip :public BaseFigure
{
public:
	Strip();
	void DrowFigure();
};

class Сorner :public BaseFigure
{
public:
	Сorner();
	void DrowFigure();
	void ShowFigure(int, int);
};

class Square :public BaseFigure
{
public:
	Square();
	void DrowFigure();
};

class Ze :public BaseFigure
{
public:
	Ze();
	void DrowFigure();
	void ShowFigure(int, int);
};

class Te :public BaseFigure
{
public:
	Te();
	void DrowFigure();
	void ShowFigure(int, int);
};




