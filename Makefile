#
## Makefile for Makefile in /home/Mystogun/exopis
##
## Made by Josselin COSMAO
## Login   <Mystogun@epitech.net>
##
## Started on  Sat Oct 15 16:46:52 2016 Josselin COSMAO
## Last update Sun Feb 11 23:10:52 2018 Josselin
##

CC      = gcc

RM      = rm -rf

NAME    = libmy_malloc.so

SRCS    = 	malloc.c \
			other.c

OBJS    = $(SRCS:.c=.o)

CFLAGS  +=  -Wall -Wextra -fPIC

all:    $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -shared -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:     fclean all

.PHONY: all clean fclean re
