CXXFLAGS=-std=c++11 -g -O0 -Wall

TARGET := move_semantics
$(TARGET): $(TARGET).cpp

.PHONY test:
test: $(TARGET)
	./$<

.PHONY clean:
	rm -rf $(TARGET)
