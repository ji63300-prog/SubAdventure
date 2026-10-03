// SubAdventure.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cstdlib>
//#include <windows.h>

using namespace std;

//class Sub {
//private:
//	int x;
//	int y;
//	int oxy;
//	char logo;
//
//public:
//	Sub(int x, int y, int oxy, char logo) : x(x), y(y), oxy(oxy), logo(logo) {}
//	int getX() const { return x; }
//	int getY() const { return y; }
//	int getOxy() const { return oxy; }
//	char getLogo() const { return logo; }
//	void setX(int newX) { x = newX; }
//	void setY(int newY) { y = newY; }
//	void setOxy(int newOxy) { oxy = newOxy; }
//	void setLogo(char newLogo) { logo = newLogo; }
//};


//l
void genMap(vector<vector<char>>& map) {
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (i == 0) {
				map[i][j] = '~';
			}
			else if (i == 10) {
				map[i][j] = '_';
			}
			if (j == 0 && i != 0) {
				map[i][j] = '{';
			}
			else if (j == 11 && i != 0) {
				map[i][j] = '}';
			}
			//cout << map[i][j] << " ";
		}
		//cout << endl;
	}
}

void printMap(vector<vector<char>>& map) {
	for (int i = 0; i < map.size(); i++){
		for (int j = 0; j < map[i].size(); j++){
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

void getSurface(vector<vector<char>>& map, int oxy) {
	for(int i = 0; i < map[0].size(); i++) {
		if (map[0][i] == '@') {
			cout << "Surface: " << i << endl;
			oxy = 50;
			cout << "Oxygen: " << oxy << endl;
		}
	}
}

void spawnSub(vector<vector<char>>& map, char sub) {
	map[0][rand() % 4 + 4] = sub;
}

void treasure(vector<vector<char>>& map) {
	vector<int> x(10);
	vector<int> y(10);
	for(int i = 0; i < 10; i++) {
		y[i] = rand() % 8 + 1;
		x[i] = rand() % 9 + 1;
	}
	for(int j = 0; j < 10; j++) {
		map[x[j]][y[j]] = '$';
	}
}

int main()
{
	//SetConsoleOutputCP(CP_UTF8);
    vector<vector<char>> map(11, vector<char>(12, '%'));
	char sub = '@';
	int oxy = 10;

	genMap(map);
	spawnSub(map, sub);
	treasure(map);
	printMap(map);
	getSurface(map, oxy);



	//for(int i = 0; i < 20; i++) {
	//	cout << rand() % 4 + 4 << " ";
	//}

}

