// SubAdventure.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h>

using namespace std;

class Sub {
private:
    int x;
    // horizontal, x-axis, (columns)
    int y;
    // vertical, y-axis, (rows)
    int oxy;
    int cash;
    int bank;
    char logo;

public:
    Sub(int spawnX, int spawnY) : x(spawnX), y(spawnY), oxy(10), cash(0), bank(0), logo('@') {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getOxy() const { return oxy; }
    int getCash() const { return cash; }
    int getBank() const { return bank; }
    char getLogo() const { return logo; }

    void up() {
        y--;
        oxy--;
    }
    void down() {
        y++;
        oxy--;
    }
    void left() {
        x--;
        oxy--;
    }
    void right() {
        x++;
        oxy--;
    }
    void refill() {
        oxy = 10;
		bank += cash;
        cash = 0;
    }

    void profit() {
        cash += rand() % 15 + 10;
    }
};


void genMap(vector<vector<char>>& map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {

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
        }
    }
}



void printMap(vector<vector<char>>& map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}



void treasure(vector<vector<char>>& map) {
    vector<int> x(10);
    vector<int> y(10);

    int num = 0;

    while (num < 10) {
        int y = rand() % 8 + 1;
        int x = rand() % 9 + 1;

        if (map[y][x] == '%') {
            map[y][x] = '$';
            num++;
        }
    }
}

void special(vector<vector<char>>& map) {
	vector<int> x(10);
	vector<int> y(10);
    int num2 = 0;

    while(num2 < 5) {
        int y = rand() % 8 + 1;   // rows 1–8
        int x = rand() % 9 + 1;   // columns 1–9

        if (map[y][x] == '%') {   // only place on empty tile
            map[y][x] = '!';
            num2++;
        }
    }
}

void checkSpot(vector<vector<char>>& map, Sub& player) {
    if (map[player.getY()][player.getX()] == '$') {
        cout << "You found treasure!" << endl;
        map[player.getY()][player.getX()] = '%';  
        player.profit();
        cout << "You picked up $" << player.getCash() << " worth of treasure!" << endl;
    }
    else if (map[player.getY()][player.getX()] == '!') {
        int num = rand() % 5;
        string animal;
        if (num == 0) {
            animal = "great white shark";
        }
        else if (num == 1) {
            animal = "giant squid";
        }
        else if (num == 2) {
            animal = "pack of orcas";
        }
        else if (num == 3) {
            animal = "pack of dolphins";
        }
        else if (num == 4) {
            animal = "bunch of old ship debris";
        }
        cout << "You ran into a " << animal << "!" << endl;
        map[player.getY()][player.getX()] = '%';


    }
}

void clear(vector<vector<char>>& map, Sub& player) {
    for(int i = 0; i < map.size(); i++) {
        for(int j = 0; j < map[i].size(); j++) {
            if(map[i][j] == '@' && map[i][j] != map[player.getY()][player.getX()]) {
                if (i == 0) {
					map[i][j] = '~';
                }
                else {
					map[i][j] = '%';
                }
            }
        }
    }
}



int main() {

    bool gameOver = false;
    int input = _getch();
    int count = 0;
    int ogX;
    int ogY;
    char ogChar;


    vector<vector<char>> map(11, vector<char>(12, '%'));

    genMap(map);
    Sub player(rand() % 4 + 4, 0);
    //map[player.getY()][player.getX()] = player.getLogo();
    treasure(map);
    special(map);
    map[player.getY()][player.getX()] = player.getLogo();
    //spawns sub

    cout << "Use WASD or arrow keys to begin" << endl;

    while (gameOver == false) {
        //ogX = player.getX();
        //ogY = player.getY();
        //ogChar = map[ogY][ogX];

		cout << endl << endl;
        clear(map, player);
        printMap(map);
        cout << "Oxygen: " << player.getOxy() << endl;
        cout << "Treasure stored sub: $" << player.getCash() << endl;
        cout << "Bank account: $" << player.getBank() << endl;
        cout << "Move (WASD): " << endl;
        input = _getch();

        if (input == 224) {
			input = _getch();
            if(input == 72) {  // Up arrow
                player.up();
            }
			else if (input == 80) {  // Down arrow
				player.down();
			}
			else if (input == 75) {  // Left arrow
				player.left();
			}
			else if (input == 77) {  // Right arrow
				player.right();
			}
        }
        else {

            if (input == 'w' || input == 'W') {
                player.up();
            }
            else if (input == 's' || input == 'S') {
                player.down();
            }
            else if (input == 'a' || input == 'A') {
                player.left();
            }
            else if (input == 'd' || input == 'D') {
                player.right();
            }
            else {
				cout << "Invalid input. Please use WASD or arrow keys to move." << endl;
            }
        }

        //if (ogChar == '~') {
        //    map[ogY][ogX] = '~';
        //}
        //else if (ogChar == '%' || ogChar == '$') {
        //    map[ogY][ogX] = '%';
        //}

        checkSpot(map, player);

        map[player.getY()][player.getX()] = player.getLogo();

        if (player.getY() == 0) {
            player.refill();
            cout << "Oxygen refilled back to 10" << endl;
            cout << "You sold your treasure for $" << player.getCash() << " and now have $" << player.getBank() << " in your bank account!" << endl;
        }
        if (player.getOxy() == 0) {
            gameOver = true;
			cout << endl << "You ran out of oxygen. Game Over. You finished with $" << player.getBank() << endl;
        }

        //count++;
        //if (count == 10) {
        //    gameOver = true;
        //}
    }


    return 0;
}
