#include <stdio.h>
#include <memory>
#include <algorithm>

#include "MyString_Final.h"

int main(int argc, char **argv) {
	MyString_Final firstStr("Hello There");
	MyString_Final secondStr(std::move(firstStr));

	// At this point, because we used the move constructor, firstStr
	// will be empty and thirdStr has the original firstStr data.
	printf("firstStr: %s. secondStr: %s\n",
			firstStr.getValue(),
			secondStr.getValue()
			);

	puts("Now create thirdStr, hitting the default constructor.");
	MyString_Final thirdStr;

	puts("\nAnd then use the move operator.");
	thirdStr = std::move(secondStr);

	printf("firstStr: %s. secondStr: %s. thirdStr: %s\n",
			firstStr.getValue(),
			secondStr.getValue(),
			thirdStr.getValue()
			);

	puts("\nNow try swapping.");

	std::swap(firstStr, thirdStr);
	printf("firstStr: %s. secondStr: %s. thirdStr: %s\n",
			firstStr.getValue(),
			secondStr.getValue(),
			thirdStr.getValue()
			);

	puts("\nLet's call substring");
	secondStr = firstStr.substring(6);
	printf("firstStr: %s. secondStr: %s. thirdStr: %s\n",
			firstStr.getValue(),
			secondStr.getValue(),
			thirdStr.getValue()
			);

	puts("\nDone.");
	return 0;
}
