all: run clean

run:
	g++ -fopenmp main.cpp -o tsp.out 
	./tsp.out

clean:
	rm -f *.bin *.txt *.blif *.out *~

.PHONY: all clean