#include <iostream>

#include "gl_render.h"
#include "string_handle.h"

#include "action_handle.h"

#include "hash_map.h"
#include "post.h"

int main(int, char**) {

	post_set_ivalid_symbols();

	ActionHandle ah;

	std::string inputTest = "DEFINE testFunc1(a, b, c, d): \"a & b | c\"";

	ah.handle_input(inputTest);

	std::cout << "Hello, world!\n";
}
