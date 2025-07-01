hollow: 
	gcc -std=c99 program/main.c program/Escenario.c program/Mapa.c program/Tokens.c program/Ejercito.c program/Enemigo.c program/Rafaga.c program/Bala.c program/Puntuacion.c program/Particulas.c program/Animacion.c program/Pantalla.c program/Colisiones.c -Wall -lm -lSDL2 -o "Hollow Knight"

object: mk main.o Escenario.o Mapa.o Tokens.o Ejercito.o Enemigo.o Rafaga.o Bala.o Puntuacion.o Particulas.o Animacion.o Pantalla.o Colisiones.o
	gcc -std=c99 obj/main.o obj/Escenario.o obj/Mapa.o obj/Tokens.o obj/Ejercito.o obj/Enemigo.o obj/Rafaga.o obj/Bala.o obj/Puntuacion.o obj/Particulas.o obj/Animacion.o obj/Pantalla.o obj/Colisiones.o -Wall -lm -lSDL2 -o "Hollow Knight"
	
main.o :
	gcc -Wall -g -std=c99 -c program/main.c -o obj/main.o
Escenario.o :
	gcc -Wall -g -std=c99 -c program/Escenario.c -o obj/Escenario.o
Mapa.o :
	gcc -Wall -g -std=c99 -c program/Mapa.c -o obj/Mapa.o
Tokens.o :
	gcc -Wall -g -std=c99 -c program/Tokens.c -o obj/Tokens.o
Ejercito.o :
	gcc -Wall -g -std=c99 -c program/Ejercito.c -o obj/Ejercito.o
Enemigo.o :
	gcc -Wall -g -std=c99 -c program/Enemigo.c -o obj/Enemigo.o
Rafaga.o :
	gcc -Wall -g -std=c99 -c program/Rafaga.c -o obj/Rafaga.o
Bala.o :
	gcc -Wall -g -std=c99 -c program/Bala.c -o obj/Bala.o
Puntuacion.o :
	gcc -Wall -g -std=c99 -c program/Puntuacion.c -o obj/Puntuacion.o
Particulas.o :
	gcc -Wall -g -std=c99 -c program/Particulas.c -o obj/Particulas.o
Animacion.o :
	gcc -Wall -g -std=c99 -c program/Animacion.c -o obj/Animacion.o
Pantalla.o :
	gcc -Wall -g -std=c99 -c program/Pantalla.c -o obj/Pantalla.o
Colisiones.o :
	gcc -Wall -g -std=c99 -c program/Colisiones.c -o obj/Colisiones.o


mk:
	mkdir obj
