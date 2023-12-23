#include "../include/RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2) {
		error("Usage: ", "./RPN ", "\"[expression]\"");
		return 1;
	}
	return compute(argv[1]);
}