#include <string>
#include <fstream>
#include <iostream>

#define UPPER_OFFSET 65 // Man ascii

using namespace std;


// Decrypt a ciphertext from key
string deVigenere(string& cipher, string& key)
{
	string pText;
	for(auto i{0}; i < key.size(); i++) {
		if(cipher.size() <= i) { // Don't go out of bounds
			break;
		}

		// Get base from upper offset, subtract cipher from key value, and push onto string
		auto c = cipher.at(i);
		auto k = key.at(i);
		c -= UPPER_OFFSET;
		k -= UPPER_OFFSET;
		auto p = c - k;
		pText.push_back(((p + 26) % 26) + UPPER_OFFSET);
	}

	return pText;
}

int main()
{
	string key, cipher;
	cout << "Enter key: ";
	getline(cin, key);

	ifstream f1("found1"), f2("found2"), ck("krypton5");
	ofstream p1("plain1"), p2("plain2"), pk("pass");

	// Check to ensure all files are open
	if(not f1.is_open() or not f2.is_open()) {
		cerr << "Unable to open ciphertexts!" << endl;
	}
	if(not p1.is_open() or not p2.is_open()) {
		cerr << "Unable to open plaintexts!" << endl;
	}
	if(not ck.is_open() or not pk.is_open()) {
		cerr << "Unable to open password!" << endl;
	}

	// Decrypt and write to file
	while(getline(f1, cipher)) {
		p1 << deVigenere(cipher, key);
	}
	while(getline(f2, cipher)) {
		p2 << deVigenere(cipher, key);
	}
	while(getline(ck, cipher)) {
		pk << deVigenere(cipher, key);
	}

	// Fin
	return 0;
}
