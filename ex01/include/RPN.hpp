#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <cstdlib>

# define RED "\x1b[1m\x1b[38;2;255;0;0m"
# define MB "\x1b[1m\x1b[38;2;25;25;599m"
# define GREEN "\x1b[1m\x1b[38;2;0;128;0m"
# define YELLOW "\x1b[1m\x1b[38;2;205;205;0m"
# define DV "\x1b[1m\x1b[38;2;148;0;211m"
# define C "\x1b[0m"

void	error(const char *type, const char *msg, const char *bold);
int		compute(const char *str);

#endif