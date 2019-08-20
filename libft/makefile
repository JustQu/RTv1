# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/06 05:49:36 by dmelessa          #+#    #+#              #
#    Updated: 2019/07/28 17:56:38 by dmelessa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRC_DIR = srcs/
INC_DIR = includes/
SRC = $(addprefix ft_,\
	memset.c bzero.c memcpy.c memccpy.c memmove.c memchr.c memcmp.c strlen.c \
	strnlen.c strdup.c strcpy.c strncpy.c strcat.c strncat.c strlcat.c \
	strchr.c strrchr.c strstr.c strnstr.c strcmp.c strncmp.c atoi.c isalpha.c \
	isdigit.c isalnum.c isascii.c isprint.c toupper.c tolower.c islower.c isupper.c \
	memalloc.c memdel.c strnew.c strdel.c strclr.c striter.c striteri.c strmap.c \
	strmapi.c strequ.c strnequ.c strsub.c strjoin.c strtrim.c strsplit.c itoa.c \
	putchar.c putstr.c putendl.c putnbr.c putchar_fd.c putstr_fd.c putendl_fd.c \
   putnbr_fd.c lstnew.c lstdelone.c lstdel.c lstadd.c lstiter.c lstmap.c isspace.c\
   strndup.c wc.c strtol.c swap.c isbase.c) get_next_line.c
CFLAGS = -Wall -Wextra -Werror
TARGET = libft.a
OBJ = $(SRC:.c=.o)

.PHONY: all
all : $(TARGET)

$(TARGET): $(OBJ)
	@ar rc $(TARGET) $^
	@echo 'libft.a created' 
$(OBJ): %.o: %.c $(INC_DIR)libft.h
	@echo compiling $<
	@$(CC) $(CFLAGS) -c $*.c -I $(INC_DIR)

.PHONY: clean
clean:
	@echo 'deliting object files'
	@rm -rf $(OBJ)

.PHONY: fclean
fclean: clean
	@echo 'deliting libft.a'
	@rm -f $(TARGET)

.PHONY: re
re: fclean all
