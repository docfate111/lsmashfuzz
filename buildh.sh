#!/bin/sh

gcc -g -Wall -I /usr/local/include -L /usr/local/lib harness.c -o h -llsmash
