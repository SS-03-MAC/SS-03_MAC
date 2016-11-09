#include <cstdint>
#include <cassert>

class uint24_t {
public:
  uint32_t value : 24;
};


int main() {
	uint24_t v;
	v.value = 0;
	uint64_t a = 0;

	uint32_t max = 1 << 24;

	for (a = 0; a < (1l << 34); a++) {
		assert(v.value < max);
		v.value += 1;
	}
}
