/*
 * Test__Simple.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: jpl
 */

#include <stdio.h>
#include "MyString_Simple.h"

int main(int argc, char **argv) {
	MyString_Simple firstStr("Hello There");
	MyString_Simple secondStr(firstStr);
	MyString_Simple thirdStr;

	thirdStr = firstStr.substring(6);

	printf("firstStr: %s. secondStr: %s thirdStr: %s\n",
			firstStr.getValue(),
			secondStr.getValue(),
			thirdStr.getValue()
			);
	puts("Done");
	return 0;
}


