all: link

link: compile
	echo "Linking"
	g++ -o bin/simulation bin/main.o bin/Action.o bin/Auxiliary.o bin/Facility.o bin/Plan.o bin/SelectionPolicy.o bin/Settelment.o bin/Simulation.o

compile:
	@echo "Compiling"
	g++ -g -c -Wall -Weffc++ -std=c++11 -Iinclude -o bin/Auxiliary.o src/Auxiliary.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11 -Iinclude -o bin/Facility.o src/Facility.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11 -Iinclude -o bin/SelectionPolicy.o src/SelectionPolicy.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11 -Iinclude -o bin/Settelment.o src/Settelment.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11 -Iinclude -o bin/Plan.o src/Plan.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11 -Iinclude -o bin/Simulation.o src/Simulation.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11 -Iinclude -o bin/Action.o src/Action.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11 -Iinclude -o bin/main.o src/main.cpp


clean:
	@echo "Cleaning"
	rm -rf bin/*
