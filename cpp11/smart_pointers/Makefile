CXXFLAGS=-std=c++11 -g -O0 -Wall -pthread

TARGET=smart_pointers

$(TARGET): $(TARGET).cpp

.PHONY test:
test: $(TARGET)
	./$<

.PHONY clean:
	rm -rf $(TARGET)
