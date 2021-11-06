#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <qdebug.h>
#include <QVector>

class Scoreboard
{
public:
    Scoreboard();
    bool Add_Score(QString level, QString user, int score);

    Scoreboard Differences(Scoreboard* other);
    void Order_Scores(QString key);
    void Merge(Scoreboard* other);                  // later if needed
    int Get_length();

    void Show_Scoreboard();

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
};

#endif // SCOREBOARD_H
