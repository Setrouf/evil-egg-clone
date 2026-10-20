2dshooter: main.c
	gcc -o ./target/2dshooter main.c ./reasings.h -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run: 2dshooter
	./target/2dshooter
