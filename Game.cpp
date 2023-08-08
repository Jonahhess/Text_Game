#include "Game.h"

void Game::initializeGame() {
    int fileLevel,fileDuration;
    ifstream readSettings("settings.txt");
    readSettings >> fileLevel >> fileDuration;
    readSettings.close();
    ChangeSettings(fileLevel,fileDuration);
    UpdateSettingsFile();
}

int Game::findSize(ifstream& fin) {   
    int size = 1;
    char temp = fin.get();

    while (fin.get(temp)) {
        if (temp == '\n') {
            size++;
        }
    }
    return size;
}

vector<string> Game::dictionary_helper(ifstream& file, int size) {

    if (dictionary.empty() == false) {
        dictionary.clear();
    }

    if (size < 1) {
            return dictionary;
    }

    string s1;
    for (int i = 0; i < size; i++) {
        getline(file,s1,'\n');
        if (s1 != "") {
            dictionary.push_back(s1);
        }
    }
    
    return dictionary;
}

void Game::load_Dictionary() {
    int size;
    ifstream fin;
    
    if (level == 2) {
        fin.open("hard.txt");
        size = findSize(fin);
        fin.close();
        fin.open("hard.txt");
        dictionary = dictionary_helper(fin,size);
    }
    else if (level == 1) {
        fin.open("medium.txt");
        size = findSize(fin);
        fin.close();
        fin.open("medium.txt");
        dictionary = dictionary_helper(fin,size);
    }
    else {
        fin.open("easy.txt");
        size = findSize(fin);
        fin.close();
        fin.open("easy.txt");
        dictionary = dictionary_helper(fin,size);
    }
    cout << "Number of Sentences: " << dictionary.size() << '\n';
    fin.close();
}

void Game::ChangeSettings(int user_level, int user_duration) {

    bool legalChange = false;

    if (user_level >= 0 && user_level <= 2) {
        if (level != user_level) {
            legalChange = true;
            level = user_level;
        }
    }

    if (user_duration >= 1 && user_duration <= 20) {
        duration = user_duration;
    }

    // on init or level change
    if (legalChange == true || dictionary.size() == 0) {
        load_Dictionary();
    }
}

void Game::UpdateSettingsFile() {
    ofstream writeSettings("settings.txt");
    writeSettings << level << ' ' << duration;
}

void Game::PrintSettings() {
    cout << "Level: " << level << "\nDuration: " << duration << '\n';
}

string Game::RandomSentence() {
    if (dictionary.size() < 1) {
        return "dictionary empty";
    }

    return dictionary[rand() % dictionary.size()];
}

int Game::GetLevel() {
    return level;
}

int Game::GetDuration() {
    return duration;
}

float Game::StartGame() {
    string sentence;
    float score;
    char letter;
    int totalLetters = 0;
    bool stop = false;
    int letterLimit = 0;
    int lettersTyped = 0;
    
    std::cout << "\npress ~ to quit\n\n";
    
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < GetDuration(); i++) {

        sentence = RandomSentence();
        totalLetters += sentence.size();
        
        for (int j = 0; j < sentence.size() && stop == false; j++) {	
            letterLimit = sentence.size() * 2;
            do {
                std::cin.get(letter);
                
                if (lettersTyped++ > letterLimit || letter == '~') {
                    stop = true;
                } else if (letter == '*') {
                    break;
                } else if (letter == '\n') {
                    std::cout << sentence.substr(j,sentence.size()-j) << '\n';
                }
            }
            while (letter != sentence[j] && stop == false);
        }
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    float seconds = duration.count();

    score = (stop == false) * totalLetters * 12 / seconds;
    cout << "\nYour score: " << score << '\n';

    return score;
}

void Game::SettingsMenu() {
        int user_level, user_duration;
        
        cout << "enter lvl:\n";
        cin >> user_level;
        cout << "enter duration:\n";
        cin >> user_duration;
        ChangeSettings(user_level, user_duration);
        UpdateSettingsFile();
}