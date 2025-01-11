Aκολουθούν οι κανόνες μεταγλώτισσης του προγράμματος μας!
  #Compliler
CC = gcc
 #Compiler flags
CFLAGS = Wall - Wextra -std=c99 -pedantic
 #Souce Files
SRC = kwdikas.c
 #Output
OUT = e_shop
 #Rules
all: $(OUT)
$(OUT): $(SRC)
  $(CC) $(CFLAGS) -o $(OUT) $(SRC)

#Clean files

  clean: 
       rm -f $(OUT)

#Run

 run: $(OUT)
   ./$(OUT)

#Rebuild

 rebuild: clean all
