SOURCES := hello.cpp
main hello.cpp:
	g++ $^ -o $@

format:
	clang-format ${SOURCES} -i --style=Google

verify-format:
	clang-format ${SOURCES} --dry-run --Werror --style=Google
