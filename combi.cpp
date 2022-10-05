#include <vector>
#include <iostream>

using namespace std;

int main()
{
	vector<string> woorden; //Dynamic array
	vector<string> special_chars = { "", "!", "@", "#", "$", "&", "*" };
	string buffer;

	// All words are read from the standard input and given to the vector (from woorden.txt)
	while (getline(cin, buffer))
	{
		woorden.push_back(buffer);
	}

	/**
	 * Output: woord | specialsign 1 | woord | specialsign 2 | woord
	 * Example : mieke!koek@huis
	 */
	for (int i = 0; i < woorden.size(); i++) {
		for (int j = 0; j < woorden.size(); j++) {
			for (int k = 0; k < woorden.size(); k++) {
				// For the first sign, a specialchar is chosen
				for (int char1 = 0; char1 < special_chars.size(); char1++) {
					// Repetition for the second char
					for (int char2 = 0; char2 < special_chars.size(); char2++) {
						cout << woorden.at(i) << special_chars.at(char1) << woorden.at(j) << special_chars.at(char2) << woorden.at(k) << endl;
					}
				}
			}
		}
	}

	return 0;
}
