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
	int realRow; //����ڰ� �Է��� ������ row
	int realCol; //����ڰ� �Է��� ������ col
	int row; //���� ���� �迭�� row
	int col; //���� ���� �迭�� col 
	int difficulty; //���̵� (�� : 3 �� : 2 �� : 1)
	int bomb; //������ ���� 
	int flag; // ��� �� ������ ĭ�� ����
	bool record = false; //�̾��ϱ� �� ���� ����� �ִ���
	int** map; //���ӿ� �̿�Ǵ� ��
	int** checkMap; // �ش� ĭ�� ������ ����� üũ�ϱ� ���� ��
	int** originalCheckMap; // ���� ���� �� checkMap�� ���� -> ���÷��̿� ���
	vector<pair<pair<int, int>, int>> replayxy; // Ž���� ĭ�� ��ǥ�� �Ӽ��� �����ϴ� ����
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

