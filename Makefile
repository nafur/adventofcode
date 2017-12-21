all: main_2017 main_2016

main_2017: main_2017.cpp $(wildcard 2017/*.h) $(wildcard utils/*.h)
	g++ -g -O3 -std=c++17 -o $@ $<
main_2016: main_2016.cpp $(wildcard 2016/*.h) $(wildcard utils/*.h)
	g++ -g -O3 -std=c++17 -o $@ $<

tidy: main_2017.cpp
	clang-tidy -checks='*' $< -- -std=c++17

clean:
	rm -f main_2017 main_2016
