#include "MineSweeper.h"

const int BOMB = -1;
const int NOTBOMB = -2;
const int TEMP = -3;
const int FLAG = -4;
const int CFLAG = -5;

MineSweeper::~MineSweeper()
{
	for (int i = 0; i < row; i++) {
		delete[]  map[i];
	}
	delete[] map;

	for (int i = 0; i < row; i++) {
		delete[]  checkMap[i];
	}
	delete[] checkMap;

	for (int i = 0; i < row; i++) {
		delete[]  originalCheckMap[i];
	}
	delete[] originalCheckMap;
}

// ���� ȭ�� ����
void MineSweeper::play()
{
	system("mode con:cols=40 lines=30");
	setCursorView(false);
	cout << "�й� : 201911288 �̸� : ������" << endl;
	gotoxy(0, 4);
	setcolor(9, 0);
	cout << "\t      �� �� �� ��" << endl;
	setcolor(10, 0);
	cout << "\t  �� �� �� �� �� �� ��" << endl << endl;
	setcolor(15, 0);
	cout << "  ============ ���� ���� =============" << endl;
	cout << "   ����Ű�� �̿��� ���ڸ� ã�� ����" << endl;
	cout << "   ��� ���� ĭ�� ����� ����� WIN " << endl;
	cout << "        ���ڸ� �����ϸ� LOSE" << endl;
	cout << "\n\t  < �� ���� ���� >" << endl;
	cout << " \n * ���� ���� ���� �Է°���" << endl;
	cout << " * ���̵� �� / �� / �� ���� ����" << endl;
	cout << "  ���� ���� : 30 %(��) 20 %(��) 10 %(��)" << endl << endl;
	cout << "\n\t  < ���� �̾��ϱ�>" << endl;
	cout << " \n * ������ ����Ǹ鼭 �ڵ����� ����" << endl;
	cout << " * ���� ���� �� �̾��ϱ� : \n\t���� �������� �̾��ϱ� ����" << endl;
	setcolor(12, 0);
	cout << "\n\n\tPress Enter to Start!" << endl;
	while (true) {
		int ch = _getch();
		if (ch == 13) {
			break;
		}
	}
	showMenu();
}

//�޴� ȭ��
void MineSweeper::showMenu()
{
	setcolor(15, 0);
	system("mode con:cols=40 lines=30");
	system("cls");
	setCursorView(true);
	cout << "�й� : 201911288 �̸� : ������\n\n";
	gotoxy(0, 4);
	setcolor(9, 0);
	cout << "\t      �� �� �� ��" << endl;
	setcolor(10, 0);
	cout << "\t  �� �� �� �� �� �� ��\n\n";
	setcolor(3, 0);
	cout << "\t�ڡڡ�  M E N U  �ڡڡ�" << endl;
	setcolor(15, 0);
	cout << "\t�� ���ο� ���� �����ϱ�\n";
	cout << "\t�� ���� �̾��ϱ�" << endl;
	cout << "\t�� ���� �����ϱ�" << endl;
	cout << "\n\t     ��    ��    ��";
	gotoxy(13, 12);
	int x = 13;
	while (true) {
		int ch = _getch();
		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 75: // left
				if (x >= 19)
					x -= 6;
				break;
			case 77: // right
				if (x <= 19)
					x += 6;
				break;
			}
			gotoxy(x, 12);
		}
		if (ch == 13) {
			break;
		}
	}
	if (x == 13) {
		startNewGame();
	}
	else if (x == 19) {
		continueGame();
	}
	else if (x == 25) {
		endGame();
	}
}

