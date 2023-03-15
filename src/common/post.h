#pragma once

#include <string>

extern std::string invalid_symbols;

static void post_set_ivalid_symbols() {
	for(char invalid = '!'; invalid <= '/'; invalid++) {
		invalid_symbols += invalid;
	}
	for(char invalid = ':'; invalid <= '@'; invalid++) {
		invalid_symbols += invalid;
	}
	for(char invalid = '['; invalid <= '`'; invalid++) {
		invalid_symbols += invalid;
	}
	for(char invalid = '{'; invalid <= '~'; invalid++) {
		invalid_symbols += invalid;
	}
}