#!/bin/bash
#gcc -L./libft/ -I./libft/ client.c -lft -o client
while true
do
	./client $*
done