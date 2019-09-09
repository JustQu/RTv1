CC = gcc
RM = rm -rf

CFLAGS = \
		 -I.\
		 -I$(INCDIR)\
		 -I$(LIBFTINC)\
		 -I$(RTMATHINC)\
		 -I$(MLXDIR)\
		 -g

LDLIBS = -lft\
		-lmlx\
		-lrtmath\
		-framework OpenGL\
		-framework AppKit

LDFLAGS	= \
		-L$(LIBFTDIR)\
		-L$(RTMATHDIR)\
		-L$(MLXDIR)

LIBFT = libft.a
LIBFTDIR = ./libft
LIBFTINC = $(LIBFTDIR)/includes

MLXDIR = ./minilibx_macos

RTMATH = rtmath.a
RTMATHDIR = ./rtmath
RTMATHINC = $(RTMATHDIR)/includes

INCDIR = ./includes/
SRCSDIR = ./src/
INCS = rtv1.h
INCS := $(addprefix $(INCDIR), $(INCS))
SRCS = main.c draw.c control.c sphere.c reader.c
OBJS = $(SRCS:.c=.o)
TARGET = RTv1

.PHONY: all
all: $(LIBFT) $(RTMATH) $(TARGET)

$(LIBFT):
	make -C $(LIBFTDIR)
	make -C $(MLXDIR)

$(RTMATH):
	make -C $(RTMATHDIR)

$(TARGET): $(OBJS)
	@echo 'making executable'
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)
	@echo DONE!

$(OBJS): %.o: $(SRCSDIR)%.c $(INCS)
	$(CC) -c $< $(CFLAGS)

.PHONY: clean
clean:
	@echo deliting object files
	@$(RM) $(OBJS)
	@make -C $(LIBFTDIR) clean

.PHONY: fclean
fclean: clean
	@echo deliting executable file
	@$(RM) $(TARGET)
	@make -C $(LIBFTDIR) fclean

.PHONY: re
re:	fclean all
