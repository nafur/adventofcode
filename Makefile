SRCS=$(wildcard *.h)

main: main.cpp ${SRCS}
	clang++ -std=c++17 -o $@ $<

clean:
	rm -f main
