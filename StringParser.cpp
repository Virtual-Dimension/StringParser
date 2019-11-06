#include "StringParser.hpp"

StringParser::StringParser()
{
	asciiStr = 0;
	stringSize = 0;
	parsePtr = 0;
}

StringParser::StringParser(const char *inStr)
{
	asciiStr = 0;
	stringSize = 0;
	this->setString(inStr);
}

StringParser::StringParser(const StringParser &inStringParser)
{
	*this = inStringParser.getPendingString();
}

StringParser::~StringParser()
{
	if (stringSize)
	{
		delete asciiStr;
	}
}

int StringParser::setString(const char *inStr)
{
	if (stringSize)
	{
		delete asciiStr;
		asciiStr = 0;
		stringSize = 0;
	}
	parsePtr = 0;
	if (inStr)
	{
		while (inStr[stringSize])
		{
			++stringSize;
		}
	}
	asciiStr = new char[stringSize + 1]();
	for (int i = 0; i < stringSize; i++)
	{
		asciiStr[i] = inStr[i];
	}
	asciiStr[stringSize] = 0;
	return stringSize;
}

char StringParser::readChar()
{
	char ch = 0;
	if (parsePtr < stringSize)
	{
		ch = asciiStr[parsePtr++];
	}
	return ch;
}

long long StringParser::readLL()
{
	long long res = 0;
	long long sym = 1;
	while (parsePtr < stringSize)
	{
		if (asciiStr[parsePtr] >= '0' && asciiStr[parsePtr] <= '9')
		{
			break;
		}
		if (asciiStr[parsePtr] == '-')
		{
			sym = -sym;
		}
		++parsePtr;
	}
	while (parsePtr < stringSize)
	{
		if (asciiStr[parsePtr] < '0' || asciiStr[parsePtr] > '9')
		{
			break;
		}
		res = res * 10 + asciiStr[parsePtr] - '0';
		++parsePtr;
	}
	return res * sym;
}

unsigned long long StringParser::readULL()
{
	unsigned long long res = 0;
	while (parsePtr < stringSize)
	{
		if (asciiStr[parsePtr] >= '0' && asciiStr[parsePtr] <= '9')
		{
			break;
		}
		++parsePtr;
	}
	while (parsePtr < stringSize)
	{
		if (asciiStr[parsePtr] < '0' || asciiStr[parsePtr] > '9')
		{
			break;
		}
		res = res * 10 + asciiStr[parsePtr] - '0';
		++parsePtr;
	}
	return res;
}

double StringParser::readDouble()
{
	double res = 0;
	double sym = 1;
	while (parsePtr < stringSize)
	{
		if (asciiStr[parsePtr] >= '0' && asciiStr[parsePtr] <= '9')
		{
			break;
		}
		if (asciiStr[parsePtr] == '-')
		{
			sym = -sym;
		}
		++parsePtr;
	}
	while (parsePtr < stringSize)
	{
		if (asciiStr[parsePtr] < '0' || asciiStr[parsePtr] > '9')
		{
			break;
		}
		res = res * 10 + asciiStr[parsePtr] - '0';
		++parsePtr;
	}
	if (parsePtr < stringSize && asciiStr[parsePtr] == '.')
	{
		double dec = 0;
		double decw = 1;
		++parsePtr;
		while (parsePtr < stringSize)
		{
			if (asciiStr[parsePtr] < '0' || asciiStr[parsePtr] > '9')
			{
				break;
			}
			dec = dec * 10 + asciiStr[parsePtr] - '0', decw = decw * 10;
			++parsePtr;
		}
		res = res + dec / decw;
	}
	return res * sym;
}

char *StringParser::readStringUntilLineBreak()
{
	return this->readStringUntil("\n\r");
}

char *StringParser::readStringUntil(const char *ch)
{
	unsigned int lastw = parsePtr;
	while (parsePtr < stringSize)
	{
		unsigned int chlen = 0;
		while (ch[chlen] && asciiStr[parsePtr] != ch[chlen])
		{
			++chlen;
		}
		if (ch[chlen])
		{
			break;
		}
		++parsePtr;
	}
	char *res = new char[parsePtr - lastw + 1]();
	for (int i = lastw, j = 0; i < parsePtr; i++, j++)
	{
		res[j] = asciiStr[i];
	}
	res[parsePtr - lastw] = 0;
	while (parsePtr < stringSize)
	{
		unsigned int chlen = 0;
		while (ch[chlen])
		{
			if (asciiStr[parsePtr] == ch[chlen])
			{
				break;
			}
			++chlen;
		}
		if (!ch[chlen])
		{
			break;
		}
		++parsePtr;
	}
	return res;
}

char *StringParser::readStringOnly(const char *ch)
{
	unsigned int lastw = parsePtr;
	while (parsePtr < stringSize)
	{
		unsigned int chlen = 0;
		while (ch[chlen])
		{
			if (asciiStr[parsePtr] == ch[chlen])
			{
				break;
			}
			++chlen;
		}
		if (!ch[chlen])
		{
			break;
		}
		++parsePtr;
	}
	char *res = new char[parsePtr - lastw + 1]();
	for (int i = lastw, j = 0; i < parsePtr; i++, j++)
	{
		res[j] = asciiStr[i];
	}
	res[parsePtr - lastw] = 0;
	return res;
}
const char *StringParser::getConstString() const
{
	return asciiStr;
}

const char *StringParser::getConstPendingString() const
{
	return asciiStr + parsePtr;
}

StringParser StringParser::getString() const
{
	return StringParser(asciiStr);
}

StringParser StringParser::getPendingString() const
{
	return StringParser(asciiStr + parsePtr);
}

bool StringParser::isEnd() const
{
	return parsePtr == stringSize;
}
