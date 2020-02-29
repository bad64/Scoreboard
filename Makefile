scoredeck:
	@if not exist "bin\" mkdir bin
	g++ main.cpp -lmingw32 -lSDL2main -lSDL2 -o bin/scoredeck.exe
