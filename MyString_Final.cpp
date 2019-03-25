/*
 * This is a copy of MyString_Simple but with move semantics added at the bottom.
 */
#include <stdio.h>
#include <string.h>
#include <memory>

#include "MyString_Final.h"

/**
 * Default Constructor.
 */
MyString_Final::MyString_Final()
: data(NULL)
{
	puts("Constructor.");
}

/**
 * Copy constructor. Note that normally you should chain to the default constructor,
 * but I don't want to puts out the extra line, as it would confuse things.
 */
MyString_Final::MyString_Final(const MyString_Final &orig)
: data(NULL)
{
	puts("Copy Constructor");
	setValue(orig.data);
}

/**
 * Construct from data.
 */
MyString_Final::MyString_Final(const char *value)
: data(NULL)
{
	puts("Value Constructor.");
	setValue(value);
}

/**
 * Destructor.
 */
MyString_Final::~MyString_Final() {
	puts("Destructor.");
	if (data != NULL) {
		puts("Free data");
		delete[] data;
		data = NULL;
	}
}

/**
 * Set a value.
 */
MyString_Final &
MyString_Final::setValue(const char *value) {
	if (data != NULL) {
		delete[] data;
		data = NULL;
	}
	if (value != NULL) {
		data = new char[strlen(value) + 1];
		strcpy(data, value);
	}
	return *this;
}

/**
 * Substring.
 */
MyString_Final
MyString_Final::substring(int firstIndex) const {
	MyString_Final retVal(data + firstIndex);

	return retVal;
}


/**
 * Copy operator
 */
MyString_Final &
MyString_Final::operator=(const MyString_Final & other)
{
	puts("Copy operator");
    if (this != &other) { // self-assignment check expected
    	setValue(other.getValue());
    }
    return *this;
}

//======================================================================
// Methods for move semantics are here.
//======================================================================

/**
 * Move constructor. Normally I would chain to the default constructor in order to
 * properly initialize to defaults in only one place, but I didn't want it to look like
 * an extra constructor was called (my puts() statement).
 */
MyString_Final::MyString_Final(MyString_Final &&orig) noexcept
: data(NULL)
{
	puts("Move Constructor");
	std::swap(data, orig.data);
}


/**
 * Move operator
 */
MyString_Final &
MyString_Final::operator=(MyString_Final && other) noexcept
{
	puts("Move operator");
    if (this != &other) { // self-assignment check expected
    	std::swap(data, other.data);
    }
    return *this;
}
