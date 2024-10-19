
all:

create: 
	mkdir -p build
	echo "Create"
	cmake . -B build/ -D CMAKE_BUILD_TYPE=Debug

s21_matrix_oop.a: create
	make -C build/ s21_matrix_oop

run: clean create
	make -C build/ s21_matrix
	./build/s21_matrix

test: clean create
	cmake  --build build --target matrix_test -j 9
	./build/matrix_test

style: clean
	find . -type f -name "*.cc" -o -name "*.h" | xargs clang-format --Werror --style=Google -n

clean:
	rm -rf build/ 