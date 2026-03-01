CC := cc
NAME := hotrace
BUILD_DIR := .build
INCLUDES = -Ilibft/includes -Iincludes
CFLAGS = -Wall -Wextra -Werror -MD $(INCLUDES) -Ofast
MODE ?= release

VPATH = src
SRCS = main.c \
	   hash_table.c \
	   hash_table_utils.c \
	   hash_table_mods.c \
	   get_next_line.c \
	   get_next_line_utils.c \
	   ft_strlen.c \
	   ft_strcpy.c \
	   ft_strcmp.c \
	   ft_bzero.c \
	   ft_fmemcpy.c \
	   ft_calloc.c

OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

ifeq ($(MODE), debug)
	CFLAGS += -g3
endif

all: $(NAME)

$(NAME): $(BUILD_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

keep: CFLAGS += -DKEEP_READING=1 -DDEFAULT_MODE=2
keep: re

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re keep

-include $(DEPS)
