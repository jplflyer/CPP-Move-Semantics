/*
 * This is a copy of MyString_Simple but with move semantics added after a big comment.
 */
#ifndef _MyString_Final_H
#define _MyString_Final_H

class MyString_Final {
private:
	char *	data;

public:
	MyString_Final();
	MyString_Final(const MyString_Final &orig);
	MyString_Final(const char *value);
	virtual ~MyString_Final();

	MyString_Final & setValue(const char *value);

	const char * getValue() const { return data != NULL ? data : ""; }
	MyString_Final substring(int firstIndex) const;

	MyString_Final & operator=(const MyString_Final &other);

	//======================================================================
	// These are the move semantics methods.
	//======================================================================

	// Copy constructor.
	MyString_Final(MyString_Final &&orig) noexcept;

	// Move assignment operator
	MyString_Final & operator=(MyString_Final &&other) noexcept;
};

#endif // _MyString_Final_H
