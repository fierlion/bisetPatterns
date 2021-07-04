#include <bitset>
#include <cstdio>

struct PatternSet64 {
	PatternSet64() {
		pattern = std::bitset<64>{};
	}


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
	

private:
	std::bitset<64> pattern;
};

int main() {
	auto starterBitset = std::bitset<64>{};
	starterBitset.set();

	auto myPattern = PatternSet64{};
	myPattern.printPattern();
	myPattern.setAll();
	myPattern.printPattern();
	myPattern.unsetAll();
	myPattern.set(0);
	myPattern.set(5);
	myPattern.set(63);
	myPattern.set(65);
	myPattern.printPattern();
	myPattern.invert();
	myPattern.printPattern();
}

