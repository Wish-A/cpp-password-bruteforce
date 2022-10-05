#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	vector<string> subs = { "a4", "b6", "e3", "t7", "o0", "i1" };
	int filenumber = 1;

	// Possible subs combinations will be created
	for (int i = 0; i < subs.size(); i++) {
		for (int j = i + 1; j < subs.size(); j++) {
			for (int k = j + 1; k < subs.size(); k++) {
				ofstream file;
				string filename(string("subst") + to_string(filenumber++) + ".txt");
				file.open(filename);
				file << subs[i] << endl << subs[j] << endl << subs[k] << endl;
				file.close();
			}
		}
	}

	return 0;
}
