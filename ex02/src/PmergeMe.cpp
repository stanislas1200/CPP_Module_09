#include "../include/PmergeMe.hpp"

void error(const char *type, const char *msg, const char *bold)
{
	std::cerr << RED "Error: " YELLOW << type << C << msg << DV << bold << C << std::endl;
}

template <typename T>
void merge(T left, T left_end, T right, T right_end, T v)
{
	while (left != left_end && right != right_end)
	{
		if (*left < *right)
			*v++ = *left++;
		else
			*v++ = *right++;
	}
	while (left != left_end)
		*v++ = *left++;
	while (right != right_end)
		*v++ = *right++;
}

template <typename T>
void insertion_sort(T &v)
{
	for (long unsigned int i = 1; i < v.size(); i++)
	{
		long unsigned int j = i;
		while (j > 0 && v[j - 1] > v[j])
		{
			std::swap(v[j], v[j - 1]);
			j--;
		}
	}
}

template <typename T>
void merge_insertion_sort(T &v)
{
	if (v.size() < 4)
	{
		insertion_sort(v);
		return;
	}
	T left(v.begin(), v.begin() + v.size() / 2);
	T right(v.begin() + v.size() / 2, v.end());
	merge_insertion_sort(left);
	merge_insertion_sort(right);
	merge(left.begin(), left.end(), right.begin(), right.end(), v.begin());
}

template <typename T>
void sort(T &l)
{
	std::clock_t start = std::clock();
	merge_insertion_sort(l);
	double time = (std::clock() - start) / (double)CLOCKS_PER_SEC * 1000;
	std::cout << DV "------" << typeid(l).name() << "------" C << std::endl;
	std::cout << MB "After:  " C;
	for (long unsigned int i = 0; i < l.size(); i++)
		std::cout << GREEN << l[i] << C " ";
	std::cout << std::endl;
	std::cout << MB "Time:   " C << time << "ms" << std::endl;
}


int run(char **av) {
	std::string			buff;
	std::vector<int>	v;
	std::deque<int>		d;
	for (int i = 1; av[i]; i++) {
		if (!av[i][0])
			return error("Invalid input: ", "empty string", ""), 1;
		for (int j = 0; av[i][j]; j++)
			if (!isdigit(av[i][j]))
				return error("Invalid input: ", "char: ", std::string(1, av[i][j]).c_str()), 1;
		buff += av[i] + std::string(" ");
		int n = std::atoi(av[i]);
		v.push_back(n);
		d.push_back(n);
	}
	std::cout << MB "Before: " C << buff << std::endl;
	sort(v);
	sort(d);
	return 0;
}