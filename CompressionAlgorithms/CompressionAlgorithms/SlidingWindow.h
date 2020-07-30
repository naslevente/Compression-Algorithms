#pragma once
#include <stdio.h>
#include <stdlib.h>

class SlidingWindow
{

private:

	SlidingWindow();
	~SlidingWindow();

public:

	static int SlidingEncode(FILE* infile, FILE* outfile);
};

