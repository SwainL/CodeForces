#include "vanya_and_lanterns.h"
#include <fstream>

using namespace std;

int main() {
#if defined(_DEBUG)
	streambuf *backup;
	ifstream fin;
	fin.open("input.txt");
	backup = cin.rdbuf();
	cin.rdbuf(fin.rdbuf());
#endif
	
	test();

	system("pause");
	return 0;
}