CC = gcc
RM = rm -rf

CFLAGS = \
		 -I.\
		 -I$(INCDIR)\
		 -I$(LIBFTINC)\
		 -I$(RTMATHINC)\
		 -g

LDLIBS = -lft\
		-lmlx\
		-lrtmath\
		-framework OpenGL\
		-framework AppKit

LDFLAGS	= \
		-L$(LIBFTDIR)\
		-L$(RTMATHDIR)

LIBFT = libft.a
LIBFTDIR = ./libft
LIBFTINC = $(LIBFTDIR)/includes

RTMATH = rtmath.a
RTMATHDIR = ./rtmath
RTMATHINC = $(RTMATHDIR)/includes

INCDIR = ./includes/
SRCSDIR = ./src/
INCS = rtv1.h
INCS := $(addprefix $(INCDIR), $(INCS))
SRCS = main.c draw.c control.c sphere.c
OBJS = $(SRCS:.c=.o)
TARGET = RTv1

.PHONY: all
all: $(LIBFT) $(RTMATH) $(TARGET)

$(LIBFT):
	@make -C $(LIBFTDIR)

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

.PHONY: fclean
fclean: clean
	@echo deliting executable file
	@$(RM) $(TARGET)
	@make -C $(LIBFTDIR) fclean
	@make -C $(RTMATHDIR) clean

.PHONY: re
re:	fclean all
