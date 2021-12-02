#include "scoreboard.h"

Scoreboard::Scoreboard() {
	length = 0;
	head = nullptr;
	tail = nullptr;
}

    // adds a new entry to the scoreboard from pass parameters
void Scoreboard::add(QString user, QDateTime time, long score) {
	Entry* temp = new Entry();
	temp->user = user;
	temp->score = score;
	temp->next = nullptr;
	temp->last = tail;
	temp->time = time;
	if (tail)
		tail->next = temp;
	else
		head = temp;
	tail = temp;
	length++;
}
    // adds a new entry that is passed in
void Scoreboard::add(Entry* add) {
	if (tail)
		tail->next = add;
	else
		head = add;
	tail = add;
	length++;
}

    // sorts the entries in decending score order, with index 0
     // being the high score
void Scoreboard::sort() {
	long pass;
	if (head != nullptr && head->next != nullptr) {
		Entry* temp = head->next;
		Entry* start = head->next;
		Entry* hold;
		while (start != nullptr) {
			pass = temp->score;
			while (temp->last != nullptr && pass > temp->last->score) {
				hold = temp->last;
				swap(hold, temp);
			}
			start = start->next;
			temp = start;
		}
	}
}
    // displays the scoreboard to application output
void Scoreboard::show() {
	sort();
	Entry* temp = head;
	qDebug() << head;

	while (temp != nullptr) {
		qDebug() << temp->score;
		qDebug() << temp->time;
		qDebug() << temp->user;
		qDebug() << "";
		temp = temp->next;
	}
}

    // returns a Scoreboard object that has all of the entries
     // in the current object that are not in other
Scoreboard* Scoreboard::extraHere(Scoreboard* other) {

	Scoreboard* diff = new Scoreboard();
	Entry* temp = head;
	long current;
	while (temp != nullptr) {
		current = other->exists(temp);
		if (current == -1) {
			diff->add(temp);
    }

		temp = temp->next;
	}
	return diff;
}

    // returns # of entries in scoreboard
int Scoreboard::getLength() { return length; }

    // swaps the location of 2 entries passed
void Scoreboard::swap(Entry* left, Entry* right) {
	Entry* pointers[2];
	pointers[0] = left->last;
	pointers[1] = right->next;

	right->last = left->last;
	left->next = right->next;
	right->next = left;
	left->last = right;

	if (pointers[0] != nullptr) {
		pointers[0]->next = right;
	} else {
		head = right;
	}

	if (pointers[1] != nullptr) {
		pointers[1]->last = left;
	} else {
		tail = left;
	}
}

    // returns the pointer to the entry at index in scoreboard
Scoreboard::Entry* Scoreboard::get(int index) {
	Entry* temp = head;
	if (getLength() > index) {
		for (int i = 0; i < index; i++) {
			if (temp->next == nullptr)  // if the index is greater than the range
			{
				break;  // of the score list, return last element in list
			}
			temp = temp->next;
		}
	} else {
		temp = new Entry();
	}

	return temp;
}

    // Sees if the passed extry exists in the scoreboard
int Scoreboard::exists(Entry* checker) {
	int index = -1;
	int count = 0;
	QDateTime Ctime = checker->time;
	Entry* temp = head;
	while (index == -1 && temp != nullptr) {
		if (temp->time == Ctime)  // Checks first if the times match then
        {
			if (equal(checker, temp)) {
				index = count;
				break;
			}
        }
		count++;
		temp = temp->next;
	}
	return index;
}

    // checks if 2 entries are the same
bool Scoreboard::equal(Entry* A, Entry* B) {
	return (A->user == B->user && A->score == B->score && A->time == B->time);
}
