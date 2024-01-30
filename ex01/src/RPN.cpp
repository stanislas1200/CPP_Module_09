#include "../include/RPN.hpp"

void error(const char *type, const char *msg, const char *bold) {
	std::cerr << RED "Error: " YELLOW << type << C << msg;
	if (bold)
		std::cerr << DV << bold << C;
	std::cerr << C << std::endl;
}

int compute(const char *str) {
	std::cout << MB "Computing: " C << str << std::endl;
	std::stack<double> stack;
	for (int i = 0; str[i]; i++) {
		if (str[i] == ' ')
			continue;
		if (isdigit(str[i])) {
			stack.push(std::atoi(&str[i]));
			while (isdigit(str[i]))
				i++;
			i--;
		} else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			if (stack.size() < 2) {
				error("Invalid input: ", "not enough values in stack to perform next ", str + i);
				return 1;
			}
			double a = stack.top();
			stack.pop();
			double b = stack.top();
			stack.pop();
			if (str[i] == '+')
				stack.push(b + a);
			else if (str[i] == '-')
				stack.push(b - a);
			else if (str[i] == '*')
				stack.push(b * a);
			else if (str[i] == '/') {
				if (a == 0) {
					error("Division by zero", "", "");
					return 1;
				}
				stack.push(b / a);
			}
		} else {
			error("Invalid input: ", "char: ", std::string(1, str[i]).c_str());
			return 1;
		}
	}
	if (stack.size() > 1) {
		error("Invalid input: ", "not enough operator in stack to perform next ", str);
		return 1;
	}
	if (stack.size() < 1) {
		error("Invalid input: ", "empty ", str);
		return 1;
	}
	std::cout << MB "Result: " GREEN << stack.top() << C << std::endl;
	return 0;
}
