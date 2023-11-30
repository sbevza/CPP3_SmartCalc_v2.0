CC= gcc
CFLAGS= -Wall -Wextra -Werror
STANDART= -std=c++17
TESTFLAGS= -lgtest -lgtest_main -lstdc++ -lm
TESTFILES= tests/*.cc model/model*.cc

OS = $(shell uname)

ifeq ($(OS), Darwin)
LEAKS = leaks --atExit -- test -fsanitize=address
OPEN = open report/index.html
LCOV = 	lcov -t "test" -o test.info -c -d . --no-external --ignore-errors mismatch > /dev/null 2>&1
else
LEAKS = CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
OPEN = xdg-open ./report/index.html
LCOV = 	lcov -t "test" -o test.info -c -d . --no-external 
endif

all: install

install:
	mkdir -p build
	qmake6 -o build/Makefile ./SmartCalc.pro
	cd build && make && make clean && rm Makefile && rm .qmake.stash

uninstall:
	rm -rf build/

tests: clean
	$(CC) $(CFLAGS) $(STANDART) $(TESTFILES) -o test $(TESTFLAGS)
	./test

gcov_report: clean
	$(CC) $(CFLAGS) --coverage $(STANDART) $(TESTFILES) -o test $(TESTFLAGS)  
	./test
	$(LCOV)	
	genhtml -o report test.info
	$(OPEN)

clang:
	find . -type f \( -name '*.h' -o -name '*.cc' \) -print0 | xargs -0 clang-format -n -style=Google

leaks: tests
	$(LEAKS)	

clean:
	rm -rf *.out *.o s21_matrix_oop.a *.gcda *.gcno *.info test
	rm -rf report

dvi:
	open readme.txt

valgrind: clean tests
	valgrind --leak-check=summary ./test  >> val_result.log 2>&1
