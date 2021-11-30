#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <qdebug.h>
#include <QVector>
#include <QDateTime>
class Scoreboard
{
public:
    struct run
    {
        QString user;
        long score;
        QDateTime time;
        run* next;
        run* last;
    };

    Scoreboard();
    void Add_Score(QString user, QDateTime time, long score);
    void Add_Score(run* add);

    Scoreboard* Extra_Here(Scoreboard* other);
    void Order_Scores(QString key);
    int Get_length();
    long Get_High_Score();

    void Show_Scoreboard();
    run* Get_Run(int index);
    QString Get_Level();



private:
    int length;

    QString level;

    void Swap_Adjectent_Runs(run* left, run* right);
    int Exists(run* checker);
    bool Runs_Equal(run* A, run* B);


    run* head;
    run* tail;
};

#endif // SCOREBOARD_H
