#include "scoreboard.h"

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
        int pass;
        int middle;
        run* temp = head->next;
        run* start = head->next;
        while(start != nullptr)
        {
            pass = temp->score;
            while(temp->last != nullptr && pass < temp->last->score)
            {
                temp = temp->last;
            }
            middle = temp->score;
            temp->score = start->score;
            start->score = middle;

            start = start->next;
        }
    }
}

void Scoreboard::Show_Scoreboard()
{
    run* temp = head;
    while(temp != nullptr)
    {
        qDebug() << temp->score;
        temp = temp->next;
    }
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


