# Компилятор и флаги
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# SFML флаги (если установлен)
SFML_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system

SRC_FILES := config.cpp controller.cpp game_objects.cpp main.cpp model.cpp tview.cpp view.cpp sfml_view.cpp

OBJ_FILES := $(patsubst %.cpp,obj/%.o,$(SRC_FILES))


TARGET := snake

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(SXXFLAGS) -o $@ $^ $(SFML_FLAGS)

obj/%.o: %.cpp | obj
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj:
	mkdir -p obj

clean:
	rm -rf obj $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
