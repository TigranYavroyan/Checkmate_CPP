CXX = g++

SRCS = *.cpp

TARGET = do

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET) && ./$(TARGET)

clean:
	rm -f $(TARGET)
