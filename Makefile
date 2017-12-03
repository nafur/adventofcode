SRCS=$(wildcard **/*.h)

main: main.cpp ${SRCS}
	clang++ -std=c++17 -o $@ $<

tidy: main.cpp
	clang-tidy -checks='*' $< -- -std=c++17

clean:
	rm -f main
