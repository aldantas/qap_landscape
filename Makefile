main_src = src/metropolis_hastings.cpp src/features_extractor.cpp
main_obj = $(main_src:.cpp=.o)

other_src = src/common.cpp src/best_improv.cpp src/writer.cpp src/printer.cpp src/reader.cpp src/fitness_distance_correlation.cpp src/accumulated_escape_probability.cpp src/negative_slope_coefficient.cpp
other_obj = $(other_src:.cpp=.o)

CFLAGS = -Wall -Wextra -g

all: mh ft

ft: src/features_extractor.o $(other_obj)
	mkdir -p bin
	g++ $(CFLAGS) $^ -o bin/$@

mh: src/metropolis_hastings.o $(other_obj)
	mkdir -p bin
	g++ $(CFLAGS) $^ -o bin/$@

.PHONY: clean
clean:
	rm -rf $(main_obj) $(other_obj) ./bin
