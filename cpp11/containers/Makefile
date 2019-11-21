CXXFLAGS=-std=c++11 -g -O0 -Wall -pthread

TARGET=containers

$(TARGET): $(TARGET).cpp

.PHONY test:
test: $(TARGET)
	./$<

.PHONY clean:
	rm -rf $(TARGET)
