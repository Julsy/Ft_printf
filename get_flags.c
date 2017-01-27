#include "ft_printf.h"


static void		get_width_precision(char *fmt, t_flags *got_flags)
{
	int i;

	i = 0;
	while(fmt[i] != '\0')
	{
		if(fmt[i] != '.' && fmt[i] != '0' && ft_isdigit(fmt[i]))
		{
			got_flags->got_width = 1;
			got_flags->width = ft_atoi(fmt + i);
			while (fmt[i] && ft_isdigit(fmt[i]))
				i++;
		}
		if(fmt[i] == '.' && fmt[i + 1] != '*')
		{
			got_flags->got_precis = 1;
			got_flags->precision = ft_atoi(fmt + i + 1);
			while (fmt[i] && ft_isdigit(fmt[i + 1]))
				i++;
		}
		i++;
	}
}

static void		get_star(char *fmt, t_flags *got_flags, va_list *args)
{
	int i;
	int arg;

	i = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '*' && !ft_isdigit(fmt[i + 1]))
		{
			arg = va_arg(*args, int);
			if (fmt[i - 1] == '.')
			{	
				if (arg >= 0)
				{
					got_flags->got_precis = 1;
					got_flags->precision = arg;
				}
			}
			else
				if (arg < 0)
					got_flags->left_justify = 1;
				got_flags->got_width = 1;
				got_flags->width = ft_abs(arg);
		}
		else if (fmt[i] == '*')
			arg = va_arg(*args, int);
		i++;
	}
}

static void		get_len_mod(char *fmt, t_flags *got_flags)
{
	int	i;

	i = -1;
	while (fmt[++i] != '\0')
	{
		if (fmt[i] == 'h')
		{
			if (fmt[++i] == 'h')
				got_flags->len_mod = hh;
			else
				got_flags->len_mod = h;
		}
		else if (fmt[i] == 'l')
		{
			if (fmt[++i] == 'l')
				got_flags->len_mod = ll;
			else
				got_flags->len_mod = l;
		}
		else if (fmt[i] == 'j')
			got_flags->len_mod = j;
		else if (fmt[i] == 'z')
			got_flags->len_mod = z;
		else if (fmt[i] == 't')
			got_flags->len_mod = t;
		i++;
	}
}

static int		get_conv(t_flags *got_flags, va_list *args)
{
	int len;

	len = 0;
	if (got_flags->conv_spec == 's' || got_flags->conv_spec == 'S' ||
	got_flags->conv_spec == 'c' || got_flags->conv_spec == 'C')	
		len += process_char(got_flags, args);
	else if (got_flags->conv_spec == 'd' || got_flags->conv_spec == 'D' ||
	got_flags->conv_spec == 'i' || got_flags->conv_spec == 'o' ||
	got_flags->conv_spec == 'O' || got_flags->conv_spec == 'u' ||
	got_flags->conv_spec == 'U' || got_flags->conv_spec == 'x' ||
	got_flags->conv_spec == 'X')
		len += process_digit(got_flags, args);
	else if (got_flags->conv_spec == 'p')
		len += process_ptr(got_flags, args);
	else if (got_flags->conv_spec == '%')
		len += process_percent(got_flags, args);
	return(len);
}

static void		set_up_flags(t_flags *got_flags)
{
	got_flags->pound = 0;
	// got_flags->pad_zero = 1;
	// got_flags->left_justify = 1;
	// got_flags->blank = 1;
	// got_flags->sign = 1;
	got_flags->got_width = 0;
	got_flags->got_precis = 0;
	got_flags->star = 0;
	got_flags->width = 0;
	got_flags->precision = 1;
	got_flags->length = 0;
	got_flags->len_mod = none;
}

int				get_flags(char *fmt, va_list *args)
{
	int			i;
	t_flags		*got_flags;

	i = 0;
	got_flags = (t_flags *)ft_memalloc(sizeof(t_flags));
	got_flags->conv_spec = fmt[ft_strlen(fmt) - 1];
	set_up_flags(got_flags);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '#')
			got_flags->pound = 1;
		if (fmt[i] == '0' && fmt[i - 1] != '.' && !ft_isdigit(fmt[i - 1]))
			got_flags->pad_zero = 1;
		if (fmt[i] == '-')
			got_flags->left_justify = 1;
		if (fmt[i] == ' ')
			got_flags->space = 1;
		if (fmt[i] == '+')
			got_flags->sign = 1;
		i++;
	}
	get_width_precision(fmt, got_flags);
	get_star(fmt, got_flags, args);
	get_len_mod(fmt, got_flags);
	i = get_conv(got_flags, args);
	//free(got_flags);
	return(i);
}
