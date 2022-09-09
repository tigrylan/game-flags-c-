#include<iostream>
#include<Windows.h>
#include<vector>
#include<iomanip>
#include <string> 


using namespace std;

HANDLE hConsole;

void printRulesOFTheGame() {
	system("cls");
	cout << "���� '���������� ����'.����� ����� ����������� �����(���������� ����� ������ 3).\n� ������ ����� ����� �������, ����� ��� ����� ���.����� ����� ����������� ������ ������� ��� ����� ����.\n���������� �������� ����, ����� ��� ����� ���� ��� �������, �� ���� - ����� ����, � ������� - ����������.\n���� ����� ����� ����� ����� n, �� ��� ������� ������ ���������� ������� �� ����� n - 1 ����.\n���� ����� ������ ����� ��� n - 1 ���, �� ���� ���������.\n��������� ����� ����� ��������� ������� ���������(������ ��������� ����� �������� �� ���������� �����).\n";
	system("pause");
}

int getNumber(const int &beg, const int &end) {
	int n;
	while (true) // ����������� ����, ������� ������ ����������� �� �������
    {
		cin >> n;   // ���� �������� �������������
		if (!cin.fail()){ // ���� ����� �����, � ������ ����� �� � ��������� ������, �� ��������� ����
			if (beg <= n && n <= end)break;
		}
		cout << "		syntax error!" << endl;
		cin.clear(); // ���������� ��������� ������
		cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
	}
	return n;
};
void swappits(vector <vector <string>>& board, vector<int> & pit1, vector<int>& pit2) {
	swap(board [ pit1[0] ] [ pit1[1] ], board [pit2[0] ] [ pit2[1] ]);
}

vector <vector <string>> initialiseBoard(const int &modeGame) {
	system("color F6");
	srand(time(0));
	cout << "������� ������ �������� ����\n";
	int sizeBoard = getNumber(1, 50);
	vector<int> pit1(2);
	vector<int> pit2(2);
	vector <vector <string>> board(4, vector<string>(sizeBoard, "�"));// ����� �
	board[0][0] = "*";
	for (int i = 1; i < board[0].size(); i++) board[2][i] = "�";// ����� �
	for (int i = 1; i < board[0].size(); i++) board[3][i] = "�";// ����� �
	for (int i = 1; i < 4; i++) board[i][0] = to_string(i); //������� ������ ����
	for (int i = 1; i < board[0].size(); i++) board[0][i] = to_string(i); //������� ��� ����

	///������������ �����
	for (int i = 0; i < board[0].size() * modeGame; i++) {
		pit1[0] = rand() % 3 + 1;
		pit1[1] = rand() % ( sizeBoard- 1) + 1;
		pit2[0] = rand() % 3 + 1;
		pit2[1] = rand() % (sizeBoard - 1) + 1;	
		swappits(board, pit1, pit2);
	}
	return board;
}

void printBoard( const vector <vector <string>> &board, int & counter){
	system("cls");
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Rus");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	cout << "   �� ������ ������ ���������� " << counter << " ����(-��)" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < board[0].size(); j++) {
			if (board[i][j] == "�") 
				SetConsoleTextAttribute(hConsole, 15);
			else if (board[i][j] == "�") 
					SetConsoleTextAttribute(hConsole, 1);
			else if (board[i][j] == "�") 
				SetConsoleTextAttribute(hConsole, 4);
			else
				SetConsoleTextAttribute(hConsole, 15);
			cout << setw(3) << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
	SetConsoleTextAttribute(hConsole, 15);
}
void movePlayer(vector <vector <string>>& board){
	vector<int> pit1(2);
	vector<int> pit2(2);
	cout << "enter the coordinates of the first pit\n";
	pit1[0] = getNumber(1, 3);
	pit1[1] = getNumber(1, board[0].size() - 1);
	cout << "enter the coordinates of the second pit\n";
	pit2[0] = getNumber(1, 3);
	pit2[1] = getNumber(1, board[0].size() - 1);
	swappits(board, pit1, pit2);
}
bool checkWin(const vector <vector <string>>& board)
{
	bool flag = true;
	for (int i = 1; i < board[1].size(); i++)
		if (board[1][i] != "�") return false;
	for (int i = 1; i < board[2].size(); i++)
		if (board[2][i] != "�") return false;
	for (int i = 1; i < board[3].size(); i++)
		if (board[3][i] != "�") return false; 
	return flag;
}


void start() {
	while (true) {
		printRulesOFTheGame();
		system("cls");
		int moveCounter = 0;
		cout << "mode game 1- middle; 2 - hard;\n";
		int modeGame = getNumber(1, 2);
		vector <vector <string>> board = initialiseBoard(modeGame);
		system("cls");
		while (true) {
			printBoard(board, moveCounter);
			movePlayer(board);
			system("cls");
			if (checkWin(board)) {
				system("cls");
				cout << "���� ��������� ������������!!!\n";
				Sleep(2500);
				break;
			}
			if (moveCounter >= ( board[0].size() - 1 ) * 3 - 1) {
				system("cls");
				cout << "�� ��������, ��� ����������� ������� ����� �����";
				Sleep(2500);
				break;
			}
			moveCounter++;
		}

		cout << "��� ������ ������ �� ���� �������� exit, ��� ����������� ����� ������\n";
		string str;
		cin>> str;
		if (str == "exit") break;
		system("cls");
	}
} 

int main(){
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Rus");
	start();
	return 0;
}