//�� ���� ����
void MineSweeper::startNewGame()
{
	replayxy.clear();
	cout << "\n\n\t���� ũ�⸦ �Է����ּ���." << endl;
	cout << "\n\t\t���� : ";
	cin >> realCol;
	col = realCol + 2;
	cout << "\t\t���� : ";
	cin >> realRow;
	row = realRow + 2;
	cout << "\n\t���̵��� �������ּ���." << endl;
	cout << "\n\t     ��    ��    ��";
	gotoxy(13, 21);
	int x = 13;
	while (true) {
		int ch = _getch();
		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 75: // left
				if (x >= 19)
					x -= 6;
				break;
			case 77: // right
				if (x <= 19)
					x += 6;
				break;
			}
			gotoxy(x, 21);
		}
		if (ch == 13) {
			break;
		}
	}
	if (x == 13) {
		difficulty = 3;
		bomb = realRow * realCol * 0.3;
	}
	else if (x == 19) {
		difficulty = 2;
		bomb = realRow * realCol * 0.2;
	}
	else if (x == 25) {
		difficulty = 1;
		bomb = realRow * realCol * 0.1;
	}

	cout << "\n\n\t��� �� ������ ���۵˴ϴ�" << endl;
	Sleep(1000);
	makeInitialMap();
	printMap();
	playGame();
}

//���� �̾��ϱ�
void MineSweeper::continueGame()
{
	readGame();
	if (this->record == true) {
		printMap();
		playGame();
	}
	else {
		setCursorView(false);
		system("mode con:cols=40 lines=30");
		system("cls");
		setcolor(15, 0);
		cout << "�й� : 201911288 �̸� : ������" << endl;
		cout << "\n\n\n\n  �̾��ϱ� ������ ���� ����� �����ϴ�." << endl;
		setcolor(12, 0);
		cout << "\n\n\t   Press Enter !" << endl;
		while (true) {
			int ch = _getch();
			if (ch == 13)
				break;
		}
		showMenu();
	}
}

//�������� 
void MineSweeper::endGame()
{
	setCursorView(false);
	system("mode con:cols=40 lines=30");
	system("cls");
	setcolor(15, 0);
	cout << "�й� : 201911288 �̸� : ������" << endl;
	readGame();

	if (record == true) {
		cout << "\n\n\t  �ֱ� �÷��� �� ����\n\t" << realRow << " X " << realCol << " , ���̵� ";
		setcolor(14, 0);
		for (int i = 0; i < difficulty; i++) {
			cout << "��";
		}
		setcolor(15, 0);
		cout << "�� \n\t  ����� �����մϴ�." << endl;
		ofstream outfile;
		outfile.open("map.txt");
		outfile << "NO_RECORD" << " ";
		this->record = false;
	}
	else {
		cout << "\n\n\t������ ���� ����� �����ϴ�." << endl;
	}
	cout << "\n\t ������ �����մϴ�." << endl << endl << endl;
}

// �ʱ� �迭 ����
void MineSweeper::makeInitialMap()
{
	// map ���� �� �ʱ�ȭ 
	map = new int* [row];
	for (int i = 0; i < row; i++)
	{
		map[i] = new int[col];
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (i == 0 || j == 0 || i == row - 1 || j == col - 1) {
				map[i][j] = TEMP;
			}
			else {
				map[i][j] = NOTBOMB;
			}
		}
	}

	// checkMap ���� �� �ʱ�ȭ
	checkMap = new int* [row];
	for (int i = 0; i < row; i++)
	{
		checkMap[i] = new int[col];
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (i == 0 || j == 0 || i == row - 1 || j == col - 1) {
				checkMap[i][j] = TEMP;
			}
			else {
				checkMap[i][j] = NOTBOMB;
			}
		}
	}

	// map�� ���� ����
	for (int i = 0; i < bomb; i++)
	{
		int x = (rand() % realRow) + 1;
		int y = (rand() % realCol) + 1;
		if (map[x][y] == NOTBOMB)
		{
			map[x][y] = BOMB;
			checkMap[x][y] = BOMB;
		}
		else
		{
			i--;
			continue;
		}
	}
	//originalCheckMap ���� �� �ʱ�ȭ 
	originalCheckMap = new int* [row];
	for (int i = 0; i < row; i++)
	{
		originalCheckMap[i] = new int[col];
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			originalCheckMap[i][j] = checkMap[i][j];
		}
	}
	countAroundBomb();
	saveGame();
}

