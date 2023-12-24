#include "../include/PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2) {
		error("Usage: ", "./PmergeMe ", "<int list>");
		return 1;
	}
	return run(argv);
}