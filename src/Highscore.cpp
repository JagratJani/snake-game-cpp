#include "HighScore.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <conio.h>

using namespace std;

const string HighScore::FILENAME = "highscores.txt";

HighScore::HighScore() {
    scores.clear();
}

void HighScore::EnsureLoaded() const {
    if (scores.empty()) {
        const_cast<HighScore*>(this)->LoadScores();
    }
}

void HighScore::LoadScores() {
    ifstream file(FILENAME);
    
    if (file.is_open()) {
        string name;
        int score;
        
        while (file >> name >> score && scores.size() < MAX_ENTRIES) {
            scores.push_back({name, score});
        }
        file.close();
    }
    
    // Ensure we always have some default scores
    if (scores.empty()) {
        scores = {
            {"AAA", 0},
            {"BBB", 0},
            {"CCC", 0},
            {"DDD", 0},
            {"EEE", 0}
        };
    }
    
    SortScores();
}

void HighScore::SaveScores() {
    ofstream file(FILENAME);
    if (file.is_open()) {
        for (const auto& entry : scores) {
            file << entry.playerName << " " << entry.score << endl;
        }
        file.close();
    }
}

void HighScore::SortScores() {
    sort(scores.begin(), scores.end(), 
        [](const ScoreEntry& a, const ScoreEntry& b) {
            return a.score > b.score;
        });
    
    if (scores.size() > MAX_ENTRIES) {
        scores.resize(MAX_ENTRIES);
    }
}

bool HighScore::IsHighScore(int score) const {
    EnsureLoaded();
    return scores.size() < MAX_ENTRIES || score > scores.back().score;
}

void HighScore::AddScore(const std::string& name, int score) {
    EnsureLoaded();
    scores.push_back({name, score});
    SortScores();
    SaveScores();
}

void HighScore::DisplayScores() const {
    EnsureLoaded();
    
    system("cls");
    cout << "###############################" << endl;
    cout << "#        HIGH SCORES         #" << endl;
    cout << "###############################" << endl;
    cout << endl;
    
    for (size_t i = 0; i < scores.size(); i++) {
        cout << " " << (i + 1) << ". " << scores[i].playerName 
             << " ........ " << scores[i].score << endl;
    }
    
    cout << endl;
    cout << "Press any key to continue..." << endl;
    _getch();
}