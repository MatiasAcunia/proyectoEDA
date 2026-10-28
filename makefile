todo: main.o editor.o texto.o linea.o diccionario.o
	gcc -Wall -o main main.o editor.o
main.o: main.cpp
	gcc -Wall -c main.cpp
editor.o: editor.h editor.cpp
	gcc -Wall -c editor.cpp
texto.o: texto.h texto.cpp
	gcc -Wall -c texto.cpp
linea.o: linea.h linea.cpp
	gcc -Wall -c linea.cpp
diccionario.o: diccionario.h diccionario.cpp
	gcc -Wall -c diccionario.cpp

# se deben agregar aca las reglas de compilacion para los modulos que agreguen
# agregar tambien las dependencias en la regla todo:
clean:
	rm -f main
	rm -f *.o

