all: bin/calc
	@echo "Finished Successfully"
	
bin/calc: obj/main.o libs/libiarith.a libs/liberrhandler.a
	gcc -obin/calc -I include obj/main.o -L libs -liarith -lerrhandler

obj/main.o: src/main.c include/calc.h include/error_handler.h
	gcc -o $@ -c -I include $<

obj/add_sub.o: src/add_sub.c include/calc.h
	gcc -o $@ -c -I include $<

obj/mul_div.o: src/mul_div.c include/calc.h include/error_handler.h
	gcc -o $@ -c -I include $<

obj/error_handler.o: src/error_handler.c include/error_handler.h
	gcc -o $@ -c -I include $<
	
libs/libiarith.a: obj/add_sub.o obj/mul_div.o include/calc.h include/error_handler.h
	ar rcs $@ $^

libs/liberrhandler.a: obj/error_handler.o
	ar rcs $@ $^
