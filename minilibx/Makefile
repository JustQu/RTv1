UNAME_S := $(shell uname -s)
TARGET := libmlx.a
MINILIBX_DIR :=
ifeq ($(UNAME_S), Linux)
	MINILIBX_DIR := ./X11
endif
ifeq ($(UNAME_S), Darwin)
	MINILIBX_DIR := ./minilibx_macos
endif

.PHONY: all
all : $(TARGET)

$(TARGET):
	echo $(MINILIBX_DIR)
	make -C $(MINILIBX_DIR) all
	cp $(MINILIBX_DIR)/$(TARGET) ./

.PHONY: clean
clean:
	@make -C $(MINILIBX_DIR) clean


.PHONY: fclean
fclean: clean
	rm $(TARGET)

.PHONY: re
re: fclean all
