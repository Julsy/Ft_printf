#include "ft_printf.h"
// #include <locale.h>
#include <wchar.h>

static void		ft_putwchar(wchar_t c)
{
	if (c <= 0x7F)
		ft_putchar(c);
	else if (c <= 0x7FF)
	{
		ft_putchar((c >> 6) + 0xC0);
		ft_putchar((c & 0x3F) + 0x80);
	}
	else if (c <= 0xFFFF)
	{
		ft_putchar((c >> 12) + 0xE0);
		ft_putchar(((c >> 6) & 0x3F) + 0x80);
		ft_putchar((c & 0x3F) + 0x80);
	}
	else if (c <= 0x10FFFF)
	{
		ft_putchar((c >> 18) + 0xF0);
		ft_putchar(((c >> 12) & 0x3F) + 0x80);
		ft_putchar(((c >> 6) & 0x3F) + 0x80);
		ft_putchar((c & 0x3F) + 0x80);
	}
}

static void		ft_putwstr(wchar_t *s)
{
	int i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putwchar(s[i]);
		i++;
	}
}

int		process_char(t_flags *got_flags, va_list *args)
{
	int		c;
	int		len;
	char	*str;
	wchar_t	wchar;
	wchar_t	*wstr;

	len = 0;
	if(got_flags->conv_spec == 's' || got_flags->conv_spec == 'S')
	{
		if (got_flags->len_mod == l || got_flags->conv_spec == 'S')
		{
			wstr = va_arg(*args, wchar_t*);
			if (wstr == NULL)
			{
				if (!got_flags->got_precis ||
					(got_flags->got_precis && got_flags->precision))
					str = ft_strdup("(null)");
				else
					str = ft_strdup("");
				process_width_s(&str, got_flags);
				len = ft_strlen(str);
				ft_putstr(str);
				return(len);
				//free(str);
			}
			else
			{
				process_precision_ws(&wstr, got_flags);
				process_width_s((char **)&wstr, got_flags);
				len = ft_wstrlen(wstr);		
				ft_putwstr(wstr);
				return(len);
			}
		}
		else
		{
			str = va_arg(*args, char*);
			if (str == NULL)
			{
				if (!got_flags->got_precis ||
					(got_flags->got_precis && got_flags->precision))
				str = ft_strdup("(null)");
				else
					str = ft_strdup("");
			}
			got_flags->length = ft_strlen(str);
			process_precision_s(&str, got_flags);
			process_width_s(&str, got_flags);
			len = ft_strlen(str);
			ft_putstr(str);
			return(len);
			//free(str);
		}
	}
	else if(got_flags->conv_spec == 'c' || got_flags->conv_spec == 'C')
	{
		if (got_flags->len_mod == l || got_flags->conv_spec == 'C')
		{
			wchar = va_arg(*args, wchar_t);
			len = ft_wcharlen(wchar);
			len += process_width_i(len, got_flags);
			ft_putwchar(wchar);
			return(len);
		}
		else
		{
			c = va_arg(*args, int);
			str = ft_strnew(1);
			if (c == 0 && got_flags->got_width == 0)
				return (1);
			else if (c == 0 && got_flags->got_width == 1)
			{
				str[0] = ' ';
				ft_putstr(str);
				return (got_flags->width);
			}
			else
				str[0] = c;
			process_width_s(&str, got_flags);
			len = ft_strlen(str);
			ft_putstr(str);
			return(len);
		}
	}
	return(0);
}
