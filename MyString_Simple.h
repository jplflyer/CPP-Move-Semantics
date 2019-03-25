#ifndef _MyString_Simple_H
#define _MyString_Simple_H

class MyString_Simple {
private:
	char *	data;

public:
	MyString_Simple();
	MyString_Simple(const MyString_Simple &orig);
	MyString_Simple(const char *value);
	virtual ~MyString_Simple();

	MyString_Simple & setValue(const char *value);

	const char * getValue() const { return data; }
	MyString_Simple substring(int firstIndex) const;

	MyString_Simple & operator=(const MyString_Simple &other);
};

#endif // _MyString_Simple_H
