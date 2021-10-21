CC = g++
CFLAGS  = -g -Wall
TARGET = closest
RM = rm

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)


