#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "headers/scoreboard.h"

using namespace std;

ScoreBoard::ScoreBoard() {
    read();
}

void ScoreBoard::read() {
    // Read mode
    ifstream high_score_file;
    string line, score_txt, date_txt, time_txt;

    high_score_file.open("high_score.txt");

    if (high_score_file.is_open()) {
        // Read text file line by line
        for (n_lines = 0; getline(high_score_file, line) && n_lines < 10; n_lines++) {
            istringstream iss(line);
            iss >> score_txt >> date_txt >> time_txt;
            scoreboard_[n_lines].date_time = date_txt + "  " + time_txt;
            scoreboard_[n_lines].score = score_txt;
        }

        high_score_file.close();
    }
}

string ScoreBoard::getCurrentDateTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    ostringstream oss;
    oss << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << "  "
        << setfill('0') << setw(2) << ltm->tm_hour << ":"
        << setfill('0') << setw(2) << ltm->tm_min;
    return oss.str();
}

void ScoreBoard::write(int score) {
    // Write mode
    ofstream high_score_file;
    string date_time = getCurrentDateTime();
    bool is_write = false;

    high_score_file.open("high_score.txt");

    int i = 0, line = 0;
    for (; i < n_lines && line < 10; i++, line++) {
        if (!is_write && score >= stoi(scoreboard_[i].score) ) {
            high_score_file << score << " " << date_time << endl;
            is_write = true, line++;
        }
        if (line < 10)
            high_score_file << scoreboard_[i].score << " " << scoreboard_[i].date_time << endl;
    }
    if (!is_write && line < 10) {
        high_score_file << score << " " << date_time << endl;
    }

    high_score_file.close();

    read();
}

string ScoreBoard::getHighScoreByIndex(int index) {
    return index >= 0 && index < n_lines ? scoreboard_[index].score : "-";
}

string ScoreBoard::getDateTimeByIndex(int index) {
    return index >= 0 && index < n_lines ? scoreboard_[index].date_time : "-";
}