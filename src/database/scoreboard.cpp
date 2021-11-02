#include "scoreboard.h"
#include <QDialog>

Scoreboard::Scoreboard()
{
    length = 0;
    head = nullptr;
    tail = nullptr;

}

bool Scoreboard::Add_Score(QString level, QString user, int score)
{
    bool works = true;

    run* temp = new run();
    temp->level = level;
    temp->user = user;
    temp->score = score;
    temp->next = nullptr;
    temp->last = tail;

    tail->next = temp;
    tail = temp;

    return works;
}


void Scoreboard::Show_Scoreboard() : QDialog()
{


}
