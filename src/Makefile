CC= gcc
CFLAGS= -Wall -Wextra -Werror -I/usr/include/x86_64-linux-gnu/qt6
STANDART= -std=c++17
TESTFLAGS= -lgtest -lgtest_main -lstdc++ -lm -lQtCore -lQtWidgets -I/usr/include/x86_64-linux-gnu/qt6
TESTFILES= tests/*.cc model/model*.cc

OS = $(shell uname)

ifeq ($(OS), Darwin)
OPEN = open report/index.html
LCOV = 	lcov -t "test" -o test.info -c -d . --no-external --ignore-errors mismatch > /dev/null 2>&1
else
OPEN = xdg-open ./report/index.html
LCOV = 	lcov -t "test" -o test.info -c -d . --no-external 
endif

all: install

test_cmake:
	mkdir -p build
	cd build && cmake ../..
	cd build && make

tests: clean uninstall test_cmake
	build/CPP3_SmartCalc_v2_0_1
	rm -rf build/

install:
	mkdir -p build
	qmake6 -o build/Makefile ./SmartCalc.pro
	cd build && make && make clean && rm Makefile && rm .qmake.stash

uninstall:
	rm -rf build/

gcov_report: clean uninstall test_cmake
	cd build && ls && cp CPP3_SmartCalc_v2_0_1 ../test
	cd ..
	./test
	$(LCOV)
	genhtml -o report test.info
	$(OPEN)
	rm -rf build/

clang:
	find . -type f \( -name '*.h' -o -name '*.cc' \) -print0 | xargs -0 clang-format -n -style=Google

clean:
	rm -rf *.out *.o s21_matrix_oop.a *.gcda *.gcno *.info test
	rm -rf report

dvi:
	open readme.txt

valgrind: clean uninstall test_cmake
	cd build && ls && cp CPP3_SmartCalc_v2_0_1 ../test
	cd ..
	valgrind --leak-check=full ./test  >> val_result.log 2>&1
	rm -rf build/

dist:
	tar -czf smartcalc_v2-0.tar.gz Makefile readme.txt SmartCalc.pro main.cc controller/* model/* tests/* view/*
