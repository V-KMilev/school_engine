#include <iostream>

#include "gl_render.h"
#include "string_handle.h"

#include "action_handle.h"

#include "hash_map.h"
#include "post.h"

int main(int, char**) {

	post_set_ivalid_symbols();

	ActionHandle ah;

	std::string inputTest1 = " DEFINE  testFunc1(a, b, c, d): \"a & (!b | !c)\"";
	// std::string inputTest2 = " DEFINE  testFunc2(a, b, c, d): \"a & testFunc1(b,a,c,d)\"";

	ah.handle_input(inputTest1);
	// ah.handle_input(inputTest2);

	std::cout << "\nHello, world!\n";
}
