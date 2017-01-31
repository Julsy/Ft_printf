#include "ft_printf.h"

static int	process_str(t_flags *got_flags, va_list *args)
{
	int		len;
	char	*str;

	len = 0;
	str = va_arg(*args, char*);
	if (str == NULL)
	{
		if (got_flags->got_precis == 0 ||
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
	if (got_flags->left_justify && !c)
		len += write(1, "\0", 1);
	if (c == 0)
		flag = 1;
	else
		str[0] = c;
	got_flags->width -= got_flags->width > 0 ? flag : 0;
	process_width_s(&str, got_flags);
	len += ft_strlen(str);
	ft_putstr(str);
	if (flag == 1 && !got_flags->left_justify)
		len += write(1, "\0", 1);
	return (len);
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
