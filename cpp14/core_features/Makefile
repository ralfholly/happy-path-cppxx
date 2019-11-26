CXXFLAGS=-std=c++14 -pedantic -g -O0 -Wall

TARGET = core_features

$(TARGET): $(TARGET).cpp

.PHONY test:
test: $(TARGET)
	./$<

.PHONY clean:
	rm -rf $(TARGET)
