#include "scoreboard.h"



Scoreboard::Scoreboard(QString lev)
{
    level = lev;
    length = 0;
    head = nullptr;
    tail = nullptr;

}

void Scoreboard::Add_Score(QString level, QString user, QDateTime time, int score)
{
    run* temp = new run();
    //temp->level = level;
    //qDebug() << "temp made";
    temp->level = level;
    temp->user = user;
    temp->score = score;
    temp->next = nullptr;
    temp->last = tail;
    temp->time = time;

    // add date

    //qDebug() << "temp pop";

    if(tail)
    {
        tail->next = temp;
    }
    else
    {
        head = temp;
    }
    //qDebug() << "tail->next";

    tail = temp;

    //qDebug() << "tail";

    length++;
}

void Scoreboard::Add_Score(run* add)
{
        if(tail)
        {
            tail->next = add;
        }
        else
        {
            head = add;
        }

        tail = add;

        length++;
}


void Scoreboard::Order_Scores(QString key)
{
    if(key == "Accending_Score")
    {
        int pass;
        run* temp = head->next;
        run* start = head->next;
        run* hold;
        while(start != nullptr)
        {
            pass = temp->score;
            while(temp->last != nullptr && pass < temp->last->score)
            {
                hold = temp->last;
                Swap_Adjectent_Runs(hold, temp);
                qDebug() << "\n";
                Show_Scoreboard();
            }

            start = start->next;
            temp = start;
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

Scoreboard* Scoreboard::Extra_Here(Scoreboard* other)
{
    // returns a Scoreboard object that has all of the runs from
    // current object that are not in other
    Scoreboard* diff = new Scoreboard(level);
    run* temp = head;
    int current;
    while(temp != nullptr)
    {
        current = other->Exists(temp);
        if(current == -1)
        {
            diff->Add_Score(temp);
        }

        temp = temp->next;
    }
    return diff;
}

void Scoreboard::Merge(Scoreboard* other)
{

}

int Scoreboard::Get_length()
{
    return length;
}

void Scoreboard::Swap_Adjectent_Runs(run* left, run* right)
{
//    qDebug() << "\nSwap Start";
//    qDebug() << left->last;
//    qDebug() << left;
//    qDebug() << left->score;
//    qDebug() << "\n";
//    qDebug() << left->next;
//    qDebug() << right->last;
//    qDebug() << right;
//    qDebug() << right->score;
//    qDebug() << right->next;
//    qDebug() << "\n";


    run* pointers[2];
    pointers[0] = left->last;
    pointers[1] = right->next;

    right->last = left->last;
    left->next = right->next;
    right->next = left;
    left->last = right;

    if(pointers[0] != nullptr)
    {
        pointers[0]->next = right;
    }
    else {
        head = right;
    }

    if(pointers[1] != nullptr)
    {
        pointers[1]->last = left;
    }
    else {
        tail =left;
    }




//    qDebug() << "\nSwap";
//    qDebug() << right->last;
//    qDebug() << right;
//    qDebug() << right->score;
//    qDebug() << right->next;
//    qDebug() << "\n";
//    qDebug() << left->last;
//    qDebug() << left;
//    qDebug() << left->score;

//    qDebug() << left->next;
}

Scoreboard::run* Scoreboard::Get_Run(int index)
{
    run* temp = head;
    for(int i = 0; i < index; i++)
    {
        if(temp->next == nullptr)               // if the index is greater than the range
        {
            break;                              // of the score list, return last element in list
        }
        temp = temp->next;
    }
    return temp;

}

QString Scoreboard::Get_Level()
{
    return level;
}

int Scoreboard::Exists(run* checker)
{
    int index = -1;
    int count = 0;
    QDateTime Ctime = checker->time;
    run* temp = head;
    while(index == -1 && temp != nullptr)
    {
        if(temp->time == Ctime)         // Checks first if the times match then
        {
            if(Runs_Equal(checker, temp))
            {
               index = count;
               break;
            }
        }
        count++;
    }
    return index;
}


bool Scoreboard::Runs_Equal(run* A, run* B)
{
    return (A->level == B->level && A->user == B->user && A->score == B->score && A->time == B->time);
}
