#badger
CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

include:=/home/badger/document/code/cpp/lib/SFML-2.5.1/include/
lib:=/home/badger/document/code/cpp/lib/SFML-2.5.1/lib/
name:=main
title:=darkness_rises
in:=./$(name).cpp
out:=./bin/$(title).exe
bin:=./bin/$(name).o

default:all

all:compile
	$(out)

compile:$(in)
	$(CC) $(CFLAGS) -I $(include) -L $(lib) $(in) -o $(bin)
	$(CC) $(bin) -o $(out) $(LDFLAGS)

clean:
	rm -f $(bin)