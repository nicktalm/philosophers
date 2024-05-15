CC = cc
NAME = philosophers
CFLAGS = -Wall -Werror -Wextra

SRCS = philosophers.c \

OBJS = $(SRCS:.c=.o)
OBJDIR = objs/
OBJS_PATH = $(addprefix $(OBJDIR), $(OBJS))

RED = '\033[1;31m'
BLUE ='\033[1;34m'
DEF_COLOR = '\033[0;39m'

VPATH = src:src

$(OBJDIR)%.o: %.c
	@mkdir -p $(dir $@)
	@cc -c $< -o $@ $(CFLAGS)

$(NAME):		$(OBJS_PATH)
				@echo $(BLUE)"Compiling $(NAME)..."$(DEF_COLOR)
				@cc $(OBJS_PATH) -o $(NAME)

all:			$(NAME)

clean:
				@echo $(RED)"Cleaning $(NAME)..."$(DEF_COLOR)
				@rm -rf $(OBJDIR)

fclean:			clean
				@echo $(RED)"Removing $(NAME)..."$(DEF_COLOR)
				@rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re