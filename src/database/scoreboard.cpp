#include "scoreboard.h"
#include <algorithm>
#include "database.h"

// adds a new entry that is passed in
void Scoreboard::add(const Entry& add) {
	Database::get().add(add);
	if (entries.empty()) {
		entries.push_back(add);
		return;
	}
	for (auto i = entries.begin(); i != entries.end(); i++)
		if (i->score < add.score) {
			entries.insert(i, add);
			return;
		}
	entries.push_back(add);
}
