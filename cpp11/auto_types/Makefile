CXXFLAGS=-std=c++11 -pedantic -g -O0 -Wall -pthread

TARGET=auto_types

$(TARGET): $(TARGET).cpp

.PHONY test:
test: $(TARGET)
	./$<

.PHONY clean:
	rm -rf $(TARGET)
