#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2 -g

all: $(NOM)

$(NOM):	$(OBJ)
	@echo creating libmlx
	@ar -r $(NOM) $(OBJ)
	@ranlib $(NOM)

clean:
	@echo deleting libmlx
	@rm -f $(NOM) $(OBJ) *~
	@rm -f mlx_app

re: clean all
