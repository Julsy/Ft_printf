# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iiliuk <iiliuk@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/11 15:25:28 by iiliuk            #+#    #+#              #
#    Updated: 2017/01/11 15:25:28 by iiliuk           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

TMP_LIB = ft_printf.a

CFLAGS = -Wall -Wextra -Werror

ORIG_LIB = libft.a

FILENAMES = ft_printf.c helper.c get_flags.c process_char.c process_ptr.c \
process_digit.c process_percent.c process_flags.c

OBJECTS = $(FILENAMES:.c=.o)

all: $(NAME)

%.o: %.c
	gcc $(CFlAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	ar rc $(TMP_LIB) $(OBJECTS)
	libtool -static -o $@ $(TMP_LIB) $(ORIG_LIB)

clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME) $(TMP_LIB)

re: fclean all

.PHONY: all clean fclean re
