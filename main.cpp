#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include "Game.h"
#include "UserLibrary.h"
using namespace std;

enum Choices {QUIT,START,CHANGE,LOGIN,LEADERBOARD};

int main() {

	srand((unsigned)time(nullptr));
	int choice;
	float score; 
	
	UserLibrary users;
	Game newGame;

	// main game logic	
	do {
		users.printCurrentUser();
		newGame.PrintSettings();
		cout << "\npress 1 to start game \npress 2 to change settings \npress 3 to log in\npress 4 for leaderboards\npress 0 to quit\n";
		cin >> choice;

		if (choice == QUIT) {
			return 0;
		}
		else if (choice == START) {
			score = newGame.StartGame();
			users.updateScore(newGame.GetLevel(), score);
			users.updatePlayersFile();
			system("pause");
		}
		else if (choice == CHANGE) {
			newGame.SettingsMenu();
		}
		else if (choice == LOGIN) {
			users.loginMenu();
		}
		else if (choice == LEADERBOARD) {
			users.leaderboard(newGame.GetLevel());
		}
	 } while (true);

    return 0;
}