#==================================================================================#
#                                                                                  #
# makefile                                                                    #
# Auteur : Corentin DESTREZ                                                        #
#==================================================================================#


CC = gcc
BUILD_FOLDER := build
exec = server client
lib = -lpthread
custom_lib= $(addprefix $(BUILD_FOLDER)/, tp6.o)

all : $(addprefix $(BUILD_FOLDER)/,$(exec))


server : $(BUILD_FOLDER)/server

client : $(BUILD_FOLDER)/client

$(BUILD_FOLDER)/server : server.c $(BUILD_FOLDER)/tp6.a
	$(CC) $^ -o $@

$(BUILD_FOLDER)/client : client.c $(BUILD_FOLDER)/tp6.a
	$(CC) $^ -o $@

$(BUILD_FOLDER)/tp6.a : $(custom_lib)
	ar rcs $@ $^

$(BUILD_FOLDER)/tp6.o : tp6.c tp6.h
	$(CC) -c -o $@ $<

clean :
	rm $(BUILD_FOLDER)/*