// �����÷���ȭ�� ���
void MineSweeper::printMap()
{
	system("mode con:cols=50 lines=35");
	system("cls");
	setcolor(15, 0);
	cout << "�й� : 201911288 �̸� : ������" << endl << endl;
	gotoxy(6, 2);
	setcolor(8, 0);
	cout << "\t" << realRow << " X " << realCol << " ���� : " << bomb << "�� " << endl;
	gotoxy(6, 3);
	cout << "\t   ���̵� ";
	setcolor(14, 0);
	for (int i = 0; i < difficulty; i++) {
		cout << "��";
	}
	gotoxy(4, 4);
	setcolor(7, 0);
	for (int i = 0; i < col; i++) {
		cout << "��";
	}
	int x = 6;
	int y = 5;
	for (int i = 1; i < row - 1; i++) {
		gotoxy(x, y);
		for (int j = 1; j < col - 1; j++) {
			if (checkMap[i][j] == BOMB || checkMap[i][j] == NOTBOMB) {
				setcolor(8, 0);
				cout << "��";
			}
			else if (checkMap[i][j] == FLAG) {
				setcolor(4, 0);
				cout << "��";
			}
			else {
				setcolor(15, 0);
				cout << checkMap[i][j] << " ";
			}
		}
		cout << endl;
		y++;
	}
	gotoxy(3, y + 1);
	setcolor(7, 0);
	for (int i = 0; i < col; i++) {
		cout << "��";
	}
	cout << endl << endl;
	setcolor(13, 0);
	cout << "      �ڡڡڡ�   R U L E   �ڡڡڡ�" << endl;
	setcolor(15, 0);
	cout << "      UP : ��\t\tDOWN : ��" << endl;
	cout << "      RIGHT : ��\tLEFT : ��" << endl;
	cout << "      ���� : ENTER\t";
	setcolor(4, 0);
	cout << "��";
	setcolor(15, 0);
	cout << ": SPACE BAR" << endl;
	cout << "      �޴� : Esc" << endl;
}

// ���� �÷��� ���
void MineSweeper::playGame()
{
	int x = 6;
	int y = 5;
	int m_row;
	int m_col;
	while (true) {
		m_row = y - 5 + 1;
		m_col = ((x - 6) / 2) + 1;
		gotoxy(6, 12 + row);
		setcolor(15, 0);
		cout << "���� ���� : " << selectable()<<"   ";
		cout << "\t��� : " << flagCount() << "         ";
		gotoxy(x, y);
		int ch = _getch();
		//���� ������
		if (ch == 13) {
			//������ ĭ�� �����̸� => �����й�
			if (checkMap[m_row][m_col] == BOMB) {
				replayxy.push_back({ {m_row,m_col},BOMB });
				setCursorView(false);
				gotoxy(10, 14 + row);
				setcolor(12, 0);
				cout << "Y O U  L O S E " << endl;
				setcolor(11, 0);
				cout << " \t ENTER -> ���÷��� \n\t Esc -> �޴�ȭ��" << endl;
				printMine(m_row, m_col);
				setcolor(15, 0);
				gotoxy(6, 12 + row);
				cout << "                                                             ";
				while (true) {
					ch = _getch();
					if (ch == 13) {
						replay();
					}
					if (ch == 27) {
						break;
					}
				}
				break;
			}
			//������ ĭ�� ���ڰ� �ƴϸ�
			else if (checkMap[m_row][m_col] == NOTBOMB) {
				replayxy.push_back({ {m_row,m_col },NOTBOMB });
				printAround(m_row, m_col, checkMap);
				gotoxy(x, y);
			}
		}
		else if (ch == 27) {
			break;
		}
		//��߱��
		else if (ch == 32) {
			// �̹� ����� ��� 
			if (checkMap[m_row][m_col] == FLAG) {
				replayxy.push_back({ {m_row,m_col },CFLAG });
				gotoxy(x, y);
				setcolor(8, 0);
				cout << "��";
				if (map[m_row][m_col] == BOMB) {
					checkMap[m_row][m_col] = BOMB;
					flag--;
				}
				else if (map[m_row][m_col] != BOMB) {
					checkMap[m_row][m_col] = NOTBOMB;
				}
			}
			// ��� ���� ĭ�� ������ ��� 
			else if (checkMap[m_row][m_col] == BOMB) {
				replayxy.push_back({ {m_row,m_col },FLAG });
				gotoxy(x, y);
				setcolor(4, 0);
				cout << "��";
				flag++;
				checkMap[m_row][m_col] = FLAG;
				// ���ڿ� ���� ��� ������ ���� ������ ������� ->�¸�
				if (flag == bomb) {
					setCursorView(false);
					gotoxy(10, 14 + row);
					setcolor(12, 0);
					cout << "   Y O U  W I N " << endl;
					setcolor(11, 0);
					cout << " \t ENTER -> ���÷��� \n\t Esc -> �޴�" << endl;
					gotoxy(6, 12 + row);
					cout << "                                                             ";
					printMine(m_row, m_col);
					while (true) {
						ch = _getch();
						if (ch == 13) {
							replay();
						}
						if (ch == 27) {
							break;
						}
					}
					break;
				}
			}
			// ��� ���� ĭ�� ���ڰ� �ƴѰ��
			else if (checkMap[m_row][m_col] == NOTBOMB) {
				replayxy.push_back({ {m_row,m_col },FLAG });
				gotoxy(x, y);
				setcolor(4, 0);
				cout << "��";
				checkMap[m_row][m_col] = FLAG;
			}
		}
		//����Ű�� �̵�
		else if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 72: // up
				if (map[m_row - 1][m_col] != TEMP)	y--;
				break;
			case 75: // left
				if (map[m_row][m_col - 1] != TEMP)	x -= 2;
				break;
			case 77: // right
				if (map[m_row][m_col + 1] != TEMP)	x += 2;
				break;
			case 80: //down
				if (map[m_row + 1][m_col] != TEMP)	y++;
				break;
			}
			gotoxy(x, y);
		}

		saveGame();
	}
	showMenu();
}

