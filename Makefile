CC = gcc
RM = rm -rf

CFLAGS = \
		 -I.\
		 -I$(INCDIR)\
		 -I$(LIBFTINC)\
		 -I$(RTMATHINC)\

LDLIBS = -lft\
		-lmlx\
		-lrtmath\
		-framework OpenGL\
		-framework AppKit\
		-g

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
	make -C $(LIBFTDIR)

$(RTMATH):
	make -C $(RTMATHDIR)

$(TARGET): $(OBJS) $(LIB)
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
