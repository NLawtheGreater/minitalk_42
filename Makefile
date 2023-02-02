# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niclaw <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 13:59:17 by niclaw            #+#    #+#              #
#    Updated: 2022/10/28 21:23:52 by niclaw           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### EXECUTABLE ###
# This is where you want to put the name of your program or library that you will be compiling

NAME1	= server
NAME2	= client
BONUS_NAME1	= server_bonus
BONUS_NAME2	= client_bonus

### DIR ###
# all the dir to neatly keep your .c and .h

DIRSRC		= src/
BONUS_DIR	= bonus/
HEAD		= include/
SHARE_DIR	= share/
LIBDIR		= libft/
BUILD =	./build/

### TESTER GIT URL ###
# add some git url to your makefile to make your evaluator life easier

TESTER1		= 
TESTER2		= 
TESTER3		=
TESTER4		=

### SOURCE FILE ###
# the name of your .c go here. SRC is for mandatory, BONUS is for the bonus. 
# SHARE is for .c file that your mandatory and bonus use. LIBFT is where your specific libft .c file go.

SRC1	=	server.c
SRC2	=	client.c

BONUS1	=	server_bonus.c
BONUS2	=	client_bonus.c

SHARE	=

### PATH ###
# DO NOT CHANGE
SRCS1		= ${addprefix ${DIRSRC}, ${SRC1}}
SRCS2		= ${addprefix ${DIRSRC}, ${SRC2}}
BONUS_SRCS1	= ${addprefix ${BONUS_DIR}, ${BONUS1}}
BONUS_SRCS2	= ${addprefix ${BONUS_DIR}, ${BONUS2}}
SHARE_SRCS	= ${addprefix ${SHARE_DIR}, ${SHARE}}

### OBJECT FILE ###
# DO NOT CHANGE
OBJS1		= ${SRCS1:.c=.o}
OBJS2		= ${SRCS2:.c=.o}
BONUS_OBJS1	= ${BONUS_SRCS1:.c=.o}
BONUS_OBJS2	= ${BONUS_SRCS2:.c=.o}
SHARE_OBJS	= ${SHARE_SRCS:.c=.o}

## LIBFT TARGET ##
LIBFT	= ${LIBDIR}libft.a

### COMPILATION ###
# the compilation flag that will we will use for the project

CC	= gcc
CFLAGS	= -g -Wall -Wextra -Werror -std=gnu99
RM	= rm -f

### COLORS ###
# up to your creativity 
NOC		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m

### TMP ###
# if needed
MSG = "Upload to git"

### RULES ###

all:	${NAME1} ${NAME2}

${NAME1}:	${OBJS1} ${SHARE_OBJS} ${LIBFT} 
	@${CC} ${CFLAGS} ${addprefix ${BUILD}, ${OBJS1}} ${addprefix ${BUILD}, ${SHARE_OBJS}}\
	${LIBFT} -o ${NAME1}
	@echo "$(GREEN) $@ Linking Done!$(NOC)" 

${NAME2}:	${OBJS2} ${SHARE_OBJS} ${LIBFT} 
	@${CC} ${CFLAGS} ${addprefix ${BUILD}, ${OBJS2}} ${addprefix ${BUILD}, ${SHARE_OBJS}}\
	${LIBFT} -o ${NAME2}
	@echo "$(GREEN) $@ Linking Done!$(NOC)" 

${LIBFT}:
	make -C ${LIBDIR}
	cp ${LIBFT} ${NAME1}
	cp ${LIBFT} ${NAME2}

.c.o:	${HEAD} ${LIBDIR} ${DIRSRC} ${SHARE_DIR} ${BONUS_DIR}
	@mkdir -p ${addprefix ${BUILD}, ${DIRSRC}}
	@mkdir -p ${addprefix ${BUILD}, ${SHARE_DIR}}
	@mkdir -p ${addprefix ${BUILD}, ${BONUS_DIR}}
	${CC} ${CFLAGS} -I ${LIBDIR} -I ${HEAD} \
	 -c $< -o ${addprefix ${BUILD}, ${<:.c=.o}}
	 
bonus:	${BONUS_OBJS1} ${BONUS_OBJS2} ${SHARE_OBJS} ${LIBFT}
	@${CC} ${CFLAGS} ${addprefix ${BUILD}, ${BONUS_OBJS1}} ${addprefix ${BUILD}, ${SHARE_OBJS}}\
	${LIBFT} -o ${NAME1}
	@${CC} ${CFLAGS} ${addprefix ${BUILD}, ${BONUS_OBJS2}} ${addprefix ${BUILD}, ${SHARE_OBJS}}\
	${LIBFT} -o ${NAME2}
	@echo "$(GREEN)BONUS DONE$(NOC)"

clean:
	@echo "$(RED)clean$(NOC)"
	${RM} -r ${BUILD}
	make clean -C ${LIBDIR} 

fclean:	clean
	@echo "$(RED)fclean$(NOC)"
	${RM} ${NAME1} ${NAME2} ${BONUS_NAME}
	make fclean -C ${LIBDIR} 

re:	fclean all

## MINITALK ##

t1:	
t2:	

test2:
#< infile CCwc -w | grep outfile

mem:		
#./pipex ${FILE1} ${COM1} ${COM2} ${FILE2}
	valgrind -s --leak-check=full ./server
mem2:		
#./pipex ${FILE1} ${COM1} ${COM2} ${FILE2}
	valgrind -s --leak-check=full ./client 4648 "sdkjdsklhjfdklshfkldjs12145646212616165dskfj"
#./pipex ${FILE1} ${COM1} ${COM2} ${FILE2}

tester:
	@echo "$(YELLOW)Testers are not perfect but its good enough$(NOC)"
	git clone ${TESTER1} TESTER1
	git clone ${TESTER2} TESTER2
#git clone ${TESTER3} TESTER3
#git clone ${TESTER3} TESTER4

norm:
	norminette

gitpush:
	git add .
	git status
	git commit -m "${MSG}"
	git push

help:
	@clear
	@echo "$(GREEN)Avaibles options:$(NOC)"
	@echo "$(RED)==================$(NOC)"
	@echo "$(RED)| $(YELLOW)make ${NAME} $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make bonus     $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make norm      $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make tester    $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make clean     $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make fclean    $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make re        $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make help      $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make test      $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make mem      $(RED)|$(NOC)"
	@echo "$(RED)==================$(NOC)"

.PHONY:	all clean fclean re bonus test mem