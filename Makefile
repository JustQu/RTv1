CC = gcc
RM = rm -rf

CFLAGS = \
		 -I.\
		 -I$(INCDIR)\
		 -I$(LIBFTINC)

LDLIBS = -lft\
		-L$(LIBFTDIR)\
		-lmlx\
		-framework OpenGL\
		-framework AppKit
LDFLAGS	= 

LIBFT = libft.a
LIBFTDIR = ./libft
LIBFTINC = $(LIBFTDIR)/includes

INCDIR = ./include
SRCSDIR = ./
SRCS = main.c
OBJS = $(SRCS:.c=.o)
TARGET = RTv1

.PHONY: all
all: $(LIBFT) $(TARGET)

$(LIBFT):
	make -C $(LIBFTDIR)

$(TARGET): $(OBJS) $(LIB)
	@echo 'making executable'
	@$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)
	@echo DONE!

$(OBJS): %.o: $(SRCSDIR)%.c $(INCDIR)/
	@$(CC) -c $< $(CFLAGS)

#.h
$(INCDIR)/:

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