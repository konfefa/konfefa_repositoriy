all:
	gcc main.c alixpress.c -o app

clean:
	rm -f app db.bin

run:
	./app
