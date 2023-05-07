#include <iostream>

#include "gl_render.h"

#include "action_handle.h"
#include "post.h"

int main(int, char**) {

	post_set_ivalid_symbols();

	ActionHandle ah;

	std::string inputTest1 = " DEFINE  testFunc1(a, b, c, d): \"a & (!b | !c)\"";
	std::string inputTest2 = " DEFINE  testFunc2(a, b, c, d): \"a & (!b | !testFunc1(b,a,c,d))\"";
	std::string inputTest3 = " DEFINE  testFunc3(a, b, c, d): \"testFunc2(b,a,c,d) & (!testFunc1(b,a,c,d) | !c)\"";
	std::string inputTest4 = " DEFINE  testFunc4(a, b, c, d): \"c & testFunc3(b,a,c,d)\"";

	ah.handle_input(inputTest1);

	std::cout << "\n";

	ah.handle_input(inputTest2);

	std::cout << "\n";

	ah.handle_input(inputTest3);

	std::cout << "\n";

	ah.handle_input(inputTest4);

	std::cout << "\nHello, world!\n";
}
