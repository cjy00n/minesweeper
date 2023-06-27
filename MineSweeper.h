#pragma once
#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include <Windows.h>
using namespace std;
class MineSweeper 
{
private:
	int realRow; //사용자가 입력한 지뢰의 row
	int realCol; //사용자가 입력한 지뢰의 col
	int row; //실제 지뢰 배열의 row
	int col; //실제 지뢰 배열의 col 
	int difficulty; //난이도 (상 : 3 중 : 2 하 : 1)
	int bomb; //지뢰의 개수 
	int flag; // 깃발 중 지뢰인 칸의 개수
	bool record = false; //이어하기 할 게임 기록이 있는지
	int** map; //게임에 이용되는 맵
	int** checkMap; // 해당 칸이 선택이 됬는지 체크하기 위한 맵
	int** originalCheckMap; // 최초 생성 시 checkMap을 저장 -> 리플레이에 사용
	vector<pair<pair<int, int>, int>> replayxy; // 탐색한 칸의 좌표와 속성을 저장하는 벡터
public:
	MineSweeper() = default;
	~MineSweeper();
	void play(); 
	void startNewGame();
	void showMenu();
	void continueGame();
	void endGame();
	void makeInitialMap();
	void printMap();
	void playGame();
	void printAround(int m_row, int m_col, int**checkMap);
	void countAroundBomb();
	int selectable();
	int flagCount();
	void saveGame();
	void readGame();
	void replay();
	void printMine(const int m_row, const int m_col);

	void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	void setcolor(int color, int bgcolor)
	{
		color &= 0xf;
		bgcolor &= 0xf;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
	}

	void setCursorView(bool visible)
	{
		CONSOLE_CURSOR_INFO cursor = { 1, visible };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	}
	
};

