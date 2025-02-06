CC = g++
CPPFLAGS = -Wall -g -std=c++11
LINKER = $(CC) -o
TARGET = interpreter
SRCS = $(shell find * -type f -name "*.cpp")

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CPPFLAGS) $(SRCS) -o $(TARGET)

%.o: %.cpp
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(TARGET) *.o
