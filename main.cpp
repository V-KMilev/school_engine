#include <iostream>

#include "gl_render.h"
#include "string_handle.h"

#include "define_handle.h"

#include "hash_map.h"

int main(int, char**) {

	DefineHandle dh("func1(a,b,c)", "DEFINE");

	std::cout << "Hello, world!\n";
}
