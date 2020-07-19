#include "HuffmanCompression.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

static int HuffEndoce(FILE* infile, FILE* outfile);

string infileSequence;
int numOfChars;

HuffmanCompression::HuffmanCompression() {
}

HuffmanCompression::~HuffmanCompression() {
}

struct sElement {

	int count;
	char identifier;
	sElement* ChildLeft = NULL;
	sElement* ChildRight = NULL;
	bool isVisited = false;
	string bitSequence;

} Element[MAXSYMBOLS];

int HuffScan(FILE* infile) {

	int c;
	while ((c = fgetc(infile)) != EOF) {

		if (Element[c].count == NULL) {

			numOfChars++;
		}

		Element[c].count += 1;
		infileSequence += c;
	}

	cout << infileSequence << endl;

	if (ferror(infile)) {

		return(1);
	}
	else {

		rewind(infile);
		return(0);
	}
}

string HuffRecord(sElement* node, string bitSequence, int dir) {

	if (node->ChildLeft == NULL) {

		node->bitSequence = bitSequence;
		cout << node->identifier << node->count << endl;
		cout << bitSequence << endl;
		Element[node->identifier] = *node;
		bitSequence = bitSequence.substr(0, bitSequence.length() - 1);
		
		return bitSequence;
	}
	else {

		for (int i = 0; i < 2; i++) {

			if (i == 0) {

				bitSequence += to_string(i);
				bitSequence = HuffRecord(node->ChildLeft, bitSequence, 0);
			}
			else {

				bitSequence += to_string(i);
				bitSequence = HuffRecord(node->ChildRight, bitSequence, 1);

				bitSequence = bitSequence.substr(0, bitSequence.length() - 1);
				return bitSequence;
			}
		}
	}
}

int HuffBuild() {

	int lo1 = 0;
	int lo2 = -1;
	bool isBuilt = false;

	while (!isBuilt) {

		for (int i = 1; i < MAXSYMBOLS; i++) {

			if (!Element[i].isVisited) {

				if ((Element[i].count != NULL && Element[i].count <= Element[lo1].count) || Element[lo1].count == NULL) {

					if ((lo2 == -1 && Element[lo1].count != NULL) || (lo2 != -1 && Element[lo2].count > Element[lo1].count)) {

						lo2 = lo1;
					}

					lo1 = i;
				}
				else if ((lo2 != -1 && Element[i].count != NULL && Element[lo2].count > Element[i].count) || (lo2 == -1 && Element[i].count != NULL)) {

					lo2 = i;
				}
			}
		}

		if (lo2 == -1) {
			
			isBuilt = true;
			break;
		}
		else {

			Element[lo1].identifier = lo1;
			Element[lo2].identifier = lo2;

			Element[lo1 + lo2].count = Element[lo2].count + Element[lo1].count;
			Element[lo1 + lo2].ChildLeft = &Element[lo1];
			Element[lo1 + lo2].ChildRight = &Element[lo2];

			Element[lo1].isVisited = true;
			Element[lo2].isVisited = true;
		}

		lo1 = 0;
		lo2 = -1;
	}

	for (int i = 0; i < 2; i++) {

		if (i == 0) {

			string bitSequence = "0";
			bitSequence = HuffRecord(Element[lo1].ChildLeft, bitSequence, 0);
		}
		else {

			string bitSequence = "1";
			bitSequence = HuffRecord(Element[lo1].ChildRight, bitSequence, 1);
		}
	}

	return(lo1);
}

void HuffCompress(FILE* outfile) {

	string OutputSequence;
	for (int i = 0; i < infileSequence.length(); i++) {

		OutputSequence += Element[infileSequence[i]].bitSequence;
	}

	cout << OutputSequence << endl;

	char OutputByte;
	int count = 0;
	for (int i = 0; i < OutputSequence.length(); i++) {

		if (count > 7) {

			count = 0;
			fwrite(&OutputByte, sizeof(OutputByte), 1, outfile);
			OutputByte = NULL;
		}

		char bit = OutputSequence[i];
		if (count == 0) {

			OutputByte = (bit & 00000001) << 7;
		}
		else {

			char byte = ((bit & 00000001) << 7 - count);
			OutputByte = byte | bit;
		}
	}
}

int HuffmanCompression::HuffEncode(FILE* infile, FILE* outfile) {

	if (infile == NULL) {

		cout << "Error with input file" << endl;
		return(EXIT_FAILURE);
	}

	if (outfile == NULL) {

		cout << "Error with output file" << endl;
		return(EXIT_FAILURE);
	}

	int val;
	if (val = HuffScan(infile)) {

		fclose(infile);
		fclose(outfile);
		return(1);
	}

	val = HuffBuild();

	HuffCompress(outfile);
	fclose(infile);
	fclose(outfile);

	return(2);
}
