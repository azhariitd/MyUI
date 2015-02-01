main: src/main.cpp Rect StackPanel IBase Slider
	g++ -Wall -g bin/IBase bin/Rect bin/StackPanel bin/Slider  src/main.cpp -lGL -lglut -o bin/main

Slider: IBase src/Slider.cpp src/Slider.h
	g++ -Wall -c -g src/Slider.cpp -o bin/Slider


Rect: IBase src/Rect.cpp src/Rect.h
	g++ -Wall -c -g src/Rect.cpp -o bin/Rect

StackPanel: IBase src/StackPanel.cpp src/StackPanel.h
	g++ -Wall -c -g src/StackPanel.cpp -o bin/StackPanel

IBase: src/IBase.cpp src/IBase.h
	g++ -Wall -c -g src/IBase.cpp -o bin/IBase
