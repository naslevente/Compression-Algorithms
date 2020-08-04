#include "HuffmanCompression.h"
#include "SlidingWindow.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

	if (argc != 3) {

		cout << "Wrong number of arguments" << endl;
		return(EXIT_FAILURE);
	}

	cout << argv[1] << endl;

	FILE* infile = fopen(argv[1], "r + b");
	FILE* outfile = fopen(argv[2], "w + b");

	//int val = HuffmanCompression::HuffEncode(infile, outfile);
	int val = SlidingWindow::SlidingEncode(infile, outfile);

	if (val == 1) {

		cout << "Error compressing the data" << endl;
		return(EXIT_FAILURE);
	}

	cout << "Successfully Compressed" << endl;
	return(EXIT_SUCCESS);
}