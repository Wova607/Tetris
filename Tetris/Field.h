#pragma once
#include"Tetroids.h"




class Field
{
public:
	enum {sizeI=25, sizeJ=40};
	char field[sizeI][sizeJ];
	int countDestroyLine;  //к-сть ліній для знищення
	int startLine; //лінія з якої починати знищення

	Field();
	void Show(int,int);
	bool CanMoveLeft(BaseFigure *,int, int);
	bool CanMoveRight(BaseFigure*,int, int);
	void FrizzFigure(BaseFigure*, int, int);
	bool StopMove(BaseFigure*, int, int);
	bool DestroyLine();
	void CopyField();
};

class InfField
{
public:
	enum {sizeI=15, sizeJ=20};
	char field[sizeI][sizeJ];
	InfField();
	void Show(int, int, BaseFigure*, int,int);
	
};