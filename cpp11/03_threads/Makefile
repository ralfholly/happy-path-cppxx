CXXFLAGS=-std=c++11 -g -O0 -Wall -pthread

TARGET=threads

$(TARGET): $(TARGET).cpp

.PHONY test:
test: $(TARGET)
	./$<

.PHONY clean:
	find -type f -executable -delete
