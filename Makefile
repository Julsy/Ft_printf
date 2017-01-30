NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

FILES = ft_printf.c helper.c get_flags.c process_char.c process_ptr.c \
process_digit_id.c process_digit_oux.c process_percent.c process_width.c process_precision.c \
process_wide_char.c

LIBFT = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c \
ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c \
ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
ft_lstmap.c ft_list_size.c ft_list_add_back.c ft_list_last.c \
ft_list_push_params.c ft_list_nth.c ft_list_reverse.c ft_realloc.c ft_abs.c \
ft_itoa_base.c ft_strndup.c ft_print_memory.c ft_get_next_line.c \
ft_itoa_unbase.c

FILE_SRCS = $(addprefix srcs/,$(FILES))

LIBFT_SRCS = $(addprefix srcs/libft/,$(LIBFT))

SRCS = $(FILE_SRCS) $(LIBFT_SRCS)

OBJECTS = $(FILES:.c=.o) $(LIBFT:.c=.o)

HDR = -I./includes

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME):
	gcc $(CFlAGS) $(HDR) -c $(SRCS)
	ar rc $(NAME) $(OBJECTS)

test:
	gcc $(CFLAGS) $(HDR) $(SRCS) test/main.c -L. test/libft.a -o test/a.out
	./test/a.out
	@rm -f $(OBJECTS)

clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME) 

re: fclean all

lib:
	gcc $(CFLAGS) $(HDR) -c $(LIBFT_SRCS)
	ar rc test/libft.a $(LIBFT:.c=.o)
	@rm -f $(OBJECTS)
