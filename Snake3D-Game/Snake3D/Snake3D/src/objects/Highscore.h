#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <filesystem>

#include "..\tools\Logger.h"

struct HighscoreEntry {
    std::string date;
    std::string name;
    int score;
};

class Highscore {
public:
    Highscore();
 
    void addEntry(const std::string& name, int punkte);
    std::vector<HighscoreEntry> loadTop10();

private:
    std::string filename;

    std::vector<HighscoreEntry> loadEntries();
    void saveEntries(const std::vector<HighscoreEntry>& eintraege);
    std::string getDate();
};