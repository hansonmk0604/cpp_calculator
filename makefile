run.exe: calculator.cpp
	g++ -o calculator calculator.cpp

clean: calculator.exe
	del calculator.exe