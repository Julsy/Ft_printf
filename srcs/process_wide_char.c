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

// static void		ft_putwstr(wchar_t *s)
// {
// 	int i;

// 	if (!s)
// 		return ;
// 	i = 0;
// 	while (s[i])
// 	{
// 		ft_putwchar(s[i]);
// 		i++;
// 	}
// }

static wchar_t	*ft_wstrdup(wchar_t *str)
{
	wchar_t	*res;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	res = (wchar_t *)malloc(sizeof(wchar_t) * (ft_wstrlen(str) + 1));
	while (i < ft_wstrlen(str))
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}

void	wchar_to_str(wchar_t in, char *str)
{
	if (in <= 0x7F)
		str[0] = in;
	else if (in <= 0x7FF)
	{
		str[0] = 192 | (((unsigned int)(in) >> 6) & 63);
		str[1] = 128 | ((unsigned int)(in) & 63);
	}
	else if (in <= 0xFFFF)
	{
		str[0] = 224 | (((unsigned int)(in) >> 12) & 63);
		str[1] = 128 | (((unsigned int)(in) >> 6) & 63);
		str[2] = 128 | ((unsigned int)(in) & 63);
	}
	else if (in <= 0x10FFFF)
	{
		str[0] = 240 | (((unsigned int)(in) >> 18) & 63);
		str[1] = 128 | (((unsigned int)(in) >> 12) & 63);
		str[2] = 128 | (((unsigned int)(in) >> 6) & 63);
		str[3] = 128 | ((unsigned int)(in) & 63);
	}
}

char	*wchars_to_str(wchar_t *in)
{
	size_t	len;
	char	*ret;
	int		pos;

	len = ft_wstrlen(in);
	ret = ft_strnew(len);
	pos = 0;
	while (*in)
	{
		wchar_to_str(*in, ret + pos);
		pos += ft_wcharlen(*in);
		in++;
	}
	return (ret);
}

int		process_wide_str(t_flags *got_flags, va_list *args)
{
	wchar_t	*wstr;
	char	*str;
	int		len;

	len = 0;
	wstr = ft_wstrdup(va_arg(*args, wchar_t*));
	if (wstr == NULL)
	{
		if (!got_flags->got_precis ||
			(got_flags->got_precis && got_flags->precision >= 6))
			str = ft_strdup("(null)");
		else
			str = ft_strdup("");
		process_width_s(&str, got_flags);
		len = ft_strlen(str);
	}
	else
	{
		process_precision_ws(&wstr, got_flags);
		str = wchars_to_str(wstr);
		process_width_s(&str, got_flags);
		if (got_flags->got_width)
			len = ((unsigned int)got_flags->width > ft_wstrlen(wstr)) ? got_flags->width : ft_wstrlen(wstr);
		else
			len = ft_wstrlen(wstr);
	}
	ft_putstr(str);
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
