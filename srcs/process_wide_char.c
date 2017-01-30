#include "ft_printf.h"

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

int		process_wide_str(t_flags *got_flags, va_list *args)
{
	wchar_t	*wstr;
	char	*str;
	int		len;

	len = 0;
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
	}
	else
	{
		process_precision_ws(&wstr, got_flags);
		process_width_s((char **)&wstr, got_flags);
		len = ft_wstrlen(wstr);		
		ft_putwstr(wstr);
	}
	return(len);
}

int		process_wide_char(t_flags *got_flags, va_list *args)
{
	int		len;
	wchar_t	wchar;

	len = 0;	
	wchar = va_arg(*args, wchar_t);
	len = ft_wcharlen(wchar);
	len += process_width_i(len, got_flags);
	ft_putwchar(wchar);
	return (len);
}
