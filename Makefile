eec: main.c
	gcc -o ./target/eec main.c ./reasings.h -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run: eec
	./target/eec
