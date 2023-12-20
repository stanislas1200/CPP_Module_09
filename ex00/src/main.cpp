#include "../include/BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <map>

# define RED "\x1b[1m\x1b[38;2;255;0;0m"
# define MB "\x1b[1m\x1b[38;2;25;25;599m"
# define GREEN "\x1b[1m\x1b[38;2;0;128;0m"
# define YELLOW "\x1b[1m\x1b[38;2;205;205;0m"
# define DV "\x1b[1m\x1b[38;2;148;0;211m"
# define C "\x1b[0m"

void error(const char *type, const char *msg, const char *bold) {
	std::cerr << RED "Error: " YELLOW << type << C << msg;
	if (bold)
		std::cerr << DV << bold << C;
	std::cerr << C << std::endl;
}

bool check_header(std::string &line) {
	std::string header = "date | value";
	line.erase(line.find_last_not_of(" \n\r\t") + 1);
	if (line != header)
		return false;
	return true;
}

bool check_date(std::string &date) {
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	for (int i = 0; i < 10; i++) {
		if (i == 4 || i == 7)
			continue;
		if (date[i] < '0' || date[i] > '9')
			return false;
	}
	return true;
}

bool check_value(const std::string& value) {
	if (value.empty())
		return false;
	char *p;
	std::strtod(value.c_str(), &p);
	if (*p != 0)
		return false;
	return true;
}

// int get_real_value(const std::string& value, std::map<std::string, int> &map) {
// 	return map[value];
// }

bool valid_value(const std::string& value) {
	if (value[0] == '-')
	{
		error("Value: ", "Not a positive number ", value.c_str());
		return false;
	}
	char *p;
	long long ll = std::strtoll(value.c_str(), &p, 10);
	if (p != value.c_str() && *p == 0 && ll > INT_MAX)
	{
		error("Value: ", "Number too large ", value.c_str());
		return false;
	}
	return true;
}

bool check_line(std::string &line, std::map<std::string, double> &map) {
	if (line.find_first_of(" |") == std::string::npos)
	{
		error("Line: ", "Invalid line ", line.c_str());
		return false;
	}
	std::string date = line.substr(0, line.find_first_of(" |"));
	if (!check_date(date))
	{
		error("Date: ", "Invalid date ", date.c_str());
		return false;
	}
	std::string value = line.substr(line.find_first_of(" |") + 3);
	if (!check_value(value))
	{
		error("Value: ", "Invalid value ", value.c_str());
		return false;
	}
	if (!valid_value(value))
		return false;
	std::map<std::string, double>::iterator it = map.find(date);
	if (it == map.end())
		it = map.lower_bound(date);
	double rl_value = it->second * std::strtod(value.c_str(), NULL);
	std::cout << MB << date << " => " DV << value << MB " = " DV << rl_value << C << std::endl;
	return true;
}

std::map<std::string, double> read_db() {
	std::map<std::string, double> map;
	std::ifstream file("data.csv");
	if (!file.is_open()) {
		error("Open: ", "Could not open file ", "db.csv");
		return map;
	}
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line)) {
		line.erase(line.find_last_not_of(" \n\r\t") + 1);
		std::string date = line.substr(0, line.find_first_of(","));
		double value = std::strtod(line.substr(line.find_first_of(",") + 1).c_str(), NULL);
		map[date] = value;
	}
	file.close();
	return map;
}

int read_file(std::ifstream &file) {
	std::string line;
	int line_num = 0;
	// std::getline(file, line);
	// check_header(line);
	if (!std::getline(file, line) || !check_header(line)) {
		error("Header: ", "Invalid header ", line.c_str());
		return 1;
	}
	std::map<std::string, double> map = read_db();
	while (std::getline(file, line)) {
		line.erase(line.find_last_not_of(" \n\r\t") + 1);
		line_num++;
		// std::cout << MB << line_num << ": " << C << line << std::endl;
		check_line(line, map);
	}
	return 0;
}

int open_file(char *path) {
	std::ifstream file(path);
	if (!file.is_open()) {
		error("Open: ", "Could not open file ", path);
		return 1;
	}
	int code = read_file(file);
	file.close();
	return code;
}

int main(int argc, char *argv[]) {
	if (argc != 2)
	{
		error("Usage: ", argv[0], " <file>");
		return 1;
	}
	return open_file(argv[1]);
}
