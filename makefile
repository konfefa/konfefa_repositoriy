all:
	gcc dz6.c alixpress.c -o app

clean:
	rm -f app *.bin

run:
	./app

run_with_db:
	./app mydatabase.bin

