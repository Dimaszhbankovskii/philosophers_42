NAME	=	philo

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

INCLUDES	=	includes
HEADER		=	philosophers.h

SRCS_DIR		=	srcs

SRCS_LIST	=	main.c \
				init_data.c \
				philo.c \
				utils.c \
				end_program.c
SRCS		=	$(addprefix $(SRCS_DIR)/,$(SRCS_LIST))

OBJS_DIR	=	objs

OBJS		=	$(addprefix $(OBJS_DIR)/,$(SRCS_LIST:.c=.o))
OBJS_FUNC	=	$(addprefix $(OBJS_DIR)/,$(SRCS_LIST_FUNC:.c=.o))

NORMAL		=	\033[0m
BOLD		=	\033[1m
UNDERLINE	=	\033[4m
BLACK		=	\033[1;30m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
VIOLET		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m

all : $(OBJS_DIR) $(NAME)

$(NAME) : $(OBJS) $(OBJS_FUNC)
	@$(CC) $(CFLAGS) -o $@ $^ -lpthread
	@echo "$(GREEN)Project succesfully compiled"

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c $(INCLUDES)/$(HEADER) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Creating object file$(WHITE) --> $(notdir $@) --> $(GREEN)[Done]$(NORMAL)"

$(OBJS_DIR) :
	@mkdir -p objs
	@echo "$(CYAN)Creating directory for objects file$(WHITE) --> $@ --> $(GREEN)[Done]$(NORMAL)"

clean :
	@rm -rf $(OBJS_DIR)
	@echo "$(VIOLET)Removing objects files$(WHITE) --> *.o --> $(GREEN)[Done]$(NORMAL)"

fclean : clean
	@rm -rf $(NAME)
	@echo "$(VIOLET)Removing perfoming file$(WHITE) --> $(NAME) --> $(GREEN)[Done]$(NORMAL)"

re : fclean all

.PHONY : all, clean, fclean, re, bonus