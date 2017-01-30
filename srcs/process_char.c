#include "ft_printf.h"

static int	process_str(t_flags *got_flags, va_list *args)
{
	int		len;
	char	*str;

	len = 0;
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
	return (len);
}

static int	process_char(t_flags *got_flags, va_list *args)
{
	char	*str;
	int		len;
	int		c;
	int		flag;

	len = 0;
	flag = 0;
	c = va_arg(*args, int);
	str = ft_strnew(1);
	if (c == 0 && got_flags->got_width == 0)
		return (1);
	else if (c == 0 && got_flags->got_width == 1 && got_flags->width)
		flag = 1;
	else
		str[0] = c;
	got_flags->width -= flag;
	process_width_s(&str, got_flags);
	len = ft_strlen(str);
	ft_putstr(str);
	return (len + flag);
}

int		process_cCsS(t_flags *got_flags, va_list *args)
{
	int	len;

	len = 0;
	if(got_flags->conv_spec == 's' || got_flags->conv_spec == 'S')
	{
		if (got_flags->len_mod == l || got_flags->conv_spec == 'S')
			len = process_wide_str(got_flags, args);
		else
			len = process_str(got_flags, args);
	}
	else if(got_flags->conv_spec == 'c' || got_flags->conv_spec == 'C')
	{
		if (got_flags->len_mod == l || got_flags->conv_spec == 'C')
			len = process_wide_char(got_flags, args);
		else
			len = process_char(got_flags, args);
	}
	return(len);
}
