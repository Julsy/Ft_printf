#include "ft_printf.h"

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
	{
		if (got_flags->pad_zero == 1)
		{
			if (*str[0] == '-')
			{
				ft_memset(tmp, '0', got_flags->width - ft_strlen(*str) + 1);
				tmp[0] = '-';
				*str = ft_strsub(*str, 1, ft_strlen(*str) - 1);
				tmp = ft_strjoin(tmp, *str);
			}
			else
				ft_memset(tmp, '0', got_flags->width - ft_strlen(*str));
		}
		else
		{
			ft_memset(tmp, ' ', got_flags->width - ft_strlen(*str));
		}
		ft_strcpy(tmp + got_flags->width - ft_strlen(*str), *str);
	}
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

void	process_precision_s(char **str, t_flags *got_flags)
{
	if (got_flags->got_precis == 0)
		return ;
	if (got_flags->length <= got_flags->precision)
		return ;
	*str = ft_strndup(*str, got_flags->precision); // cut part of the str
}

void	process_precision_ws(wchar_t **wstr, t_flags *got_flags)
{
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	if (got_flags->got_precis == 0)
		return ;
	if (ft_wstrlen(*wstr) <= got_flags->precision)
		return ;
	while ((*wstr)[i] && len <= got_flags->precision)
		len += ft_wcharlen((*wstr)[i++]);
	(*wstr)[i - 1] = 0;
}

void	process_precision_i(char **str, t_flags *got_flags)
{
	char	*tmp;

	if (got_flags->got_precis == 0)
		return ;
	if (got_flags->length > got_flags->precision)
		return ;
	got_flags->pad_zero = 0;
	tmp = ft_strnew(got_flags->precision);
	if (*str[0] == '-')
	{
		ft_memset(tmp, '0', got_flags->precision - 1);
		tmp[0] = '-';
		//printf("TMP %s\n", tmp);
		*str = ft_strsub(*str, 1, ft_strlen(*str) - 1);
		tmp = ft_strjoin(tmp, *str);
	}
	else
	{
		ft_memset(tmp, '0', got_flags->precision - got_flags->length);
		ft_strcpy(tmp + got_flags->precision - ft_strlen(*str), *str);
	}
	*str = tmp;
}
