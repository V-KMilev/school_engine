#include <iostream>

#include "gl_render.h"

#include "action_handle.h"
#include "post.h"

int main(int, char**) {

	post_set_ivalid_symbols();

	ActionHandle ah;

	std::string inputTest1 = " DEFINE  testFunc1(a, b): \"a & b\"";
	std::string inputTest2 = " DEFINE  testFunc2(a, b, c): \"a & (b | testFunc1(b,c))\"";
	std::string inputTest3 = " DEFINE  testFunc3(a, b, c): \"testFunc2(c,b,a) & (testFunc1(a,c) | a)\"";
	std::string inputTest4 = " DEFINE  testFunc4(a, b): \"b & testFunc3(b,a,d)\"";

	ah.handle_input(inputTest1);
	ah.get_logical_tree("testFunc1").print();
	std::cout << "\n";

	ah.handle_input(inputTest2);
	ah.get_logical_tree("testFunc2").print();
	std::cout << "\n";

	ah.handle_input(inputTest3);
	ah.get_logical_tree("testFunc3").print();
	std::cout << "\n";

	ah.handle_input(inputTest4);
	ah.get_logical_tree("testFunc4").print();

	std::cout << "\nHello, world!\n";
}
