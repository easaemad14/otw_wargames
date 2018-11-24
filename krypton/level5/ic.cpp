#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

static const unsigned int maxKeySize{20};
static const unsigned int alphaSize{26};
static const unsigned int upperOffset{65};


// Calculate IC from string
// https://en.wikipedia.org/wiki/Index_of_coincidence#Calculation
float calcIC(string& str)
{
	float retVal{0};
	int counts[alphaSize];
	memset(counts, 0, sizeof(counts));

	// Some error checking is always good
	if(str.length() < 2) {
		return 1; // Normalize towards one
	}

	// Count all characters
	for(auto c : str) {
		if(not isupper(c)) {
			cerr << "Non-uppercase character passed: " << c << endl;
			continue;
		}
		++counts[c - upperOffset];
	}

	// Calculate IC from counts
	for(auto i{0}; i < alphaSize; i++) {
		retVal += static_cast<float>(alphaSize) * counts[i] * (counts[i] - 1) / 
			str.length() / (str.length() - 1);
	}
	return retVal;
}

// Calculate IC from string, based off of substring size len
float calcICFromKey(string& str, unsigned int len)
{
	float retVal{0};
	vector<float> ics;

	// Need to create a vector of strings based off of guessed key size len
	vector<string> subs;
	for(auto i{0}; i < str.length(); i += len) {
		auto s = str.substr(i, len);
		subs.push_back(s);
	}

	// Calculate IC of each column
	for(auto i{0}; i < len; i++) {
		string col;
		for(auto j{0}; j < subs.size(); j++) {
			try { // This is easier than error checking :)
				col.push_back(subs.at(j).at(i));
			} catch(...) { // We wen't out of bounds
				break;
			}
		}
		ics.push_back(calcIC(col));
	}

	// Calculate average of IC values? and return
	for(auto f : ics) {
		retVal += f / ics.size();
	}
	return retVal;
}

int main()
{
	string buf;
	ifstream f1("found1"), f2("found2"), f3("found3");
	vector<ifstream*> ifs { &f1, &f2, &f3 };
	ofstream os("ic.out");

	// Ensure files are open
	for(auto f : ifs) {
		if(not f->is_open()) {
			cerr << "Unable to open ciphertext!" << endl;
			return 1;
		}
	}
	if(not os.is_open()) {
		cerr << "Could not open output stream!" << endl;
		return 1;
	}

	// Read the line from every file and calculate IC by key size
	for(auto i{0u}; i < ifs.size(); i++) {
		if(not getline(*ifs.at(i), buf)) {
			cerr << "Could not read from ciphertext; aborting!" << endl;
			return 1;
		}

		os << endl << "found" << to_string(i + 1) << endl;
		for(auto j{1u}; j <= maxKeySize; j++) {
			os << "IC for keysize " << to_string(j) << ": " << 
				to_string(calcICFromKey(buf, j)) << endl;
		}
	}

	return 0;
}
