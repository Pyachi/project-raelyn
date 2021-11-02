#ifndef SCOREBOARD_H
#define SCOREBOARD_H


#include <qdebug.h>


class Scoreboard
{
public:
    Scoreboard();
    bool Add_Score(QString level, QString user, int score);

private:
    int length;




    struct run
    {
        QString level;
        QString user;
        int score;
        run* next;
        run* last;
    };

    run* head;
    run* tail;

    void Show_Scoreboard();
};

#endif // SCOREBOARD_H
