#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <fstream>
#include <streambuf>

#define MAX_BUF 1024

using namespace std;

int main(int argc, char** argv)
{	
	int g;
	char thisChar;
	
	//cout << " " << argv[1][0] << " st\n";
	ifstream t((argv[1][0] == '1')?"insertionSort.txt":((argv[1][0] == '2')?"bubbleSort.txt":(argv[1][0] == '3')?"mergeSort.txt":"quickSort.txt"));
	
    string str((istreambuf_iterator<char>(t)),
                 istreambuf_iterator<char>());
    cout << str;
	cin.get();
    return 0;
}
