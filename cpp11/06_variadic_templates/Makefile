CXXFLAGS=-std=c++11 -g -O0 -Wall

TARGET := variadic_templates
$(TARGET): $(TARGET).cpp

.PHONY test:
test: $(TARGET)
	./$<

.PHONY clean:
	rm -rf $(TARGET)
