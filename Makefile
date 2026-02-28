CC := cc
NAME := hotrace
BUILD_DIR := .build
INCLUDES = -Ilibft/includes -Iincludes
CFLAGS = -Werror -Wextra -Wall -MD $(INCLUDES)
MODE ?= release

VPATH = src
SRCS = main.c \
	   hash_table.c

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

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
