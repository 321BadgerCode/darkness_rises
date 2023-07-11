#badger
CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

include:=/home/badger/document/code/cpp/lib/SFML-2.5.1/include/SFML/
lib:=/home/badger/document/code/cpp/lib/SFML-2.5.1/lib/
name:=editor
in:=./$(name)/$(name).cpp
out:=./$(name)/$(name).exe
bin:=./$(name)/$(name).o

default:all

all:compile
	$(out)

compile:$(in)
	$(CC) $(CFLAGS) -I $(include) -L $(lib) $(in) -o $(bin)
	$(CC) $(bin) -o $(out) $(LDFLAGS)

clean:
	rm -f $(bin)