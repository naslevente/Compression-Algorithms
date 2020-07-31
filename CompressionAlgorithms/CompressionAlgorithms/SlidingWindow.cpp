#include "SlidingWindow.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <queue>

using namespace std;

#define MAX_ITEMS 256
#define BUFFERSIZE 6

typedef struct Encoded {

	int offset;
	int length;
};

SlidingWindow::SlidingWindow() {
}

SlidingWindow::~SlidingWindow() {
}

int findLongestMatch(queue<int> lookAheadBuffer, queue<int> dictionary, int index, int dictionaryIndex) {

	int character = lookAheadBuffer.pop;
	Encoded *code;

	for (int i = 0; i < dictionary.size(); i++) {

		int dicChar = dictionary.pop;

		if (dicChar == character) {

			index++;
			dictionaryIndex++;

			int length = 1;
			for (int i = 0; i < BUFFERSIZE - 1; i++) {

				try {

					int dicChar = dictionary.pop;
					int character = lookAheadBuffer.pop;
				}
				catch (int error) {

					break;
				}

				if (dicChar == character) {

					length++;
					index++;
					dictionaryIndex++;
				}
				else {

					if (length == 1 || length == 2) {

						index -= i;
						dictionaryIndex -= (i - 1);
						break;
					}
					else {

						if (code == NULL) {

							code->length = length;
							code->offset = dictionaryIndex - index;
						}
						else {

							if (code->length < length) {

								code->length = length;
								code->offset = dictionaryIndex - index;
							}
						}

						index -= i;
						dictionaryIndex -= (i - 1);
					}
				}
			}
		}
	}
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

	queue<int> output;
	queue<int> lookAheadBuffer;
	queue<int> dictionary;

	int index = 0;
	int dictionaryIndex = 0;

	for (int c = fgetc(infile); c != EOF; c = fgetc(infile)) {

		lookAheadBuffer.push(c);

		if (lookAheadBuffer.size() == 4) {

			if (dictionary.empty || dictionary.size() == 1|| dictionary.size() == 2) {

				output.push(c);
			}
			else {

				int something = findLongestMatch(lookAheadBuffer, dictionary, index, dictionaryIndex);
			}
		}
	}
}

