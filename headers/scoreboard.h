#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>

class ScoreBoard {
    protected:
        int n_lines;
        struct HighScoreText {
            std::string date_time;
            std::string score;
        } scoreboard_[10];

        std::string getCurrentDateTime();
    public:
        ScoreBoard();
        
        void write(int score);

        void read();
        std::string getHighScoreByIndex(int index);
        std::string getDateTimeByIndex(int index);
};

#endif // SCOREBOARD_H