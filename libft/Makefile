# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afomenko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/13 12:43:47 by afomenko          #+#    #+#              #
#    Updated: 2017/12/13 12:43:50 by afomenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIB_SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	  ft_isprint.c ft_itoa.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	  ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c \
	  ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c \
	  ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c \
	  ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c \
	  ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
	  ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
	  ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c \
	  ft_toupper.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
	  ft_lstiter.c ft_lstmap.c ft_memset.c ft_range.c get_next_line.c ft_strjfree.c \
	  ft_atoi_base.c

PRT_SRCS = ft_printf/ft_printf.c ft_printf/check_struct.c ft_printf/record_struct.c ft_printf/print_s_c.c ft_printf/syntax_s.c ft_printf/print_wc_ws.c\
ft_printf/additional_print_wc_ws.c ft_printf/additional_wchar.c ft_printf/print_d_i_o_x.c ft_printf/syntax_d_i.c ft_printf/syntax_o_x.c\
ft_printf/additional_functions_number.c ft_printf/handle_size.c ft_printf/lib_functions.c ft_printf/lib_functions2.c ft_printf/additional_u.c\
ft_printf/syntax_u.c

OBJS = $(LIB_SRCS:.c=.o) $(GNL_SRCS:.c=.o) $(PRT_SRCS:.c=.o)

INCLUDES = -I libft.h get_next_line/get_next_line.h ft_printf/ft_printf.h

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
