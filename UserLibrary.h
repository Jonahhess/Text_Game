#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


class UserLibrary {

protected:
	class User {
		string name;
		float easyScore, mediumScore, hardScore;

	public:
		User(string init_name = "", float init_easyScore = 0, float init_mediumScore = 0, float init_hardScore = 0) 
			 : name(init_name), easyScore(init_easyScore), mediumScore(init_mediumScore), hardScore(init_hardScore) {}

		string GetName();
		float GetEasyScore();
		float GetMediumScore();
		float GetHardScore();
		void UpdateEasyScore(float newScore);
		void UpdateMediumScore(float newScore);
		void UpdateHardScore(float newScore);
		void printUserInfo();
	};

private:
	vector<User> users;
	int current_user;

	void initializeUserLibrary();

public:
	UserLibrary() : users(), current_user(0) {
		initializeUserLibrary();
		updatePlayersFile();
	}

	int findSize(ifstream& fin);
	void updatePlayersFile();
	void enterUser(string user_name, float user_easyScore = 0, float user_mediumScore = 0, float user_hardScore = 0);
	void leaderboard(int level);
	void updateScore(int level,float score);
	void printCurrentUser();
	void loginMenu();
};
