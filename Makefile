dot: 01-dot_avx.o 01-dot_non_avx.o 01-dot_main.o
	g++ -Wall -std=c++17 -O3 01-dot_avx.o 01-dot_non_avx.o 01-dot_main.o -o 01-dot.out

01-dot_non_avx.o: 01-dot_non_avx.cc
	g++ -Wall -std=c++17 -O3 -fPIC -c $< -o $@

%.o: %.cc
	g++ -Wall -std=c++17 -O3 -fPIC -mavx2 -mfma -c $< -o $@

clean:
	rm -rf *.o *.out