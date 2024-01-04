_IGREEN=\033[42m
_WHITE=\033[1;37m
END=\033[0m
BGreen=\033[1;32m

exe: clem.o paul.o gabin.o etienne.o main.o
	gcc -g clem.o paul.o gabin.o etienne.o main.o -o exe
	@echo "${BGreen}[✔] TEST EXE PASSED${END}"

gabin.o: gabin.c gabin.h structure.h
	gcc -g -c gabin.c -o gabin.o -Wall
	@echo "${BGreen}[✔] TEST GABIN PASSED${END}"

etienne.o: etienne.c etienne.h structure.h
	gcc -g -c etienne.c -o etienne.o -Wall
	@echo "${BGreen}[✔] TEST ETIENNE PASSED${END}"
	
paul.o: paul.c paul.h structure.h
	gcc -g -c paul.c -o paul.o -Wall
	@echo "${BGreen}[✔] TEST PAUL PASSED${END}"

clem.o: clem.c clem.h structure.h
	gcc -g -c clem.c -o clem.o -Wall
	@echo "${BGreen}[✔] TEST CLEM PASSED${END}"

main.o: main.c paul.h gabin.h etienne.h clem.h structure.h
	gcc -g -c main.c -o main.o -Wall
	@echo "${BGreen}[✔] TEST MAIN PASSED${END}"

clean:
	rm -f *.o
