#ifndef STRINGPARSER_HPP
#define STRINGPARSER_HPP
/**
 * @name StringParser 
 * @author Ciyang
 * @date 2019-11-06
 * @version 1.0.0
 * @copyright Copyright © 2019 Ciyang. All rights reserved. 
 */

class StringParser
{
public:
	StringParser();
	StringParser(const char *);
	StringParser(const StringParser &);
	~StringParser();
	int setString(const char *);
	char readChar();
	long long readLL();
	unsigned long long readULL();
	double readDouble();
	char *readStringUntilLineBreak();
	char *readStringUntil(const char *);
	char *readStringOnly(const char *);
	const char *getConstString() const;
	const char *getConstPendingString() const;
	StringParser getString() const;
	StringParser getPendingString() const;
	bool isEnd() const;

private:
	char *asciiStr;
	unsigned int parsePtr;
	unsigned int stringSize;
};

#endif
