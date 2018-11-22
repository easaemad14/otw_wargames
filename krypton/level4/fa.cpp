#include <string.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

#define KEY_SIZE 6
#define UPPER_OFFSET 65 // Man ascii

int main()
{
	vector<string> cVec; // Vector of 6-byte cipher strings
	int fa[KEY_SIZE][26];
	string buf;
	ifstream f1("found1"), f2("found2");
	ofstream counts("counts");

	memset(fa, 0, sizeof(fa));

	if(not f1.is_open() or not f2.is_open()) {
		cerr << "Unable to open ciphertexts!" << endl;
	}
	if(not counts.is_open()) {
		cerr << "Unable to open output file!" << endl;
	}

	// Fill the vectors
	while(getline(f1, buf)) {
		cVec.push_back(buf);
	}
	while(getline(f2, buf)) {
		cVec.push_back(buf);
	}

	// Do some counting
	for(auto s : cVec) {
		for(size_t i{0}; i < KEY_SIZE; i++) {
			if(s.size() <= i) {
				break;
			}
			++fa[i][s.at(i) - UPPER_OFFSET];
		}
	}

	// Spit out counts
	for(int i{0}; i < KEY_SIZE; i++) {
		counts << endl << "Position " << to_string(i) << ": " << endl;
		for(int j{0}; j < 26; j++) {
			counts << static_cast<char>(j + UPPER_OFFSET) << ": " << to_string(fa[i][j]) << endl;
		}
	}
}
