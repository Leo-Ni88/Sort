CURR_DIR := $(shell pwd)
SRC_DIR := $(CURR_DIR)

SRC:=$(wildcard $(SRC_DIR)/*.c)
OBJ:=$(patsubst ./%.c, ./%.o, $(SRC)) 

CFLAGS+= -I$(CURR_DIR)/../include

sort: $(OBJ) 
	cc $(CFLAGS) -o $@ $^ 
	mv sort ../

#$(OBJ): %.o: %.c %.h
#	cc -c $(CFLAGS) $< -o $(OBJ)

#main.0:
#	cc -c $(CFLAGS) -o $@ $<

#sortfun.o:
#	cc -c $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -rf $(obj)
	rm -rf ../sort
