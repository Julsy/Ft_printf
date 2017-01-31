#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stddef.h>
# include <stdint.h>
# include "libft.h"
# include <locale.h>
# include <wchar.h>

enum
{
	none,
	hh,
	h,
	l,
	ll,
	j,
	z,
	t
}					len_mod;

typedef struct		s_flags
{
	int				pound;
	int				pad_zero;
	int				left_justify;
	int				space;
	int				sign;
	int				got_width;	
	int				got_precis;
	int				width;
	unsigned int	precision;
	unsigned int	length;
	char			len_mod;
	char			conv_spec;
}					t_flags;

int					get_flags(char *fmt, va_list *args);
size_t				ft_wstrlen(wchar_t *str);
int					ft_wcharlen(wchar_t c);
int					ft_strlen_num(unsigned int x);
void				ft_putstr_tolower(char *s);
int					isnot_percent(int c);
int					process_cCsS(t_flags *got_flags, va_list *args);
int					process_digit(t_flags *got_flags, va_list *args);
int					process_ptr(t_flags *got_flags, va_list *args);
int					process_percent(t_flags *got_flags, va_list *args);
void				process_width_s(char **str, t_flags *got_flags);
int					process_width_i(unsigned int i, t_flags *got_flags);
void				process_precision_s(char **str, t_flags *got_flags);
void				process_precision_i(char **str, t_flags *got_flags);
void				process_precision_ws(wchar_t **wstr, t_flags *got_flags);
int					process_width_ws(wchar_t **wstr, t_flags *got_flags);
int					process_wide_str(t_flags *got_flags, va_list *args);
int					process_wide_char(t_flags *got_flags, va_list *args);
int					process_o(t_flags *got_flags, va_list *args);
int					process_u(t_flags *got_flags, va_list *args);
int					process_x(t_flags *got_flags, va_list *args);

int					ft_printf(char *fmt, ...);

#endif

// • You have to manage the following conversions: sSpdDioOuUxXcC
// • You must manage %%
// • You must manage the flags #0-+ and space
// • You must manage the minimum field-width
// • You must manage the precision
// • You must manage the flags hh, h, l, ll, j, et z

// 0. 28 basic tests failed -> continue working on NULL str
// 1. Error check, continue tests (order? in x - what's first? what's when value = 0?)
// 2. Finish separating files for each conv spec
// 3. Check.sh - Acti's test (compare test itself with system and user output)

// http://en.cppreference.com/w/cpp/io/c/fprintf