void MineSweeper::printAround(int m_row, int m_col, int** checkMap)
{
	setcolor(15, 0);
	int x = 2 * m_col + 4;
	int y = m_row + 4;
	gotoxy(x, y);
	cout << map[m_row][m_col] << " ";
	checkMap[m_row][m_col] = map[m_row][m_col];
	if (map[m_row][m_col] == 0) {
		if (map[m_row - 1][m_col - 1] != BOMB && map[m_row - 1][m_col - 1] != TEMP && checkMap[m_row - 1][m_col - 1] != FLAG) {
			if (map[m_row - 1][m_col - 1] == 0 && checkMap[m_row - 1][m_col - 1] != 0) {
				printAround(m_row - 1, m_col - 1, checkMap);
			}
			else {
				gotoxy(x - 2, y - 1);
				cout << map[m_row - 1][m_col - 1] << " ";
				checkMap[m_row - 1][m_col - 1] = map[m_row - 1][m_col - 1];
			}
		}
		if (map[m_row][m_col - 1] != BOMB && map[m_row][m_col - 1] != TEMP && checkMap[m_row][m_col - 1] != FLAG) {
			if (map[m_row][m_col - 1] == 0 && checkMap[m_row][m_col - 1] != 0) {
				printAround(m_row, m_col - 1, checkMap);
			}
			else {
				gotoxy(x - 2, y);
				cout << map[m_row][m_col - 1] << " ";
				checkMap[m_row][m_col - 1] = map[m_row][m_col - 1];
			}
		}
		if (map[m_row + 1][m_col - 1] != BOMB && map[m_row + 1][m_col - 1] != TEMP && checkMap[m_row + 1][m_col - 1] != FLAG) {
			if (map[m_row + 1][m_col - 1] == 0 && checkMap[m_row + 1][m_col - 1] != 0) {
				printAround(m_row + 1, m_col - 1, checkMap);
			}
			else {
				gotoxy(x - 2, y + 1);
				cout << map[m_row + 1][m_col - 1] << " ";
				checkMap[m_row + 1][m_col - 1] = map[m_row + 1][m_col - 1];
			}
		}
		if (map[m_row + 1][m_col] != BOMB && map[m_row + 1][m_col] != TEMP && checkMap[m_row + 1][m_col] != FLAG) {
			if (map[m_row + 1][m_col] == 0 && checkMap[m_row + 1][m_col] != 0) {
				printAround(m_row + 1, m_col, checkMap);
			}
			else {
				gotoxy(x, y + 1);
				cout << map[m_row + 1][m_col] << " ";
				checkMap[m_row + 1][m_col] = map[m_row + 1][m_col];
			}
		}
		if (map[m_row - 1][m_col] != BOMB && map[m_row - 1][m_col] != TEMP && checkMap[m_row - 1][m_col] != FLAG) {
			if (map[m_row - 1][m_col] == 0 && checkMap[m_row - 1][m_col] != 0) {
				printAround(m_row - 1, m_col, checkMap);
			}
			else {
				gotoxy(x, y - 1);
				cout << map[m_row - 1][m_col] << " ";
				checkMap[m_row - 1][m_col] = map[m_row - 1][m_col];
			}
		}
		if (map[m_row - 1][m_col + 1] != BOMB && map[m_row - 1][m_col + 1] != TEMP && checkMap[m_row - 1][m_col + 1] != FLAG) {
			if (map[m_row - 1][m_col + 1] == 0 && checkMap[m_row - 1][m_col + 1] != 0) {
				printAround(m_row - 1, m_col + 1, checkMap);
			}
			else {
				gotoxy(x + 2, y - 1);
				cout << map[m_row - 1][m_col + 1] << " ";
				checkMap[m_row - 1][m_col + 1] = map[m_row - 1][m_col + 1];
			}
		}
		if (map[m_row][m_col + 1] != BOMB && map[m_row][m_col + 1] != TEMP && checkMap[m_row + 1][m_col + 1] != FLAG) {
			if (map[m_row][m_col + 1] == 0 && checkMap[m_row][m_col + 1] != 0) {
				printAround(m_row, m_col + 1, checkMap);
			}
			else {
				gotoxy(x + 2, y);
				cout << map[m_row][m_col + 1] << " ";
				checkMap[m_row][m_col + 1] = map[m_row][m_col + 1];
			}
		}
		if (map[m_row + 1][m_col + 1] != BOMB && map[m_row + 1][m_col + 1] != TEMP && checkMap[m_row + 1][m_col + 1] != FLAG) {
			if (map[m_row + 1][m_col + 1] == 0 && checkMap[m_row + 1][m_col + 1] != 0) {
				printAround(m_row + 1, m_col + 1, checkMap);
			}
			else {
				gotoxy(x + 2, y + 1);
				cout << map[m_row + 1][m_col + 1] << " ";
				checkMap[m_row + 1][m_col + 1] = map[m_row + 1][m_col + 1];
			}
		}
	}
}

