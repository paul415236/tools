#!/bin/bash

#CFLAG = -D_USE_COLOR_EMPHASIZE_

gcc ${CFLAG} ParallelGrep.c -o turbo_grep -lpthread
