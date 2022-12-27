#!/bin/bash

while [ 1 ]
do
    leaks minishell | grep "leaked bytes"
    sleep 1
done
