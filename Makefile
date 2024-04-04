NAME	=	philo

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror ##-g -fsanitize=thread
RM		=	rm -f

SRCS	=	main.c utils.c utils2.c\
			routine.c routine_helpers.c\
			params.c initialization.c

OBJS	=	$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.c.o:
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
			@echo "Compiling $<."

clean:
			@$(RM) $(OBJS)
			@echo "object files cleaned."
			
fclean:		clean
			@$(RM) $(NAME)
			@echo "philosophers cleaned."

re:			fclean all

.PHONY:		all clean fclean re