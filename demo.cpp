#include <iostream>
#include <stdio.h>
#include "StringParser.hpp"

int main() {
	StringParser a = StringParser("L  1231.1234654 \r\nASDFG\r\n\n\n\n\nRA");
	printf("%s\n", a.readStringUntil("1"));
	StringParser b= a.getPendingString();
	printf("%u\n", b.readULL());
	printf("%u\n", b.readULL());
	printf("%s\n", b.readStringUntilLineBreak());
	printf("%s\n", b.readStringUntilLineBreak());
	printf("%lf\n", a.getPendingString().readDouble());
	
}
