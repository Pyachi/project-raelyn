#include "scoreboard.h"
#include <QDialog>
#include <QGridLayout>

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

    length++;
    return works;
}


void Scoreboard::Order_Scores(QString key)
{

    if(key == "Accending_Score")
    {
        QVector<int> scores;
        QVector<run*> addresses;
        run* temp = head;
        while(temp != nullptr)
        {
            scores.append(temp->score);
            addresses.append(temp);





            temp = temp->next;
        }
    }
}

void Scoreboard::Show_Scoreboard()
{
    

}

Scoreboard Scoreboard::Differences(Scoreboard* other)
{
    Scoreboard diff = Scoreboard();
}

void Scoreboard::Merge(Scoreboard* other)
{

}

int Scoreboard::Get_length()
{
    return length;
}


