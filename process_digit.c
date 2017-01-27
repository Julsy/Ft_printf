#include "ft_printf.h"

static unsigned long long	get_unsigned_arg(t_flags *got_flags, va_list *args)
{
	if (got_flags->len_mod == hh)
		return (unsigned long long)(char)va_arg(*args, unsigned int);
	if (got_flags->len_mod == h)
		return (unsigned long long)(short int)va_arg(*args, unsigned int);
	if (got_flags->len_mod == none)
		return (unsigned long long)va_arg(*args, unsigned int);
	if (got_flags->len_mod == l)
		return (unsigned long long)va_arg(*args, unsigned long);
	if (got_flags->len_mod == ll)
		return (unsigned long long)va_arg(*args, unsigned long long);
	if (got_flags->len_mod == j)
		return (unsigned long long)va_arg(*args, uintmax_t);
	if (got_flags->len_mod == z)
		return (unsigned long long)va_arg(*args, size_t);
	if (got_flags->len_mod == t)
		return (unsigned long long)va_arg(*args, unsigned long long);
	return (0);
}

static ptrdiff_t	get_signed_arg(t_flags *got_flags, va_list *args)
{
	if (got_flags->len_mod == hh)
		return (ptrdiff_t)(signed char)va_arg(*args, int);
	if (got_flags->len_mod == h)
		return (ptrdiff_t)(short int)va_arg(*args, int);
	if (got_flags->len_mod == none)
		return (ptrdiff_t)va_arg(*args, int);
	if (got_flags->len_mod == l)
		return (ptrdiff_t)va_arg(*args, long);
	if (got_flags->len_mod == ll)
		return (ptrdiff_t)va_arg(*args, long long);
	if (got_flags->len_mod == j)
		return (ptrdiff_t)va_arg(*args, intmax_t);
	if (got_flags->len_mod == z)
		return (ptrdiff_t)va_arg(*args, ssize_t);
	if (got_flags->len_mod == t)
		return (ptrdiff_t)va_arg(*args, ptrdiff_t);
	return (0);
}

int			process_digit(t_flags *got_flags, va_list *args)
{
	int					len;
	char				*str;
	ptrdiff_t			sarg;
	unsigned long long	arg;

	len = 0;
	if (got_flags->conv_spec == 'd' || got_flags->conv_spec == 'D' || got_flags->conv_spec == 'i') /* Print signed decimal integer */
	{
		if (got_flags->conv_spec == 'D')
		{
			got_flags->conv_spec = 'd';
			got_flags->len_mod = l;
		}
		sarg = get_signed_arg(got_flags, args);
		if (got_flags->precision == 0 && !sarg)
		{
			len += process_width_i(0, got_flags);
			return (len);
		}
		str = ft_itoa(sarg);
		got_flags->length = ft_strlen(str);
		//printf("ORIG: %s\n", str);
		process_precision_i(&str, got_flags);
		//printf("PREC: %s\n", str);
		if (got_flags->space && str[0] != '-' && !got_flags->sign)
			str = ft_strjoin(" ", str);
		if (got_flags->sign && sarg >= 0 && !got_flags->pad_zero)
			str = ft_strjoin("+", str);
		//printf("SIGN: %s\n", str);
		process_width_s(&str, got_flags);
		//printf("WIDTH: %s\n", str);
		if (got_flags->sign && sarg >= 0 && got_flags->pad_zero)
			str[0] = '+';
		if (got_flags->pound == 1)
			str = ft_strjoin("0", str);
		len = ft_strlen(str);
		ft_putstr(str);
		//free(str);
	}
	else if (got_flags->conv_spec == 'o' || got_flags->conv_spec == 'O') /* Print unsigned octal integer */
	{
		if (got_flags->conv_spec == 'O')
		{
			got_flags->conv_spec = 'o';
			got_flags->len_mod = l;
		}
		arg = get_unsigned_arg(got_flags, args);
		str = ft_itoa_unbase(arg, 8);
		if (!got_flags->pound)
		{
			if (!arg && got_flags->precision == 0)
			{
				len += process_width_i(0, got_flags);
				return (len);
			}
		}
		else
		{
			str = ft_strjoin("0", str);
			if (!(arg && got_flags->precision))
			{
				ft_putchar('0');
				return (1);
			}
		}
		got_flags->length = ft_strlen(str);
		process_precision_i(&str, got_flags);
		process_width_s(&str, got_flags);
		len = ft_strlen(str);
		ft_putstr(str);
	}
	else if (got_flags->conv_spec == 'u' || got_flags->conv_spec == 'U') /* Print unsigned decimal integer */
	{
		if (got_flags->conv_spec == 'U')
		{
			got_flags->conv_spec = 'u';
			got_flags->len_mod = l;
		}		
		arg = get_unsigned_arg(got_flags, args);
		if (got_flags->precision == 0 && arg == 0)
			return (0);
		str = ft_itoa_unbase(arg, 10);
		got_flags->length = ft_strlen(str);
		process_precision_i(&str, got_flags);
		process_width_s(&str, got_flags);
		len = ft_strlen(str);
		ft_putstr(str);
		// free(str);
	}
	else if (got_flags->conv_spec == 'x')
	{
		arg = get_unsigned_arg(got_flags, args);
		if (got_flags->got_precis && got_flags->precision == 0 && arg == 0)
		{
			str = ft_strnew(1);
			len = ft_strlen(str);
			len += process_width_i(len, got_flags);
			ft_putstr(str);
			return (len);
		}
		if (arg)
		{
			str = ft_itoa_unbase(arg, 16);
			got_flags->length = ft_strlen(str);
			process_precision_i(&str, got_flags);
			if (got_flags->pad_zero && got_flags->pound)
			{
				got_flags->width -= 2;
				process_width_s(&str, got_flags);
			}
			if (ft_strcmp("0", str) && got_flags->pound)
				str = ft_strjoin("0x", str);
			process_width_s(&str, got_flags);
			len = ft_strlen(str);
			ft_putstr_tolower(str);
		}
		else
		{
			str = ft_strjoin("0", str);
			process_width_s(&str, got_flags);
			len = ft_strlen(str);
			ft_putstr(str);
		}
		//free(str);
	}
	else if (got_flags->conv_spec == 'X')
	{
		arg = get_unsigned_arg(got_flags, args);
		if (got_flags->precision == 0 && arg == 0)
			return (0);
		str = ft_itoa_unbase(arg, 16);
		got_flags->length = ft_strlen(str);
		process_precision_i(&str, got_flags);
		process_width_s(&str, got_flags);
		if (got_flags->pound == 1 && !got_flags->got_precis && arg)
			str = ft_strjoin("0X", str);
		len = ft_strlen(str);
		ft_putstr(str);
		//free(str);
	}
	return (len);
}
