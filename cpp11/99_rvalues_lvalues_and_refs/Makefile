CXXFLAGS=-std=c++11 -g -O0 -Wall

TARGET := rvalues_lvalues_and_refs
$(TARGET): $(TARGET).cpp

.PHONY test:
test: $(TARGET)
	./$<

.PHONY clean:
	rm -rf $(TARGET)
