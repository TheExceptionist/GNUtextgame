exe_name = renegades
objects = main.o util.o hero.o move.o power.o attack_type.o status.o attribute.o console.o filesystem.o party.o menu.o title_menu.o 
compiler = g++
flags = 
.SUFFIXES: .o .cpp
.cpp.o:
	$(compiler) $(flags) -c $<

$(exe_name) : $(objects)
	g++ -o $(exe_name) $(objects)
	rm *.o
