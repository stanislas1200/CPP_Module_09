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
void merge_insertion_sort(T &v)
{
	if (v.size() < 2)
		return;
	T left(v.begin(), v.begin() + v.size() / 2);
	T right(v.begin() + v.size() / 2, v.end());
	merge_insertion_sort(left);
	merge_insertion_sort(right);
	merge(left.begin(), left.end(), right.begin(), right.end(), v.begin());
}

// void merge_insertion_sort_v(std::vector<int> &v)
// {
// 	if (v.size() < 2)
// 		return;
// 	std::vector<int> left(v.begin(), v.begin() + v.size() / 2);
// 	std::vector<int> right(v.begin() + v.size() / 2, v.end());
// 	merge_insertion_sort(left);
// 	merge_insertion_sort(right);
// 	merge(left.begin(), left.end(), right.begin(), right.end(), v.begin());
// }

// void merge_insertion_sort_d(std::deque<int> &d)
// {
// 	if (d.size() < 2)
// 		return;
// 	std::deque<int> left(d.begin(), d.begin() + d.size() / 2);
// 	std::deque<int> right(d.begin() + d.size() / 2, d.end());
// 	merge_insertion_sort_d(left);
// 	merge_insertion_sort_d(right);
// 	merge(left.begin(), left.end(), right.begin(), right.end(), d.begin());
// }

// void vector_sort(std::vector<int> &v)
// {
// 	std::clock_t start = std::clock();
// 	// std::vector<int> v;
// 	// for (int i = 0; buff[i]; i++)
// 	// {
// 	// 	if (buff[i] == ' ')
// 	// 		continue;
// 	// 	v.push_back(std::atoi(&buff[i]));
// 	// 	while (isdigit(buff[i]))
// 	// 		i++;
// 	// }
// 	merge_insertion_sort(v);
// 	double time = (std::clock() - start) / (double)CLOCKS_PER_SEC * 1000;
// 	std::cout << DV "------VECTOR------" C << std::endl;
// 	std::cout << MB "After: " C;
// 	for (long unsigned int i = 0; i < v.size(); i++)
// 		std::cout << GREEN << v[i] << C " ";
// 	std::cout << std::endl;
// 	std::cout << MB "Time: " C << time << "ms" << std::endl;
// }

// void deque_sort(std::deque<int> &d)
// {
// 	std::clock_t start = std::clock();
// 	// std::deque<int> d;
// 	// for (int i = 0; buff[i]; i++)
// 	// {
// 	// 	if (buff[i] == ' ')
// 	// 		continue;
// 	// 	d.push_back(std::atoi(&buff[i]));
// 	// 	while (isdigit(buff[i]))
// 	// 		i++;
// 	// }
// 	merge_insertion_sort(d);
// 	double time = (std::clock() - start) / (double)CLOCKS_PER_SEC * 1000;
// 	std::cout << DV "------DEQUE------" C << std::endl;
// 	std::cout << MB "After: " C;
// 	for (long unsigned int i = 0; i < d.size(); i++)
// 		std::cout << GREEN << d[i] << C " ";
// 	std::cout << std::endl;
// 	std::cout << MB "Time: " C << time << "ms" << std::endl;
// }

template <typename T>
void sort(T &l)
{
	std::clock_t start = std::clock();
	merge_insertion_sort(l);
	double time = (std::clock() - start) / (double)CLOCKS_PER_SEC * 1000;
	std::cout << DV "------" << typeid(l).name() << "------" C << std::endl;
	std::cout << MB "After: " C;
	for (long unsigned int i = 0; i < l.size(); i++)
		std::cout << GREEN << l[i] << C " ";
	std::cout << std::endl;
	std::cout << MB "Time: " C << time << "ms" << std::endl;
}


int run(char **av) {
	std::string buff;
	std::vector<int> v;
	std::deque<int> d;
	for (int i = 1; av[i]; i++) {
		for (int j = 0; av[i][j]; j++)
			if (!isdigit(av[i][j]))
				return error("Invalid input: ", "char: ", std::string(1, av[i][j]).c_str()), 1;
		buff += av[i] + std::string(" ");
		v.push_back(std::atoi(av[i]));
		d.push_back(std::atoi(av[i]));
	}

	std::cout << MB "Before: " C << buff << std::endl;
	// vector_sort(v);
	// deque_sort(d);
	sort(v);
	sort(d);
	return 0;
}