#include <util.h>

namespace Random {
namespace {
std::mt19937 randGen(static_cast<unsigned long>(std::chrono::steady_clock::now()
																										.time_since_epoch()
																										.count()));
}

int getInt(void) {
	int i = static_cast<int>(randGen());
	return i < 0 ? -i : i;
}
}
