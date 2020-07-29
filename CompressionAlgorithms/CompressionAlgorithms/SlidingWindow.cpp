#include "SlidingWindow.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <queue>

using namespace std;

#define MAX_ITEMS 256

typedef struct Encoded {

	int offset;
	int length;
};

SlidingWindow::SlidingWindow() {
}

SlidingWindow::~SlidingWindow() {
}

int findLongestMatch(queue<int> lookAheadBuffer) {


}

int SlidingWindow::SlidingEncode(FILE* infile, FILE* outfile) {

	if (infile == NULL) {

		cout << "Error with the input file" << endl;
		return(EXIT_FAILURE);
	}

	if (outfile == NULL) {

		cout << "Error with the output file" << endl;
		return(EXIT_FAILURE);
	}

	queue <int> lookAheadBuffer;

	for (int c = fgetc(infile); c != EOF; c = fgetc(infile)) {

		lookAheadBuffer.push(c);

		if (lookAheadBuffer.size() == 4) {


		}
	}
}
