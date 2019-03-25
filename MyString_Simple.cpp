/*
 * This is a simple example without move semantics.
 */
#include <stdio.h>
#include <string.h>

#include "MyString_Simple.h"

/**
 * Default Constructor.
 */
MyString_Simple::MyString_Simple()
: data(NULL)
{
	puts("Constructor.");
}

/**
 * Copy constructor.
 */
MyString_Simple::MyString_Simple(const MyString_Simple &orig)
: data(NULL)
{
	puts("Copy Constructor");
	setValue(orig.data);
}

/**
 * Construct from data.
 */
MyString_Simple::MyString_Simple(const char *value)
: data(NULL)
{
	puts("Value Constructor.");
	setValue(value);
}

/**
 * Destructor.
 */
MyString_Simple::~MyString_Simple() {
	puts("Destructor.");
	if (data != NULL) {
		puts("Free data");
		delete[] data;
		data = NULL;
	}
}

/**
 * Copy operator
 */
MyString_Simple &
MyString_Simple::operator=(const MyString_Simple & other)
{
    if (this != &other) { // self-assignment check expected
    	setValue(other.getValue());
    }
    return *this;
}

/**
 * Set a value.
 */
MyString_Simple &
MyString_Simple::setValue(const char *value) {
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
 * The substring method.
 */
MyString_Simple
MyString_Simple::substring(int firstIndex) const {
	MyString_Simple retVal(data + firstIndex);

	return retVal;
}
