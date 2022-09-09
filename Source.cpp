#include<iostream>
#include<Windows.h>
#include<vector>
#include<iomanip>
#include <string> 


using namespace std;

HANDLE hConsole;

void printRulesOFTheGame() {
	system("cls");
	cout << "Игра 'Российский флаг'.Вдоль доски расположены лунки(количество лунок кратно 3).\nВ каждой лунке лежит красный, белый или синий шар.Одним ходом разрешается менять местами два любых шара.\nНеобходимо добиться того, чтобы все белые шары шли первыми, за ними - синие шары, а красные - последними.\nЕсли общее число лунок равно n, то для решения задачи достаточно сделать не более n - 1 хода.\nЕсли игрок делает более чем n - 1 ход, то игра проиграна.\nПрограмма может иметь несколько уровней сложности(уровни сложности могут зависеть от количества ходов).\n";
	system("pause");
}

int getNumber(const int &beg, const int &end) {
	int n;
	while (true) // Бесконечный цикл, который внутри прерывается по условию
    {
		cin >> n;   // Ввод значения пользователем
		if (!cin.fail()){ // Если ввели число, а значит поток не в состоянии ошибки, то завершаем цикл
			if (beg <= n && n <= end)break;
		}
		cout << "		syntax error!" << endl;
		cin.clear(); // Сбрасываем состояние ошибки
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
	cout << "Введите ширину игрового поля\n";
	int sizeBoard = getNumber(1, 50);
	vector<int> pit1(2);
	vector<int> pit2(2);
	vector <vector <string>> board(4, vector<string>(sizeBoard, "Б"));// буква б
	board[0][0] = "*";
	for (int i = 1; i < board[0].size(); i++) board[2][i] = "С";// буква с
	for (int i = 1; i < board[0].size(); i++) board[3][i] = "К";// буква к
	for (int i = 1; i < 4; i++) board[i][0] = to_string(i); //боковой столец цифр
	for (int i = 1; i < board[0].size(); i++) board[0][i] = to_string(i); //верхний ряд цифр

	///перемещиваем буквы
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
	cout << "   На данный момент совершенно " << counter << " хода(-ов)" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < board[0].size(); j++) {
			if (board[i][j] == "Б") 
				SetConsoleTextAttribute(hConsole, 15);
			else if (board[i][j] == "С") 
					SetConsoleTextAttribute(hConsole, 1);
			else if (board[i][j] == "К") 
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
		if (board[1][i] != "Б") return false;
	for (int i = 1; i < board[2].size(); i++)
		if (board[2][i] != "С") return false;
	for (int i = 1; i < board[3].size(); i++)
		if (board[3][i] != "К") return false; 
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
				cout << "Наше искренние поздравления!!!\n";
				Sleep(2500);
				break;
			}
			if (moveCounter >= ( board[0].size() - 1 ) * 3 - 1) {
				system("cls");
				cout << "Вы програли, вам потреболась слишком много ходов";
				Sleep(2500);
				break;
			}
			moveCounter++;
		}

		cout << "Для выхода выхода из игры наберите exit, для продолжения любой символ\n";
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