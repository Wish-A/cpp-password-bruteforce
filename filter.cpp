#include <iostream>
#include <string>

#define FILTER_MINIMUM_WORD_LENGTH 16 // Constant

using namespace std;

int main() {
	string buffer;
	while (getline(cin, buffer)) {
		if (buffer.length() >= FILTER_MINIMUM_WORD_LENGTH) {
			cout << buffer << endl;
		} else {
		    // The password is smaller than the constant of 16, so it is not displayed.
		}
	}

	return 0;
}
