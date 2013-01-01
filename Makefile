CC=g++
COFLAGS=-Wall -c -O3 -I/home/YiamiYo/SDL/include/
CEFLAGS=-Wall -static-libstdc++ -static-libgcc -mwindows
LDFLAGS=-L/home/YiamiYo/SDL/lib/x86/ -lmingw32 -lSDLmain -lSDL -lopengl32
SOURCES=main.cpp ball.cpp functions.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CEFLAGS) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(COFLAGS) $< -o $@

clean:
	@rm -f $(OBJECTS) $(EXECUTABLE)

run:
	@[ -f $(EXECUTABLE) ] && ./$(EXECUTABLE) || echo "Need to compile first."