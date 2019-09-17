# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/06 05:49:36 by dmelessa          #+#    #+#              #
#    Updated: 2019/09/17 15:16:52 by dwalda-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

SRC_DIR = ./srcs/
SRC = mat3_init.c mat3_inv.c mat3_mul.c mat3_transpose.c\
	mat4_copy.c mat4_init.c mat4_inv.c mat4_mul.c mat4_trace.c mat4_transpose.c\
	vec3_distance.c vec3_init.c vec3_mul.c vec3_normalize.c vec3_rotate.c vec3_sub.c vec3_wrap.c\
	vec4_init.c vec4_mul.c vec4_normalize.c vec4_sub.c vec4_sum.c vec3_sum.c\
	utils1.c utils2.c

INC_DIR = ./includes/
INCS = rtmath.h mat3.h mat4.h rt_types.h utils.h vec3.h vec4.h
INCS := $(addprefix $(INCDIR), $(INCS))

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -O3

NAME = librtmath.a

.PHONY: all
all : $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $^
	@echo '$(NAME) created'

VPATH = ./includes/

$(OBJ): %.o: %.c $(INCS)
	@$(CC) $(CFLAGS) -c $*.c -I $(INC_DIR)

.PHONY: clean
clean:
	@echo 'deliting $(NAME) object files'
	@rm -rf $(OBJ)

.PHONY: fclean
fclean: clean
	@echo 'deliting $(NAME)'
	@rm -f $(NAME)

.PHONY: re
re: fclean all
