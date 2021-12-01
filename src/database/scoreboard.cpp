#include "scoreboard.h"

Scoreboard::Scoreboard() {
	length = 0;
	head = nullptr;
	tail = nullptr;
}

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

void Scoreboard::add(Entry* add) {
	if (tail)
		tail->next = add;
	else
		head = add;
	tail = add;
	length++;
}

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

Scoreboard* Scoreboard::extraHere(Scoreboard* other) {
	// returns a Scoreboard object that has all of the runs from
	// current object that are not in other
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

int Scoreboard::getLength() { return length; }

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

int Scoreboard::exists(Entry* checker) {
	int index = -1;
	int count = 0;
	QDateTime Ctime = checker->time;
	Entry* temp = head;
	while (index == -1 && temp != nullptr) {
		//        qDebug() << temp;
		//        qDebug() << temp->time;
		//        qDebug() << Ctime;
		//        qDebug() << "";
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

long Scoreboard::getHighScore() {
	sort();
	return get(0)->score;
}

bool Scoreboard::equal(Entry* A, Entry* B) {
	return (A->user == B->user && A->score == B->score && A->time == B->time);
}
