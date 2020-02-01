CPPUNIT_PATH=/usr/local
GCC = g++ -std=c++14 -g

TARGET = readSensorValueTest
SRCS   = readSensorValueTest.cpp readSensorValue.cpp
OBJS   = $(SRCS:.cpp=.o) main.o

all : $(TARGET)

$(TARGET): $(OBJS)
	$(GCC) -o $@ $(OBJS) -L${CPPUNIT_PATH}/lib -lstdc++ -lcppunit -ldl

main.o : main.cpp

include makefile.dep

%.o: %.cpp
	$(GCC) -c $*.cpp -I${CPPUNIT_PATH}/include

clean:
	-rm *.exe *.o $(TARGET)
