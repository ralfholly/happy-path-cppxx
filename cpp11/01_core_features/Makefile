CXXFLAGS=-std=c++11 -g -O0 -Wall

core_features: core_features.cpp

.PHONY test:
test: core_features
	./$<

.PHONY clean:
	find -type f -executable -delete
