#include "UserLibrary.h"

string UserLibrary::User::GetName() {
    return name;
}
float UserLibrary::User::GetEasyScore() {
    return easyScore;
}
float UserLibrary::User::GetMediumScore() {
    return mediumScore;
}
float UserLibrary::User::GetHardScore() {
    return hardScore;
}

void UserLibrary::User::UpdateEasyScore(float newScore) {
    if (newScore > easyScore) {
        cout << "A New Record!\n"; 
        easyScore = newScore;
    }
}
void UserLibrary::User::UpdateMediumScore(float newScore) {
    if (newScore > mediumScore) {
        cout << "A New Record!\n"; 
        mediumScore = newScore;
    }
}
void UserLibrary::User::UpdateHardScore(float newScore) {
    if (newScore > hardScore) {
        cout << "A New Record!\n"; 			
        hardScore = newScore;
    }
}

void UserLibrary::User::printUserInfo() {
    cout << name << '\n';
}


void UserLibrary::initializeUserLibrary() {
    string user_name;
    float user_easyScore,user_mediumScore,user_hardScore;
    ifstream readPlayers("players.txt");
    
    int players = findSize(readPlayers);
    readPlayers.close();

    if (players <= 1) {
        enterUser("Guest");
        return;
    }

    readPlayers.open("players.txt");
    
    for (int i = 1; i < players; i++) {
        getline(readPlayers,user_name,'\t');
        readPlayers >> user_easyScore;
        readPlayers >> user_mediumScore;
        readPlayers >> user_hardScore;
        readPlayers.ignore();
        
        enterUser(user_name,user_easyScore,user_mediumScore,user_hardScore);
    }
    readPlayers >> current_user;
    readPlayers.close();
}

int UserLibrary::findSize(ifstream& fin) {   
    int size = 1;
    char temp = fin.get();

    while (fin.get(temp)) {
        if (temp == '\n') {
            size++;
        }
    }
    return size;
}

void UserLibrary::updatePlayersFile() {
    ofstream writePlayers("players.txt");
    
    for (int i = 0; i < users.size(); i++) {
        writePlayers << users[i].GetName() << '\t' << users[i].GetEasyScore() 
        << '\t' << users[i].GetMediumScore() << '\t' << users[i].GetHardScore() << '\n';
    }
    writePlayers << current_user;
    writePlayers.close();
}

void UserLibrary::enterUser(string user_name, float user_easyScore, float user_mediumScore, float user_hardScore) {

    if (user_name == "") {
        return;
    }

    bool is_new_user = true;

    int i = 0;
    for (; i < users.size(); i++) {
        if (users[i].GetName() == user_name) {
            current_user = i;
            is_new_user = false;
            i = users.size() -1;
        }
    }

    if (is_new_user == true) {
        current_user = i;
        users.push_back(User(user_name,user_easyScore,user_mediumScore,user_hardScore));
    }
}

void UserLibrary::leaderboard(int level) {
    cout << "\nThe Leaderboards for this level:\n";
    
    if (level == 0) {
        for (int i = 0; i < users.size(); i++) {
            cout << users[i].GetName() << '\t' << users[i].GetEasyScore() << '\n';
        }
    }
    else if (level == 1) {
        for (int i = 0; i < users.size(); i++) {
            cout << users[i].GetName() << '\t' << users[i].GetMediumScore() << '\n';
        }
    }
    else {
        for (int i = 0; i < users.size(); i++) {
            cout << users[i].GetName() << '\t' << users[i].GetHardScore() << '\n';
        }
    }
    cout << '\n';
}

void UserLibrary::updateScore(int level,float score) {
    
    if (level == 0) {
        users[current_user].UpdateEasyScore(score);
    }
    if (level == 1) {
        users[current_user].UpdateMediumScore(score);
    }
    if (level == 2) {
        users[current_user].UpdateHardScore(score);
    }
}

void UserLibrary::printCurrentUser() {
    cout << "Current User: ";
    users[current_user].printUserInfo();
}

void UserLibrary::loginMenu() {
    string user_name;	
    cout << "enter user name: ";
    cin >> user_name;
    enterUser(user_name);
    updatePlayersFile();
}

