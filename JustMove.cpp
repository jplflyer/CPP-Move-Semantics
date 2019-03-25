/*
 * JustMove.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: jpl
 */

#include <stdio.h>
#include <string.h>
#include <memory>
#include <algorithm>

int
main(int argc, char **argv)
{
	char * a = strdup("a");
	char * b = strdup("b");

	int c = 1;
	int d = 2;

	printf("Starting: %s and %s, %d and %d\n", a, b, c, d);

	std::swap(a, b);
	std::swap(c, d);

	printf("After: %s and %s, %d and %d\n", a, b, c, d);

	return 0;
}
