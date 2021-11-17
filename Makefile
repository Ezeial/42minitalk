CC 			= 	gcc
NAME_SERVER	=	server
NAME_CLIENT	=	client
LIB_PATH	=	libft/libft.a
INCLUDES	=	includes/minitalk.h
SRCS_CLIENT	=	srcs/client.c
SRCS_SERVER	=	srcs/server.c

OBJS_CLIENT =	$(SRCS_CLIENT:.c=.o)
OBJS_SERVER	=	$(SRCS_SERVER:.c=.o)

#CFLAGS		=	-Wall -Wextra -g3 -fsanitize=address
CFLAGS		=	-Wall -Wextra -Werror

all : $(NAME_SERVER) $(NAME_CLIENT)

######################################### SERVER #########################################
$(NAME_SERVER): $(OBJS_SERVER) $(INCLUDES)
	make -C libft
	$(CC) ${CFLAGS} $(OBJS_SERVER) $(LIB_PATH) -o $(NAME_SERVER)

######################################### CLIENT #########################################
$(NAME_CLIENT): $(OBJS_CLIENT) $(INCLUDES)
	make -C libft
	$(CC) ${CFLAGS} $(OBJS_CLIENT) $(LIB_PATH) -o $(NAME_CLIENT)

##########################################################################################

clean:
	make $@ -C libft
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

fclean: clean
	rm -f $(NAME_SERVER)
	rm -f $(NAME_CLIENT)

re:
	make fclean
	make all

.PHONY: all clean fclean re
