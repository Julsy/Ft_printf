#include "ft_printf.h"

static char	*right_justify(char **str, t_flags *got_flags, char *tmp)
{
	if (got_flags->pad_zero == 1)
	{
		if (*str[0] == '-' || got_flags->space)
		{
			ft_memset(tmp, '0', got_flags->width - ft_strlen(*str) + 1);
			tmp[0] = got_flags->space ? ' ' : '-';
			*str = ft_strsub(*str, 1, ft_strlen(*str) - 1);
			tmp = ft_strjoin(tmp, *str);
		}
		else
			ft_memset(tmp, '0', got_flags->width - ft_strlen(*str));
	}
	else
		ft_memset(tmp, ' ', got_flags->width - ft_strlen(*str));
	ft_strcpy(tmp + got_flags->width - ft_strlen(*str), *str);
	return (tmp);
}

void	process_width_s(char **str, t_flags *got_flags)
{
	int		len;
	char	*tmp;

	len = 0;
	if (got_flags->got_width == 0)
		return ;
	if ((unsigned int)got_flags->width <= ft_strlen(*str))
		return ;
	tmp = ft_strnew(got_flags->width);
	if (got_flags->left_justify == 1)
	{
		ft_strcpy(tmp, *str);
		ft_memset(tmp + ft_strlen(*str), ' ', got_flags->width - ft_strlen(*str));
	}
	else
		tmp = right_justify(str, got_flags, tmp);
	*str = tmp;
}

int		process_width_i(unsigned int i, t_flags *got_flags)
{
	int		len;
	char	*tmp;

	len = 0;
	if (got_flags->got_width == 0)
		return (0);
	tmp = ft_strnew(got_flags->width);
	if (got_flags->width < 0)
		ft_memset(tmp, ' ', i);
	else
		ft_memset(tmp, ' ', got_flags->width - i);
	len = ft_strlen(tmp);
	ft_putstr(tmp);
	return (len);
}

// void	ft_conv_ws(char in, t_output *out, t_arg *flags, va_list *ap)
// {
// 	wchar_t *s;
// 	char	*str;

// 	(void)in;
// 	s = va_arg(*ap, wchar_t *);
// 	if (!s)
// 	{
// 		if (!flags->got_precis
// 			|| (flags->got_precis && flags->precision >= 6))
// 			str = ft_strdup("(null)");
// 		else
// 			str = ft_strdup("");
// 	}
// 	else
// 	{
// 		s = wchar_dup(s);
// 		handle_precision((char **)&s, flags, 'w');
// 		str = wchars_to_str(s);
// 	}
// 	handle_padding(&str, flags, 'w');
// 	out->str = ft_strnjoin(out->str, out->len, str, ft_strlen(str));
// 	out->len += ft_strlen(str);
// }

// int		process_width_ws(wchar_t **wstr, t_flags *got_flags)
// {
// 	int		i;
// 	int		start;
// 	size_t	len;
// 	wchar_t	*tmp;

// 	i = 0;
// 	len = 0;
// 	if (got_flags->got_width == 0)
// 		return (0);
// 	if (got_flags->pad_zero || got_flags->left_justify)
// 		return (-1);
// 	if ((unsigned int)got_flags->width <= ft_wstrlen(*wstr))
// 		return (0);
// 	tmp = (wchar_t *)malloc(sizeof(wchar_t) * (ft_wstrlen(*wstr) + 1));
// 	printf("%lu\n", got_flags->width - ft_wstrlen(*wstr));
// 	ft_memset((char *)tmp, ' ', got_flags->width - ft_wstrlen(*wstr));
// 	printf("ft_memset: |%S|\n", tmp);
// 	start = got_flags->width - ft_wstrlen(*wstr);
// 	while (wstr[i])
// 	{
// 		tmp[start] = *wstr[i];
// 		start++;
// 		i++;
// 	}
// 	tmp[start] = '\0';
// 	printf("strcpy: |%S|\n", tmp);
// 	*wstr = tmp;
// 	return (0);
// }

