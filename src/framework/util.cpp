#include <util.h>
#include <chrono>

namespace Random {
namespace {
std::mt19937 randGen(static_cast<unsigned long>(
		std::chrono::steady_clock::now().time_since_epoch().count()));
}

int getInt(void) {
  int i = static_cast<int>(randGen());
  return i < 0 ? -i : i;
}

int getInt(int max) {
	int i = static_cast<int>(randGen());
	i = i < 0 ? -i : i;
	return i % max;
}

double getDouble(double max) {
	int i = static_cast<int>(randGen());
	i = i < 0 ? -i : i;
	return static_cast<double>(i) / static_cast<double>(INT_MAX / max);
}
}  // namespace Random
