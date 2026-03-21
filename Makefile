CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = app

all: $(TARGET)

$(TARGET): main.cpp alixpress.cpp
	$(CXX) $(CXXFLAGS) main.cpp alixpress.cpp -o $(TARGET)

clean:
	rm -f $(TARGET) *.bin

run: $(TARGET)
	./$(TARGET)

run_with_db: $(TARGET)
	./$(TARGET) mydatabase.bin
