#include <iostream>

#include "gl_render.h"
#include "string_handle.h"

#include "define_handle.h"

int main(int, char**) {

	StringHandle sh;

	DefineHandle dh("func1(a,b,c)", "DEFINE");

	dh.show_parameters();

	std::cout << "Hello, world!\n";
}
