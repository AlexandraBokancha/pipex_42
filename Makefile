NAME			=	pipex

SRC				=	src/ft_split.c src/main.c src/path.c \
					src/utils.c src/error.c

OBJS			=	${SRC:.c=.o}

CC				=	cc

HEAD 			= -Isrc/pipex.h

CFLAGS			= -Wall -Wextra -Werror -g3

all				:	${NAME}

%.o: %.c pipex.h
	@${CC} ${CFLAGS} ${HEAD} -c $< -o $@ >/dev/null 2>&1

$(NAME)			:	${OBJS}	
	@${CC} ${CFLAGS} -g3 ${OBJS} -o ${NAME} >/dev/null 2>&1
	@echo "\nPIPEX IS CREATED"

clean			:
	@rm -rf ${OBJS}

fclean			:	clean
	@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re
