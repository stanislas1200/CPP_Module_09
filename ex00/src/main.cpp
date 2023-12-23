#include "../include/BitcoinExchange.hpp"

int main(int argc, char *argv[]) {
	if (argc != 2)
	{
		error("Usage: ", argv[0], " <file>");
		return 1;
	}
	return open_file(argv[1]);
}
