#!/bin/bash

while true
do
    valgrind --leak-check=yes ./Minishell
    sleep 100
done 
