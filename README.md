# C++ Move Semantics
This little project is to help me understand the little weirdness that comes from C++ move semantics. It's a tutorial for myself as well as anyone else who wants to learn this stuff.µ

# Eclipse Files
I use Eclipse as my IDE, and I have committed my files.

# What are Move Semantics and Why Do I Care?
Imagine you wrote your own string class. Your class definition might look like this:

    class MyString {
    private:
    	char *	data;

    public:
    	MyString();
    	MyString(const MyString &orig);
    	MyString(const char *value);
    	virtual ~MyString();

    	MyString & setValue(const char *value);

    	const char * getValue() const { return data; }
    	MyString substring(int firstIndex) const;

    	MyString & operator=(const MyString &other);
    };

Imagine your code does this:

    int main(int argc, char **argv) {
    	MyString firstStr("Hello There");
    	MyString secondStr(firstStr);
    	MyString thirdStr;

    	thirdStr = firstStr.substring(6);

    	printf("firstStr: %s. secondStr: %s thirdStr: %s\n",
    			firstStr.getValue(),
    			secondStr.getValue(),
    			thirdStr.getValue()
    			);
    	puts("Done");
    	return 0;
    }

Look at my code MyString1.h and .cpp for the example code. What is going to happen is:

1. Construct firstString (allocate space)
2. Construct secondString (allocate space)
3. Construct thirdString (NULL)
4. The substring allocates space and returns it as a temporary object.
5. It calls the copy operator, passing in the temporary object.
6. The copy operator allocates a second copy of the string from substring
7. And then when we're done, we destroy the temporary object, freeing the space.

This results in extra allocation and release of storage. Move operators help you get rid of that when dealing with temporary objects. It improves new/delete efficiency.

The output with my puts statements is:

    Value Constructor.
    Copy Constructor
    Constructor.
    Value Constructor.
    Destructor.
    Free data
    firstStr: Hello There. secondStr: Hello There thirdStr: There
    Done
    Destructor.
    Free data
    Destructor.
    Free data
    Destructor.
    Free data

# Why Does This Matter?
Performance. For my simple tests, you wouldn't bother. But imagine that you're allocating a huge chunk of data. It's going to be expensive to alloc/copy/free all the time, so being able to do a move can save a significant amount. For instance, if you have a huge array with pointers to objects, each of which allocates more data, being able to use move semantics means you don't allocate a thing. You only MOVE the pointer to the array. You don't have to create a bunch of new objects. You don't have to copy their contents. And then because it's a temporary, destroy it.

# The Results
I have two programs, Test_Simple2 and Test_Final. Test_Simple2 uses MyString_Simple, which does not have move constructors and operators. Test_Final uses MyString_Final, which does have these. Otherwise, they are identical.

The output from Test_Simple2 (no move semantics);
    Value Constructor.
    Copy Constructor
    firstStr: Hello There. secondStr: Hello There
    Now create thirdStr, hitting the default constructor.
    Constructor.

    And then use the move operator.
    firstStr: Hello There. secondStr: Hello There. thirdStr: Hello There

    Now try swapping.
    Copy Constructor
    Destructor.
    Free data
    firstStr: Hello There. secondStr: Hello There. thirdStr: Hello There

    Let's call substring
    Value Constructor.
    Destructor.
    Free data
    firstStr: Hello There. secondStr: There. thirdStr: Hello There

    Done.
    Destructor.
    Free data
    Destructor.
    Free data
    Destructor.
    Free data

The output from Test_Final (with move semantics):
    Value Constructor.
    Move Constructor
    firstStr: . secondStr: Hello There
    Now create thirdStr, hitting the default constructor.
    Constructor.

    And then use the move operator.
    Move operator
    firstStr: . secondStr: . thirdStr: Hello There

    Now try swapping.
    Move Constructor
    Move operator
    Move operator
    Destructor.
    firstStr: Hello There. secondStr: . thirdStr:

    Let's call substring
    Value Constructor.
    Move operator
    Destructor.
    firstStr: Hello There. secondStr: There. thirdStr:

    Done.
    Destructor.
    Destructor.
    Free data
    Destructor.
    Free data

Note that the main() methods are identical, except for which class is used. Note the destructor calls in which "Free Data" is dumped. In the top one, we free data 5 times. In the second, because we moved data, we only free data 2 times. One is the original data, and one is the output from the substring() call, which allocates new data.

# The code
There is a Makefile, two versions of MyString, and four sample programs:

MyString_Simple: a simple string class with no move semantics
MyString_Final: the same class with move semantics added

JustMove: an example of using std::swap.

Test_Simple: A demonstration of using MyString_Simple

Test_Simple2
Test_Final: these two are nearly identical except one uses MyString_Simple and one uses MyString_Final

# The std:: Methods
You'll see my code includes two standard files

    #include <memory>
    #include <algorithm>

These respectively define std::move() and std::swap().

## std::move
Move does not do what it seems. It is just a type cast. If you do something like this:

    MyString_Final a("a");
    MyString_Final b(a);

The second line calls the copy constructor. If you do this:

    MyString_Final b(std::move(a));

It marks a as a RHS expression (right-hand-side), and then it can try using the move constructor instead. std::move() is ONLY a typecast.

I don't think you would do what I did here, except as a demo. It's sort of silly. But it does help you to test.

## std::swap
This is a simple template function that basically evaluates to this:

    void swap(Type &a, Type &b) {
      Type newType(a);
      a = b;
      b = newType;
    }

In other words, it's just a swap method. It will call appropriate constructors. In my two examples, this is what happens without move semantics:

    Now try swapping.
    Copy Constructor
    Destructor.
    Free data
    firstStr: Hello There. secondStr: Hello There. thirdStr: Hello There

And this is with move semantics:

    Now try swapping.
    Move Constructor
    Move operator
    Move operator
    Destructor.
    firstStr: Hello There. secondStr: . thirdStr:

I think some of the difference in output is because I don't have all the print statements. But you'll see that the first one calls the copy constructor, which duplicates all the data, and when it's done, it has to destroy the duplicated data. The second one does move semantics, so you still end up with a temporary object, but from there, it's entirely a move operation.
