#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>
#include <vector>

struct ScoreEntry {
    std::string playerName;
    int score;
};

class HighScore {
private:
    static const std::string FILENAME;
    static const int MAX_ENTRIES = 5;
    mutable std::vector<ScoreEntry> scores;
    
    void LoadScores();
    void SaveScores();
    void SortScores();
    void EnsureLoaded() const;
    
public:
    HighScore();
    bool IsHighScore(int score) const;
    void AddScore(const std::string& name, int score);
    void DisplayScores() const;
};

#endif