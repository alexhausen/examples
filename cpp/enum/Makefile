CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		Enums.o

LIBS =

TARGET =	Enums

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
