# Makefile for Beginning Linux Programming 3rd Edition
# Chapter 8

CC=gcc
CONNECT=connect1 connect2
INSERT=insert1 insert2
SELECT=select1 select2 select3 select4
UPDATE=update1

ALL=$(CONNECT) $(INSERT) $(SELECT) $(UPDATE)

all: $(ALL)

CFLAGS=-I/usr/include/mysql -Wall -g
# LDFLAGS=-lmysqlclient -g
LDFLAGS=-L/usr/lib -lmysqlclient 


clean:
	@rm -f $(ALL) *~
