all: run clean

run:
	g++ -fopenmp main.cpp -o tsp.out 
	./tsp.out

runsec:
	g++ -fopenmp main.cpp -D sec -o tsp.out 
	./tsp.out

vivopar:
	python3 maps.py
	g++ -fopenmp live.cpp -o live.out
	./live.out

vivosec:
	python3 maps.py
	g++ live.cpp -D sec -o live.out
	./live.out
clean:
	rm -f *.out *~ *json

.PHONY: all clean