#include "ft_printf.h"

int		process_ptr(t_flags *got_flags, va_list *args)
{
	char	*ptr;
	int		len;

	len = 0;
	if(got_flags->conv_spec == 'p')
	{
		ptr = va_arg(*args, void*);
		ptr = ft_itoa_base((long long)ptr, 16);
		ptr = ft_strjoin("0x", ptr);
		got_flags->length = ft_strlen(ptr);
		process_width_s(&ptr, got_flags);
		len = ft_strlen(ptr);
		ft_putstr_tolower(ptr);
		free(ptr);
	}
	return(len);
}
