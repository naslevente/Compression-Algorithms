#include "SlidingWindow.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <queue>

using namespace std;

#define MAX_ITEMS 256
#define BUFFERSIZE 4

struct Encoded {

	int offset = NULL;
	int length = NULL;
};

SlidingWindow::SlidingWindow() {
}

SlidingWindow::~SlidingWindow() {
}

void UpdateQueues(queue<int> &dictionary, queue<int> &lookAheadBuffer, string &output, bool changeOutput) {

	if (changeOutput) {

		output.append(to_string(lookAheadBuffer.front()));
	}

	dictionary.push(lookAheadBuffer.front());

	if (dictionary.size() >= 101) {

		dictionary.pop();
	}

	lookAheadBuffer.pop();
}

void AddCode(queue<int> &dictionary, queue<int> &lookAheadBuffer, string &output, Encoded *longestMatch) {

	if (longestMatch->length != NULL) {

		output.append(to_string(longestMatch->length));
		output.append(to_string(longestMatch->offset));

		cout << longestMatch->length << " " << lookAheadBuffer.size() << endl;

		for (int i = 0; i < longestMatch->length; i++) {

			UpdateQueues(dictionary, lookAheadBuffer, output, false);
		}
	}
	else {

		UpdateQueues(dictionary, lookAheadBuffer, output, true);
	}
}

Encoded *setEncoded(int index, int dictionaryIndex, int length, Encoded *code) {

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

	return code;
}

Encoded* findLongestMatch(queue<int> lookAheadBuffer, queue<int> dictionary, int index, int dictionaryIndex) {

	int character = lookAheadBuffer.front();
	lookAheadBuffer.pop();
	Encoded* code = new Encoded;

	int size = dictionary.size();

	for (int i = 0; i < size; i++) {

		int dicChar = dictionary.front();
		dictionary.pop();

		if (dicChar == character) {

			queue<int> dictionaryCopy = dictionary;
			queue<int> lookAheadCopy = lookAheadBuffer;

			int characterCopy = character;

			index++;
			dictionaryIndex++;

			int length = 1;
			for (int i = 0; i < BUFFERSIZE; i++) {

				if (lookAheadCopy.empty() || dictionaryCopy.empty()) {

					code = setEncoded(index, dictionaryIndex, length, code);
					break;
				}
				else {

					dicChar = dictionaryCopy.front();
					dictionaryCopy.pop();

					character = lookAheadCopy.front();
					lookAheadCopy.pop();

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

							code = setEncoded(index, dictionaryIndex, length, code);

							index -= i;
							dictionaryIndex -= (i - 1);

							break;
						}
					}
				}
			}

			character = characterCopy;
		}
		else {

			index++;
		}
	}

	return code;
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

	//queue<int> output;
	string output;
	queue<int> lookAheadBuffer;
	queue<int> dictionary;

	int index = 0;
	int dictionaryIndex = 0;

	for (int c = fgetc(infile); c != EOF; c = fgetc(infile)) {

		lookAheadBuffer.push(c);
		cout << c << " " << lookAheadBuffer.size() << endl;
		Encoded* longestMatch = new Encoded;

		if (lookAheadBuffer.size() == BUFFERSIZE) {

			if (dictionary.empty() || dictionary.size() == 1|| dictionary.size() == 2) {

				output.append(to_string(lookAheadBuffer.front()));
				dictionary.push(lookAheadBuffer.front());
				lookAheadBuffer.pop();
			}
			else {

				longestMatch = findLongestMatch(lookAheadBuffer, dictionary, index, dictionaryIndex);
			}

			AddCode(dictionary, lookAheadBuffer, output, longestMatch);
		}
	}

	if (lookAheadBuffer.empty()) {

		cout << "Reeached the end of the input file" << endl;
	}
	else {

		while (lookAheadBuffer.size() > 2) {

			Encoded* longestMatch = findLongestMatch(lookAheadBuffer, dictionary, index, dictionaryIndex);
			AddCode(dictionary, lookAheadBuffer, output, longestMatch);
		}
	}
}

