#include <bitset>
#include <cstdio>
#include <random>
#include <stdint.h>

enum Direction {
	RIGHT,
	LEFT,
	UP,
	DOWN
};

struct PatternSet64 {
	PatternSet64() {
		pattern = std::bitset<64>{};
		maxSide = 8;
	}

	bool setAll() {
		pattern.set();
		return true;
	}

	bool unsetAll() {
		pattern.reset();
		return true;
	}

	bool invert() {
		pattern.flip();
		return true;
	}

	bool set(int index) {
		if (index > 64) {
			// throw index out of bounds exception
			return false;
		}
		pattern.set(index, 1);
		return true;
	}

	bool unset(int index) {
		if (index > 64) {
			// throw index out of bounds exception
			return false;
		}
		pattern.reset(index);
		return true;
	}

        bool setToRandom() {
		std::random_device rd;
    		std::mt19937_64 e2(rd());
		std::uniform_int_distribution<uint64_t> dist(std::llround(std::pow(2,61)), std::llround(std::pow(2,62)));
		uint64_t randomInt64 = dist(e2);
		pattern = std::bitset<64>{randomInt64};
	}	

	// should be copy or readonly?
	std::bitset<64> getPattern() {
		return pattern;
	}

	// readonly
	void printPattern() {
		printf("Pattern\n");		
		for (int i=0; i<8; i++) {
			for (int j=0; j<8; j++) {
				int current = (i*8)+j;
				printf("%s ", pattern.test(current) ? "*" : "-");
			}
			printf("\n");
		}
		printf("\n");
	}

	// readonly
	int compare(std::bitset<64> other) {
		auto result = std::bitset<64>{};
		// set result to pattern
		result |= pattern;

		// return count of common bits
		result &= other;
		return result.count();
	}

	// NOTE destructive operation
	// NOTE Work in progress
	// this ultimately needs to copy to a larger bit array
	// to deal with clipping
	// and should also do better bounds checking
	bool shift(Direction direction, int count) {
		if (count > maxSide) {
			// for now we'll truncate
			count = maxSide;
		}
		// TODO result will contain more info about the operation
		bool result = false;
		switch (direction) {
			case RIGHT:
				pattern <<= count;
				result = true;
				break;
			case LEFT :
				pattern >>= count;
				result = true;
				break;
			case UP   :
				pattern >>= (count * maxSide);
				result = true;
				break;
			case DOWN :
				pattern <<= (count * maxSide);
				result = true;
				break;
		        default   :
				result = false;
				break;
		}
		return result;
	}


private:
	std::bitset<64> pattern;
	int maxSide;
};

int main() {
	// quick test generation methods
	auto myPattern = PatternSet64{};
	myPattern.setAll();
	//myPattern.printPattern();

	myPattern.unsetAll();
	myPattern.set(3);
	myPattern.set(10);
	myPattern.set(12);
	myPattern.set(19);
	myPattern.printPattern();

	myPattern.shift(Direction::RIGHT, 2);
	myPattern.printPattern();
	myPattern.shift(Direction::LEFT, 4);
	myPattern.printPattern();

	myPattern.shift(Direction::DOWN, 4);
	myPattern.printPattern();
	myPattern.shift(Direction::UP, 4);
	myPattern.printPattern();


	myPattern.invert();
	//myPattern.printPattern();

	myPattern.setToRandom();
	//myPattern.printPattern();

	// test set comparison
	auto starterBitset = PatternSet64{};
	starterBitset.set(0);
	//starterBitset.printPattern();

	myPattern.setAll();
	int result1= starterBitset.compare(myPattern.getPattern());
	//printf("Result: %d\n", result1);
	starterBitset.invert();
	int result2 = starterBitset.compare(myPattern.getPattern());
	//printf("Result: %d\n", result2);
}

