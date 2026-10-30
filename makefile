todo: main.o editor.o texto.o linea.o diccionario.o
	g++ -Wall -o main main.o editor.o texto.o linea.o diccionario.o
main.o: main.cpp
	g++ -Wall -c main.cpp
editor.o: editor.h editor.cpp
	g++ -Wall -c editor.cpp
texto.o: texto.h texto.cpp
	g++ -Wall -c texto.cpp
linea.o: linea.h linea.cpp
	g++ -Wall -c linea.cpp
diccionario.o: diccionario.h diccionario.cpp
	g++ -Wall -c diccionario.cpp

# se deben agregar aca las reglas de compilacion para los modulos que agreguen
# agregar tambien las dependencias en la regla todo:
clean:
	rm -f main
	rm -f *.o

