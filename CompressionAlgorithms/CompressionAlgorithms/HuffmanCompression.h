#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>

class HuffmanCompression
{

#define MAXSYMBOLS 512

#define LEFT 0
#define RIGHT 1

private:

	HuffmanCompression();
	~HuffmanCompression();

public:

	static int HuffEncode(FILE* infile, FILE* outfile);
};

