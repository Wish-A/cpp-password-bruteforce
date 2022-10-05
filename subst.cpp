#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

// argc == numbers of arguments being passed into the program from cmd line
// argv == value array of arguments
int main(int argc, char** argv)
{
	// The characters that need to be modified are "stored" in it
	vector<string> from;

	// Stores the characters by which it is moved
	vector<string> converted;

	string line;
	ifstream file; // Input file stream ofstream and ifstream which means it can create files, write information to files, and read information from files. 

	// If the passed arguments are equal or more than 2. This opens the txt files in the array
	if (argc >= 2) {
		file.open(argv[1]);
    } else { // argc >= 2
        cerr << argv[0] << ": Geen arg, 1 moet gegeven worden" << endl;
        return EXIT_FAILURE;
	}

	// If something other than the file is given: Example: an int
	if (!file.good()) {
		cerr << argv[0] << ": File '" << argv[1] << "' is not a valid file." << endl;
		return EXIT_FAILURE;
	}

	// Length of line should be 2!!! otherwise stderror (as indicated in pdf).
	while (getline(file, line)) {
		if (line.length() != 2) { // Has 2 char
			cerr << "Invalid file line it is not 2: " << line << endl;
			continue;
		}
		// http://www.cplusplus.com/reference/string/string/substr/
		// We need the first letter of the string by using pos 0 and length 1, the first letter is taken from the string
		from.push_back(line.substr(0, 1));

		// The second letter can be found on pos 1 length 1 (from letter 1, 1 more)
		converted.push_back(line.substr(1, 1));
	}

	// Stop if there is a difference in size
    if (from.size() != converted.size()) {
    	cerr << "There is a difference in size. Stop" << endl;
    	return EXIT_FAILURE;
    }

	while (getline(cin, line)) {
	    // Print the current input line back to stdout.
		cout << line << endl;
		
		// Make a copy of the current input line for comparison after replacing characters.
		string hay = line;

        // Iterate over the translatable characters, find them and replace them.
		for (int i = 0; i < from.size(); i++) {
			// Save the currently translating character as string returns a reference to the element at position i in the vector.
			string needle = from.at(i);
			string replace_with = converted.at(i);

			// Start searching for the needle at the first position of the current word
			size_t pos = line.find(needle, 0);

			// Keep searching for other occurances of the needle in the word
			while (pos != string::npos) {
				line.replace(pos, needle.length(), replace_with);
				pos = line.find(needle, pos);
			}
		}

        // Only print new string to output if it's different from the hay string.
		if (line.compare(hay) != 0)
			cout << line << endl;
	}

	return EXIT_SUCCESS;
}
