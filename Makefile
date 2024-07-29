RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
END_COLOR = \033[0m
BOLD_GREEN = \033[1;32m
BOLD_YELLOW = \033[1;33m
END = \033[0m

NAME = cub3d

CFLAGS = -Wall -Werror -Wextra -g

LIBMLX_DIR = lib/

VGFLAGS = valgrind --leak-check=full --suppressions=sup --track-origins=yes --show-leak-kinds=all --log-file=leaks.log -s

TESTFLAGS = -fsanitize=address

INCDIR:=srcs
ODIR:=obj

SRC := closing.c freeing.c handlers.c init_window.c \
		main.c main_utils.c minimaper.c raycaster.c

OBJ := $(patsubst %.c, $(ODIR)/%.o,$(SRC))

LIBFLAGS = -I$(LIBMLX_DIR) -L$(LIBMLX_DIR) -lmlx -lX11 -lXext -lm

CC = cc

RM = rm -f

TOTAL_FILES := $(words $(SRC))
COMPILED_FILES := $(shell if [ -d "$(ODIR)" ]; then find $(ODIR) -name "*.o" | wc -l; else echo 0; fi)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFLAGS) -o $(NAME)
	@printf "$(BOLD_GREEN)...cub3d in the making: $$(echo "$(shell find $(ODIR) -name "*.o" | wc -l) $(TOTAL_FILES)" | awk '{printf "%.2f", $$1/$$2 * 100}')%%$(RES)\r"
	@printf "\n"
	@echo "${BOLD_GREEN}cub3d is reborn...${END}"

test: $(OBJ)
	@$(CC) $(CFLAGS) $(TESTFLAGS) $(OBJ) $(LIBFLAGS) -o $(NAME)
	@echo "${BOLD_GREEN}...cub3d is reborn${END}"

$(ODIR):
	@mkdir -p $@
	
$(ODIR)/%.o: $(INCDIR)/%.c
	@mkdir -p $(dir $@) 
	@printf "$(BOLD_GREEN)...cub3d in the making: $$(echo "$(shell find $(ODIR) -name "*.o" | wc -l) $(TOTAL_FILES)" | awk '{printf "%.2f", $$1/$$2 * 100}')%%$(RES)\r"
	@$(CC) $(CFLAGS) -c -o $@ $<

fclean: clean
	@$(RM) $(NAME)

clean:
	@$(RM) $(OBJ)
	@echo "${RED}cub3d is no more...${END}"

re: fclean all
