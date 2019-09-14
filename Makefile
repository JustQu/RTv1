CC = gcc
RM = rm -rf
UNAME_S := $(shell uname -s)

CFLAGS = -O3\
		 -I.\
		 -I$(INCDIR)\
		 -I$(LIBFTINC)\
		 -I$(RTMATHINC)\
		 -I$(MLXINC)\
		 -Wall\
		 -Werror\
		 -Wextra

LDLIBS = -lm\
		-lft\
		-lmlx\
		-lrtmath

ifeq ($(UNAME_S),Linux)
	LDLIBS += -L/usr/X11/lib -lXext -lX11
endif
ifeq ($(UNAME_S), Darwin)
	LDLIBS += -framework OpenGL -framework AppKit
endif

LDFLAGS	= \
		-L$(LIBFTDIR)\
		-L$(RTMATHDIR)\
		-L$(MLXDIR)

LIBFT = libft.a
LIBFTDIR = ./libft
LIBFTINC = $(LIBFTDIR)/includes

MLXDIR = ./minilibx
MLXINC = ./minilibx/include

RTMATH = rtmath.a
RTMATHDIR = ./rtmath
RTMATHINC = $(RTMATHDIR)/includes

INCDIR = ./includes/
SRCSDIR = ./src/
INCS = rtv1.h
INCS := $(addprefix $(INCDIR), $(INCS))
SRCS = main.c draw.c control.c sphere.c reader.c saver.c camera_movement.c\
		convert_to_16.c ft_itoaf.c list_funcs.c object_initiation.c other_initiation.c\
		other_out.c out_objects.c out_params.c param_reading.c utils.c cone.c cylinder.c normals.c\
		plane.c intersection.c rays.c
OBJS = $(SRCS:.c=.o)
TARGET = RTv1

.PHONY: all
all: $(LIBFT) $(RTMATH) $(TARGET)

$(LIBFT):
	make -C $(LIBFTDIR)
	make -C $(MLXDIR)

$(RTMATH):
	@make -C $(RTMATHDIR)

$(TARGET): $(OBJS)
	@echo 'making executable'
	@$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)
	@echo DONE!

$(OBJS): %.o: $(SRCSDIR)%.c $(INCS)
	@$(CC) -c $< $(CFLAGS)

.PHONY: clean
clean:
	@echo deliting object files
	@$(RM) $(OBJS)
	@make -C $(LIBFTDIR) clean
	@make -C $(RTMATHDIR) clean
	@make -C $(MLXDIR) clean

.PHONY: fclean
fclean: clean
	@echo deliting executable file
	@$(RM) $(TARGET)
	@make -C $(LIBFTDIR) fclean
	@make -C $(RTMATHDIR) fclean
	@make -C $(MLXDIR) clean

.PHONY: re
re:	fclean all
