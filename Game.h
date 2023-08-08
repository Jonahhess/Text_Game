#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Game {

private:
	int level;
	int duration;
	vector<string> dictionary;

	int findSize(ifstream& fin);
	vector<string> dictionary_helper(ifstream& file, int size);
	void load_Dictionary();
	void initializeGame();

public:
	Game() : level(0), duration(10){
		initializeGame();
	}
	void ChangeSettings(int user_level, int user_duration);
	void UpdateSettingsFile();
	void PrintSettings();
	string RandomSentence();
	void PrintRemainingSentence(string sentence, int j);
	int GetLevel();
	int GetDuration();
	float StartGame();
	void SettingsMenu();

};

	