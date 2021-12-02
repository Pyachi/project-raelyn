#include "scoreboard.h"
#include <algorithm>
#include "database.h"

// adds a new entry that is passed in
void Scoreboard::add(const Entry& add) {
	for (auto i = entries.begin(); i != entries.end(); i++) {
		if (i->score < add.score) {
			entries.insert(i, add);
			break;
		}
	}
}
