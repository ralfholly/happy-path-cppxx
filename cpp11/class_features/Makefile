CXXFLAGS=-std=c++11 -pedantic -g -O0 -Wall

TARGET = class_features

$(TARGET): $(TARGET).cpp

.PHONY test:
test: $(TARGET)
	./$<

.PHONY clean:
	rm -rf $(TARGET)

