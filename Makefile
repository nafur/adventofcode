main_2017: main_2017.cpp $(wildcard 2017/*.h)
	clang++ -std=c++17 -o $@ $<

tidy: main_2017.cpp
	clang-tidy -checks='*' $< -- -std=c++17

clean:
	rm -f main_2017
