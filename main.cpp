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
	std::string inputTest4 = " DEFINE  testFunc4(a, b, c, d): \"b | testFunc3(b,a,d)\"";

	std::string inputTest11 = " SOLVE  testFunc1(1, 1)";
	std::string inputTest21 = " SOLVE  testFunc2(1, 1, 0)";
	std::string inputTest31 = " SOLVE  testFunc3(1, 0, 1)";
	std::string inputTest41 = " SOLVE  testFunc4(0, 1, 0, 1)";

	ah.handle_input(inputTest1);
	ah.get_logical_tree("testFunc1").print();

	ah.handle_input(inputTest11);
	bool a = ah.get_solve("testFunc1");

	std::cerr << a << "\n";

	ah.handle_input(inputTest2);
	ah.get_logical_tree("testFunc2").print();

	ah.handle_input(inputTest21);
	a = ah.get_solve("testFunc2");

	std::cerr << a << "\n";

	ah.handle_input(inputTest3);
	ah.get_logical_tree("testFunc3").print();

	ah.handle_input(inputTest31);
	a = ah.get_solve("testFunc3");

	std::cerr << a << "\n";

	ah.handle_input(inputTest4);
	ah.get_logical_tree("testFunc4").print();

	ah.handle_input(inputTest41);
	a = ah.get_solve("testFunc4");

	std::cerr << a << "\n";

	std::cerr << "\nHello, world!\n";
}
