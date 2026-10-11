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
    Sub(int spawnX, int spawnY) : x(spawnX), y(spawnY), oxy(15), cash(0), bank(0), logo('@') {}

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
        oxy = 15;
		bank += cash;
        cash = 0;
    }

    void profit() {
        cash += rand() % 15 + 10;
    }
};

void mainMenu() {
    system("cls");
	cout << "Welcome to Sub Adventure!" << endl;
    cout << "Collect and sell as much treasure as you can without running out of oxygen!" << endl;
    cout << "Use WASD or arrow keys to navigate the deep sea!" << endl;
    cout << "Use I to inspect nearby waters." << endl;
	cout << "Press any key to begin" << endl;
    _getch();
}


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



void printFullMap(vector<vector<char>>& map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}


void printCam(vector<vector<char>>& map, Sub& player) {
    int startX = player.getX() - 2;
    int startY = player.getY() - 2;

    // Keep the 5x5 view inside the map boundaries.
    if (startX < 0)
        startX = 0;
    if (startX > map[0].size() - 5)
        startX = map[0].size() - 5;

    if (startY < 0)
        startY = 0;
    if (startY > map.size() - 5)
        startY = map.size() - 5;

    // Display only the 5x5 section.
    for (int i = startY; i < startY + 5; i++) {
        for (int j = startX; j < startX + 5; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}



bool boundary(vector<vector<char>>& map, int futureX, int futureY) {
	if (futureY < 0 || futureY >= map.size() || futureX < 0 || futureX >= map[0].size()) {
		return false;
	}

    if (map[futureY][futureX] == '{' || map[futureY][futureX] == '}' || map[futureY][futureX] == '_') {
        cout << "You are trying to swim out of bounds! Please try another input." << endl;
        return false;
    }
	return true;
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


void checkSpot(vector<vector<char>>& map, Sub& player, bool inspect = false)
{
    int x = player.getX();
    int y = player.getY();

    // Check the tile the submarine is standing on.
    if (inspect == false) {
        if (map[y][x] == '$') {
            cout << "You found treasure!" << endl;

            map[y][x] = '%';

            int oldCash = player.getCash();
            player.profit();
            int found = player.getCash() - oldCash;

            cout << "You picked up $" << found << " worth of treasure!" << endl;
        } else if (map[y][x] == '!') {
            int num = rand() % 5;
            string animal;

            if (num == 0)
                animal = "great white shark";
            else if (num == 1)
                animal = "giant squid";
            else if (num == 2)
                animal = "pack of orcas";
            else if (num == 3)
                animal = "pack of dolphins";
            else
                animal = "bunch of old ship debris";

            cout << "You ran into a " << animal << "!" << endl;
            map[y][x] = '%';
        }
    } if (inspect == true) {

        int aroundX[] = { 0, 0, -1, 1, -1, -1, 1, 1 };
        int aroundY[] = { -1, 1, 0, 0, -1, 1, -1, 1 };

        bool found = false;

        for (int i = 0; i < 8; i++) {
            int checkX = x + aroundX[i];
            int checkY = y + aroundY[i];

            if (checkX < 0 || checkX >= map[0].size() ||
                checkY < 0 || checkY >= map.size()) {
                continue;
            }

            if (map[checkY][checkX] == '$') {
                cout << "You found nearby treasure!" << endl;

                map[checkY][checkX] = '%';

                int oldCash = player.getCash();
                player.profit();
                int found = player.getCash() - oldCash;

                cout << "You collected $" << found << " worth of treasure!" << endl;

                found = true;
            } else if (map[checkY][checkX] == '!') {
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
                else {
                    animal = "bunch of old ship debris";
                }

                cout << "You ran into a " << animal << "!" << endl;

                map[checkY][checkX] = '%';

                found = true;
            }
        }

        if (found == false) {
            cout << "No events of note found." << endl;
        }
    }
}

    


void clear(vector<vector<char>>& map, Sub& player) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '@' && (i != player.getY() || j != player.getX())) {
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

    //printFullMap(map);
    //spawns sub

    mainMenu();
    printFullMap(map);
    //cout << "Use WASD or arrow keys to begin" << endl;

    while (gameOver == false) {
        //ogX = player.getX();
        //ogY = player.getY();
        //ogChar = map[ogY][ogX];

		cout << endl << endl;
        clear(map, player);
        printCam(map, player);
        cout << "Oxygen: " << player.getOxy() << endl;
        cout << "Treasure stored sub: $" << player.getCash() << endl;
        cout << "Bank account: $" << player.getBank() << endl;
        cout << "Move (WASD) or Inspect (I): " << endl;
        input = _getch();

        if (input == 224) {
			input = _getch();
            if(input == 72) {  // Up arrow
                if(boundary(map, player.getX(), player.getY() - 1)) {
                    player.up();
                }
            }
			else if (input == 80) {  // Down arrow
				if(boundary(map, player.getX(), player.getY() + 1)) {
					player.down();
				}
			}
			else if (input == 75) {  // Left arrow
				if(boundary(map, player.getX() - 1, player.getY())) {
					player.left();
				}
			}
			else if (input == 77) {  // Right arrow
				if(boundary(map, player.getX() + 1, player.getY())) {
					player.right();
				}
			}
        }
        else {

            if (input == 'w' || input == 'W') {
                if(boundary(map, player.getX(), player.getY() - 1)) {
                    player.up();
                }
            }
            else if (input == 's' || input == 'S') {
                if(boundary(map, player.getX(), player.getY() + 1)) {
                    player.down();
                }
            }
            else if (input == 'a' || input == 'A') {
                if(boundary(map, player.getX() - 1, player.getY())) {
                    player.left();
                }
            }
            else if (input == 'd' || input == 'D') {
                if(boundary(map, player.getX() + 1, player.getY())) {
                    player.right();
                }
			}
            else if (input == 'i' || input == 'I') {
                checkSpot(map, player, true);
            } else {
				cout << "Invalid input. Please use WASD or arrow keys to move or I to inspect." << endl;
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
            cout << "You sold all your treasure and now have $" << player.getBank() << " in your bank account!" << endl;
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
