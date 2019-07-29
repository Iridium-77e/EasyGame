#include <iostream>
#include <cmath>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <cwchar>
#include <vector>

using namespace std;

vector<string> playerlist;
string currentplayer;
string previousplayer;
bool setprevious = true;
int playercount;
int playerprogression = 1;
int roundtime;
int timescale = 1000;
// Regular timescale: 1000

void collectnames() {
	string playercollected;
	bool continuenameloop;
	bool firstloop = true;
	int playerscollected = 1;

	cout << "How many players will there be?" << endl;
	cin >> playercount;
	playerlist.resize (playercount);
	while(continuenameloop) {
		cout << "Who is player " << playerscollected << "?" << endl;
		if(firstloop == true) {
			cin.ignore();
			firstloop = false;
		}
		getline(cin, playercollected);
		playerlist.insert (playerlist.begin() + playerscollected, playercollected);
		playerscollected++;

		if(playerscollected == playercount+1) {
			continuenameloop = false;
		}
	}
}

void introduction() {
	cout << "Welcome to EasyGame" << endl;
	collectnames();
	cout << "How many minutes per turn?" << endl;
	cin >> roundtime;
}

void playerlogic() {
	playerprogression++;
	previousplayer = currentplayer;
	if(playerprogression > playercount) {
		playerprogression = 1;
	}
	currentplayer = playerlist [playerprogression];
	if(setprevious == true) {
		previousplayer = playerlist [1];
		setprevious = false;
	}
}

void skipturn() {
	char playturn;

	cout << "It is " << playerlist [playerprogression] << "'s turn!" << endl;
	cout << "Play turn? (Y/N)" << endl;
	cin >> playturn;
	if(playturn == 'n' or playturn == 'N') {
		playerlogic();
		skipturn();

	}
}

void playertime() {
	bool runtimer = true;
	int timeremaining = roundtime;

	while(runtimer) {
		cout << string( 100, '\n' );
		cout << "You have " << timeremaining << " minutes remaining." << endl;
		Sleep(roundtime * timescale * 12);
		timeremaining--;
		if(timeremaining == 0) {
			cout << string( 100, '\n' );
			cout << previousplayer << "'s time is up! \n" << endl;
			runtimer = false;
		}
	}
}

int main() {
	system("color 71");
	SetConsoleTitle("EasyGame");
	introduction();
	while(true) {
		playerlogic();
		playertime();
		skipturn();
	}
}