// ������ ĭ�� �ֺ� ���� ���� ����
void MineSweeper::countAroundBomb()
{
	for (int i = 1; i < row - 1; i++) {
		for (int j = 1; j < col - 1; j++) {
			int count = 0;
			// ���ڰ� �ƴϸ� �ֺ� ���� ���� ����
			if (map[i][j] != BOMB) {
				if (map[i - 1][j - 1] == BOMB)	count++;
				if (map[i - 1][j] == BOMB)	count++;
				if (map[i - 1][j + 1] == BOMB)	count++;
				if (map[i][j + 1] == BOMB)	count++;
				if (map[i][j - 1] == BOMB)	count++;
				if (map[i + 1][j - 1] == BOMB)	count++;
				if (map[i + 1][j] == BOMB)	count++;
				if (map[i + 1][j + 1] == BOMB)	count++;
				map[i][j] = count;
			}
		}
	}
}

// ���� ������ ĭ�� ���� ����
int MineSweeper::selectable()
{
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (checkMap[i][j] == NOTBOMB || checkMap[i][j] == BOMB)
				count++;
		}
	}
	return count;
}

// ����� ���� ���� 
int MineSweeper::flagCount()
{
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (checkMap[i][j] == FLAG)
				count++;
		}
	}
	return count;
}

