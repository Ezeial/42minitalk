NAME_SERVER	=	server
NAME_CLIENT	=	client

LIB_FOLDER	=	libft

INCLUDES	=	includes/minitalk.h

SRCS_CLIENT	=	srcs/client.c
SRCS_SERVER	=	srcs/server.c srcs/server_utils.c

OBJS_CLIENT =	$(SRCS_CLIENT:.c=.o)
OBJS_SERVER	=	$(SRCS_SERVER:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror
CC			=	gcc

all: ${NAME_CLIENT} ${NAME_SERVER}

$(NAME_SERVER): $(OBJS_SERVER) $(INCLUDES)
	make -C ${LIB_FOLDER}
	$(CC) ${CFLAGS} -L./${LIB_FOLDER} -I./libft/includes $(OBJS_SERVER) -lft -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(INCLUDES)
	make -C ${LIB_FOLDER}
	$(CC) ${CFLAGS} -L./${LIB_FOLDER} -I./libft/includes $(OBJS_CLIENT) -lft -o $(NAME_CLIENT)

clean:
	make clean -C ${LIB_FOLDER}
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

fclean: clean
	make fclean -C ${LIB_FOLDER}
	rm -f $(NAME_SERVER)
	rm -f $(NAME_CLIENT)

re:
	make fclean
	make all

.PHONY: all clean fclean re
