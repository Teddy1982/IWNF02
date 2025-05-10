#include <chrono>
#include <ctime>

#include "Highscore.h"

Highscore::Highscore() {
    filename = "data/Highscores.txt";
    if (!std::filesystem::exists(filename)) {
        if (!std::filesystem::exists("data")) {
            std::filesystem::create_directory("data");
        }
        std::ofstream ofs(filename);
        if (!ofs) {
            Logger::log(2, "error while creating '%s'\n", filename.c_str());
        }
    }
}

void Highscore::addEntry(const std::string& name, int score) {
    std::vector<HighscoreEntry> entries = loadEntries();

    HighscoreEntry newEntry;
    newEntry.date = getDate();
    newEntry.name = name;
    newEntry.score = score;
    entries.push_back(newEntry);

    std::sort(entries.begin(), entries.end(), [](const HighscoreEntry& a, const HighscoreEntry& b) {
        return a.score > b.score;
        });

    saveEntries(entries);
}

std::vector<HighscoreEntry> Highscore::loadTop10() {
    std::vector<HighscoreEntry> entries = loadEntries();

    std::sort(entries.begin(), entries.end(), [](const HighscoreEntry& a, const HighscoreEntry& b) {
        return a.score > b.score;
        });

    if (entries.size() > 10) {
        entries.resize(10);
        saveEntries(entries);
    }

    return entries;
}

std::vector<HighscoreEntry> Highscore::loadEntries() {
    std::vector<HighscoreEntry> entries;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        HighscoreEntry entry;
        entry.date = line;

        if (!std::getline(file, line)) break;
        entry.name = line;

        if (!std::getline(file, line)) break;
        entry.score = std::stoi(line);

        entries.push_back(entry);
    }

    return entries;
}

void Highscore::saveEntries(const std::vector<HighscoreEntry>& entries) {
    std::ofstream file(filename, std::ios::trunc);
    for (const auto& entry : entries) {
        file << entry.date << "\n" << entry.name << "\n" << entry.score << "\n";
    }
}

std::string Highscore::getDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t jetzt = std::chrono::system_clock::to_time_t(now);
    std::tm localTime;

#ifdef _WIN32
    localtime_s(&localTime, &jetzt);  // Windows
#else
    localtime_r(&jetzt, &localTime);  // Unix/Linux
#endif

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%d.%m.%Y");
    return oss.str();
}