// ���� �����ϱ�
void MineSweeper::saveGame()
{
	ofstream outfile;
	outfile.open("map.txt");
	if (outfile.is_open()) {
		this->record = true;
		outfile << "SAVE" << " ";
		outfile << row << " ";
		outfile << col << " ";
		outfile << difficulty << " ";
		outfile << bomb << " ";
		outfile << flag << " ";
		outfile << endl;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (outfile.is_open()) {
					outfile << map[i][j] << " ";
				}
			}
			outfile << endl;
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (outfile.is_open()) {
					outfile << checkMap[i][j] << " ";
				}
			}
			outfile << endl;
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (outfile.is_open()) {
					outfile << originalCheckMap[i][j] << " ";
				}
			}
			outfile << endl;
		}

		for (auto it = replayxy.begin(); it < replayxy.end(); it++) {
			outfile << (*it).first.first << " ";
			outfile << (*it).first.second << " ";
			outfile << (*it).second << " ";
		}
	}
}

// ����� ���� �ҷ�����
void MineSweeper::readGame()
{
	ifstream infile;
	infile.open("map.txt");
	string state;
	int row, col, difficulty, bomb, flag;
	infile >> state;
	if (state == "SAVE") {
		this->record = true;
		infile >> row >> col >> difficulty >> bomb >> flag;
		this->row = row;
		this->col = col;
		this->difficulty = difficulty;
		this->bomb = bomb;
		this->flag = flag;
		this->realRow = row - 2;
		this->realCol = col - 2;

		int** savedMap = new int* [row];
		for (int i = 0; i < row; i++) {
			savedMap[i] = new int[col];
		}

		int** savedCheckMap = new int* [row];
		for (int i = 0; i < row; i++) {
			savedCheckMap[i] = new int[col];
		}

		int** savedOriginalCheckMap = new int* [row];
		for (int i = 0; i < row; i++)
		{
			savedOriginalCheckMap[i] = new int[col];
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				infile >> savedMap[i][j];
			}
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				infile >> savedCheckMap[i][j];
			}
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				infile >> savedOriginalCheckMap[i][j];
			}
		}
		this->map = savedMap;
		this->checkMap = savedCheckMap;
		this->originalCheckMap = savedOriginalCheckMap;

		this->replayxy.clear();
		int m_row, m_col, check;
		while (!infile.eof()) {
			infile >> m_row;
			infile >> m_col;
			infile >> check;
			replayxy.push_back({ {m_row,m_col},check });
		}
	}
}

// ���÷���
void MineSweeper::replay() {
	readGame();
	gotoxy(8, 18 + row);
	setcolor(15, 0);
	cout << "���÷����� ..." << endl;
	int x = 6;
	int y = 5;
	for (int i = 1; i < row - 1; i++) {
		gotoxy(x, y);
		for (int j = 1; j < col - 1; j++) {
			setcolor(8, 0);
			cout << "��";
		}
		cout << endl;
		y++;
	}
	int m_row, m_col, check;
	for (auto it = replayxy.begin(); it != replayxy.end(); it++) {
		m_row = (*it).first.first;
		m_col = (*it).first.second;
		check = (*it).second;
		int x = 2 * m_col + 4;
		int y = m_row + 4;
		if (check == NOTBOMB) {
			Sleep(200);
			setcolor(15, 0);
			printAround(m_row, m_col, originalCheckMap);
			gotoxy(x, y);
		}
		if (check == FLAG) {
			Sleep(100);
			setcolor(4, 0);
			gotoxy(x, y);
			cout << "��";
		}
		if (check == CFLAG) {
			Sleep(100);
			setcolor(8, 0);
			gotoxy(x, y);
			cout << "��";
		}
	}
	for (auto it = replayxy.begin(); it != replayxy.end(); ++it) {
		m_row = (*it).first.first;
		m_col = (*it).first.second;
		int x = 2 * m_col + 4;
		int y = m_row + 4;
		printMine(m_row, m_col);
	}
	gotoxy(8, 18 + row);
	cout << "                      " << endl;
}

//������ ĭ ���
void MineSweeper::printMine(const int m_row, const int m_col)
{
	setcolor(14, 0);
	for (int i = 1; i < row - 1; i++) {
		for (int j = 1; j < col - 1; j++ ) {
			gotoxy(2 * j + 4, i + 4);
			if (map[i][j] == BOMB) {
				gotoxy(2 * j + 4, i + 4);
				cout << "��";
			}
		}
	}
}

