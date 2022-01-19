#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "defendiendo_torres.h"
#include "animos.h"
#include "utiles.h"


#define MAX_ENANOS 25
#define MAX_ELFOS 25
#define MAX_ENEMIGOS 500
#define MAX_LETRAS 10

//CAMINOS Y TORRES
static const int DIMENSION_NIVEL_1_2 = 15;
static const int DIMENSION_NIVEL_3_4 = 20;
const int CAMINO_1 = 1;
const int CAMINO_2 = 2;
const int RESISTENCIA_PERDIDA_POR_DEFENSOR = 50;

const int COL_ENTRADA_NIVEL_1 = 14;
const int COL_TORRE_NIVEL_1 = 0;

const int COL_ENTRADA_NIVEL_2 = 0;
const int COL_TORRE_NIVEL_2 = 14;

const int FIL_ENTRADA_1_NIVEL_3 = 0;
const int FIL_ENTRADA_2_NIVEL_3 = 0;
const int FIL_TORRE_1_NIVEL_3 = 19;
const int FIL_TORRE_2_NIVEL_3 = 19;

const int FIL_ENTRADA_1_NIVEL_4 = 19;
const int FIL_ENTRADA_2_NIVEL_4 = 19;
const int FIL_TORRE_1_NIVEL_4 = 0;
const int FIL_TORRE_2_NIVEL_4 = 0;

//PERSONAJES
static const char ENANO = 'G';
static const char ELFO = 'L';
static const int FUERZA_ATAQUE_ENANO = 60;
static const int FUERZA_ATAQUE_ELFO = 30;
static const int VIDA_MINIMA_ORCO = 1;
static const int ORCOS_NIVEL_1 = 100;
static const int ORCOS_NIVEL_2 = 200;
static const int ORCOS_NIVEL_3 = 300;
static const int ORCOS_NIVEL_4 = 500;
const int VIDA_BASE_ORCO = 200; 
const int ELFOS_UNIDADES_NUEVAS = 10;
const int ENANOS_UNIDADES_NUEVAS = 10;
const int MAX_UNIDADES_NUEVAS = 20;
const int CANT_DEFENSORES_NIVEL_1_2 = 5;
const int CANT_DEFENSORES_NIVEL_3 = 6;
const int CANT_DEFENSORES_NIVEL_4 = 8;

//JUEGO 
const char SI = 'S';
const char NO = 'N';
const int JUGANDO = 0;
const int GANO = 1 ;
const int JUGANDO_NIVEL = 0;
const int MUERTOS_MIN_PEDIR_ALIADO = 5;
const int RESETEAR_MUERTOS = 0;
const float SEGUNDOS = 2;
static const int NIVEL_UNO = 1;
static const int NIVEL_DOS = 2;
static const int NIVEL_TRES = 3;
static const int NIVEL_CUATRO = 4;

//COLORES
#define VERDE_CLARO "\033[1m\33[32m"
#define ROJO_F "\x1b[41m"
#define FIN "\033[0m"
 



//POSTCONDICION = iniciará el juego con su respectivo texto.

void introduccion_general(){
	printf(VERDE_CLARO"							-----------------------------------------\n");
	printf("							BIENVENIDO A DEFENDIENDO TORRES (PARTE 2) \n");
	printf("							-----------------------------------------\n" );
	detener_el_tiempo(SEGUNDOS);
	printf("		La comarca necesita tu ayuda para poder repeler a las hordas de orcos! Las diferentes batallas serán\n				lideradas por Gimli y Legolas. La batalla se decidirá por vos...\n" FIN);
	detener_el_tiempo(SEGUNDOS);
}	

//PRECONDICION = Los datos obtenidos de animos.c deben ser correctos.
//POSTCONDICION = Mostrarà las estadisticas principales del juego.

void introduccion_uno(juego_t juego){

	printf("	DATOS OBTENIDOS:\n        ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯ \n\n        × CRITICO DE GIMLI: %i%% \n     	× FALLO DE GIMLI: %i%%\n     	× CRITICO DE LEGOLAS: %i%% \n     	× FALLO DE LEGOLAS: %i%% \n\n\n", juego.critico_gimli, juego.fallo_gimli, juego.critico_legolas, juego.fallo_legolas);
	detener_el_tiempo(SEGUNDOS);
	printf(VERDE_CLARO "Mi lord, en esta primer batalla debe posicionar 5 enanos. El mapa estará dado como un 15x15 y solamente debe darme valores que verifiquen: \n 	ø El nùmero debe estar entre 0 y 14.\n 	ø No debe posicionarse dentro del camino \n 	ø No debe existir otro enano en la misma posicion.\n   Empecemos Señor...\n\n" FIN);
	detener_el_tiempo(SEGUNDOS);

}

void introduccion_dos(){
	printf(VERDE_CLARO "\nBienvenido al nivel 2! Esta batalla serà liderada por usted y por Legolas. Debera posicionar elfos cumpliendo las mismas condiciones que el primer nivel. Comencemos!\n\n" FIN);
	detener_el_tiempo(SEGUNDOS);
}

void introduccion_tres(){
	printf(VERDE_CLARO "Bienvenido al nivel 3 mi señor. En esta ocación los enemigos vendrán de la parte norte hacia las dos torres. Deberá posicionar en primer lugar tres enanos, y por ultimo tres elfos. \n" FIN);
	detener_el_tiempo(SEGUNDOS);
}
void introduccion_cuatro(){
	printf(VERDE_CLARO "Has llegado al nivel final, lo felicito mi Lord, pero la batalla aún no termina. Esta última horda estará compuesta por 500 orcos y solamente tendrá a disposiciòn inicial 8 defensores \n" FIN);
}

//PRECONDICION = Recibira el juego Y las posiciones de las entradas y torres validas.
//POSTCONDICION = Creará un camino aleatorio uniendo las entradas y las torres correspondientes..

void construir_camino(juego_t *juego, coordenada_t entrada_1, coordenada_t torre_1, coordenada_t entrada_2, coordenada_t torre_2 ){

	if(juego->nivel_actual == NIVEL_UNO){
		obtener_camino(juego->nivel.camino_1, &(juego->nivel.tope_camino_1), entrada_1, torre_1);	

	} else if (juego->nivel_actual == NIVEL_DOS){
		obtener_camino(juego->nivel.camino_2, &(juego->nivel.tope_camino_2), entrada_2, torre_2);

	} else if(juego->nivel_actual == NIVEL_TRES || juego->nivel_actual == NIVEL_CUATRO){ 
		obtener_camino(juego->nivel.camino_1, &(juego->nivel.tope_camino_1), entrada_1, torre_1);
		obtener_camino(juego->nivel.camino_2, &(juego->nivel.tope_camino_2), entrada_2, torre_2);
	}	

}


//PRECONDICION = Recibira el juego con sus estrucuturas validas.
//POSTCONDICION = Inicializara a los defensores con SU TIPO y DAÑO.

void inicializar_defensores(juego_t * juego){

		if (juego->nivel_actual == NIVEL_UNO){
		juego->nivel.tope_defensores = CANT_DEFENSORES_NIVEL_1_2;
		for(int i = 0; i < juego->nivel.tope_defensores; i++){
			juego->nivel.defensores[i].tipo = ENANO;
		}
	} else if (juego->nivel_actual == NIVEL_DOS){
		juego->nivel.tope_defensores = CANT_DEFENSORES_NIVEL_1_2;
		for(int i = 0; i < juego->nivel.tope_defensores; i++){
			juego->nivel.defensores[i].tipo = ELFO;
		}
	} else if (juego->nivel_actual == NIVEL_TRES){
		juego->nivel.tope_defensores = CANT_DEFENSORES_NIVEL_3;
		for(int i = 0; i < 3; i++){
			juego->nivel.defensores[i].tipo = ENANO;
			juego->nivel.defensores[i+3].tipo = ELFO;
		}
	} else if (juego->nivel_actual == NIVEL_CUATRO){
		juego->nivel.tope_defensores = CANT_DEFENSORES_NIVEL_4;
		for(int i = 0; i < 4; i++){
			juego->nivel.defensores[i].tipo = ENANO;
			juego->nivel.defensores[i+4].tipo = ELFO;
		}
	}
	for(int i = 0; i < juego->nivel.tope_defensores; i++){
		juego->nivel.defensores[i].posicion.fil = -10;
		juego->nivel.defensores[i].posicion.col = -10;
		if(juego->nivel.defensores[i].tipo == ENANO){
			juego->nivel.defensores[i].fuerza_ataque = FUERZA_ATAQUE_ENANO;
		} else if(juego->nivel.defensores[i].tipo == ELFO){
			juego->nivel.defensores[i].fuerza_ataque = FUERZA_ATAQUE_ELFO;
		}
	}

}

//PRECONDICION = Recibira la posicion donde se quiere ubicar al defensor.
//POSTCONDICION = Decidira si es posible la colocacion del defensor.

bool posicion_invalida(juego_t juego, int fil_actual, int col_actual, int defensores_posicionados){

	int tope;
	bool lugar_ocupado = false;

	if(juego.nivel_actual == NIVEL_UNO || juego.nivel_actual == NIVEL_DOS){
		tope = DIMENSION_NIVEL_1_2;
	} else {
		tope = DIMENSION_NIVEL_3_4;
	}
	if((fil_actual < 1)  || (col_actual < 1) || (fil_actual > tope) || (col_actual > tope)) {
		lugar_ocupado = true;	
	} 

	if(juego.nivel_actual == NIVEL_UNO){
		for (int i = 0; i < juego.nivel.tope_camino_1; i++){
			if(juego.nivel.camino_1[i].fil == fil_actual-1 && juego.nivel.camino_1[i].col == col_actual-1){
				lugar_ocupado = true;
			}
		}	
	} else if(juego.nivel_actual == NIVEL_DOS){
		for (int i = 0; i < juego.nivel.tope_camino_2; i++){
			if(juego.nivel.camino_2[i].fil == fil_actual-1 && juego.nivel.camino_2[i].col == col_actual-1){
				lugar_ocupado = true;
			}
		}
	} else if(juego.nivel_actual == NIVEL_TRES || juego.nivel_actual == NIVEL_CUATRO){
		for (int i = 0; i < juego.nivel.tope_camino_1; i++){
			if(juego.nivel.camino_1[i].fil == fil_actual-1 && juego.nivel.camino_1[i].col == col_actual-1){
				lugar_ocupado = true;
			}
		}
		for (int i = 0; i < juego.nivel.tope_camino_2; i++){
			if(juego.nivel.camino_2[i].fil == fil_actual-1 && juego.nivel.camino_2[i].col == col_actual-1){
				lugar_ocupado = true;
			}
		}
	} 
	
	for (int i = 0; i < (defensores_posicionados); i++){
		if(juego.nivel.defensores[i].posicion.fil == fil_actual-1 && juego.nivel.defensores[i].posicion.col == col_actual-1){
					lugar_ocupado = true;
		}
	}
	return lugar_ocupado;
}
//PRECONDICION = Recibira una estructura valida .
//POSTCONDICION = Ubicará a los defensores dependiendo el nivel.

void ver_tipo_defensor(char tipo_defensor[MAX_LETRAS], char tipo){
	if(tipo == ENANO){
	strcpy(tipo_defensor, "enano");	
	} else{
		strcpy(tipo_defensor, "elfo");
	}
	
}



void posicionar_defensores(juego_t * juego){

	inicializar_defensores(juego);
	mostrar_juego(*juego);
	int defensores_posicionados = 0;
	char tipo_defensor[MAX_LETRAS]; 
	for(int i = 0; i < (juego->nivel.tope_defensores); i++){
		ver_tipo_defensor(tipo_defensor, juego->nivel.defensores[i].tipo);
		printf("Fila de posicion para defensor Nª%i de tipo %s: ", i+1, tipo_defensor);
		scanf("%i", &(juego->nivel.defensores[i].posicion.fil));
		printf("Columna de posicion para defensor Nª%i de tipo %s: ", i+1, tipo_defensor);
		scanf("%i", &(juego->nivel.defensores[i].posicion.col));
		while(posicion_invalida(*juego, (juego->nivel.defensores[i].posicion.fil), (juego->nivel.defensores[i].posicion.col), defensores_posicionados) == true){
			printf("POSICION INCORRECTA MI LORD! Por favor repita la Fila de posicion para el defensor: ");
			scanf("%i", &(juego->nivel.defensores[i].posicion.fil));
			printf(" Y ahora repitamos la Columna para el defensor: ");
			scanf("%i", &(juego->nivel.defensores[i].posicion.col));
		}
		(juego->nivel.defensores[i].posicion.fil)--;
		(juego->nivel.defensores[i].posicion.col)--;

		defensores_posicionados++;
		mostrar_juego(*juego);
	}

}

//PRECONDICION = Recibira una estructura valida .
//POSTCONDICION = Iniciará el tope maximo de enemigos y la vida de cada uno.

void inicializar_orcos(juego_t * juego){ 

	if (juego->nivel_actual == NIVEL_UNO){
		juego->nivel.max_enemigos_nivel = ORCOS_NIVEL_1;

	} else if (juego->nivel_actual == NIVEL_DOS){
		juego->nivel.max_enemigos_nivel = ORCOS_NIVEL_2;

	} else if (juego->nivel_actual == NIVEL_TRES){
		juego->nivel.max_enemigos_nivel = ORCOS_NIVEL_3;

	} else if (juego->nivel_actual == NIVEL_CUATRO){
		juego->nivel.max_enemigos_nivel = ORCOS_NIVEL_4;

	}
	for(int i = 0; i < juego->nivel.max_enemigos_nivel; i++){
		juego->nivel.enemigos[i].vida = VIDA_BASE_ORCO + (rand ()%101);
	}
	juego->nivel.tope_enemigos = 0;

}

//PRECONDICION = Recibira el juego con sus estrucuturas validas.
//POSTCONDICION = Devolvera la cantidad de muertos que existen hasta ese momento.
int contador_muertos(nivel_t nivel){

	int contador = 0;
	for(int i = 0; i < nivel.tope_enemigos; i++){
		if(nivel.enemigos[i].vida < VIDA_MINIMA_ORCO){
			contador++;
		}
	}

	return contador;	
}
//POSTCONDICION = Decidirá si se quiere agregar un defensor.

void preguntar_defensor_nuevo_nivel_3_4(bool *quiere_agregar, int enanos_extra, int elfos_extra){

	char decision;
	printf("Quiere agregar un defensor nuevo? va a poder solamente %i en todo el juego! Le quedan %i enanos y %i elfos. (SI = S) (NO = N):", MAX_UNIDADES_NUEVAS, enanos_extra, elfos_extra);
	scanf(" %c", &decision);
	if(decision == NO){
		*quiere_agregar = false;
	} else if( decision == SI){
		*quiere_agregar = true; 
	} else{
		*quiere_agregar = false;
	}
	
}

void preguntar_defensor_nuevo_nivel_2(bool *quiere_agregar, int elfos_extra){

	char decision;
	printf("Quiere agregar un elfo nuevo? va a poder solamente %i en todo el juego y le quedan %i! OJO (SI = S) (NO = N):", ELFOS_UNIDADES_NUEVAS, elfos_extra);
	scanf(" %c", &decision);
	if(decision == NO){
		*quiere_agregar = false;
	} else if( decision == SI){
		*quiere_agregar = true; 
	} else{
		*quiere_agregar = false;
	}
	
}

void preguntar_defensor_nuevo(bool *quiere_agregar, int enanos_extra){

	char decision;
	printf("Quiere agregar un enano nuevo? va a poder solamente %i en todo el juego y le quedan %i! OJO (SI = S) (NO = N):", ENANOS_UNIDADES_NUEVAS, enanos_extra);
	scanf(" %c", &decision);
	if(decision == NO){
		*quiere_agregar = false;
	} else if( decision == SI){
		*quiere_agregar = true; 
	} else{
		*quiere_agregar = false;
	}
	
}


//PRECONDICION = Recibirà un nivel con las dimensiones correspondientes, ademas, en un estado debido.
//POSTCONDICION = Se ubicara a los defensores en la posicion elegida por el usuario.

void pedir_coordenadas(nivel_t * nivel){

	printf("Digame la fila donde lo quiere agregar: \n");
	scanf(" %i", &(nivel->defensores[nivel->tope_defensores].posicion.fil));
	printf("Digame la Columna donde lo quiere agregar:\n");
	scanf(" %i", &(nivel->defensores[nivel->tope_defensores].posicion.col));
	(nivel->defensores[nivel->tope_defensores].posicion.col)--;
	(nivel->defensores[nivel->tope_defensores].posicion.fil)--;
}


//PRECONDICION = Recibirá el juego con la capacidad de agregar un defensor.
//POSTCONDICION = Se decidira que tipo de defensor quiere, ELFO o ENANO.

char decidir_tipo_defensor(juego_t * juego){

	printf("Què tipo de defensor quiere señor? (ENANO = G, ELFO = L) \n");
	scanf(" %c", &(juego->nivel.defensores[juego->nivel.tope_defensores].tipo));
	return (juego->nivel.defensores[juego->nivel.tope_defensores].tipo);

}

bool pide_defensor(int turnos){

	if ((turnos != 25) && (turnos != 50) && (turnos != 75) && (turnos != 100) && (turnos != 125) && (turnos != 150) && (turnos != 175) && (turnos != 200) && (turnos != 225)){
		return false;
	}
	return true;
}

//PRECONDICION = Recibira una estructura valida con  el nivel ya inicializado.
//POSTCONDICION = Jugarà el nivel.
void realizar_turno(juego_t *juego, int *muertos, int *turnos){

			jugar_turno(juego);
			mostrar_juego(*juego);
		
			
			*muertos = contador_muertos(juego->nivel);
			(*turnos)++;
			printf("MUERTOS TOTALES = %i\n", *muertos);
			printf("TURNO Nª%i\n", *turnos);
			detener_el_tiempo(0.5);


}

//PRECONDICION = Recibira una estructura valida con  el nivel ya inicializado.
//POSTCONDICION = Jugarà el nivel.

void jugar_nivel_uno(juego_t *juego, int *muertos, int *turnos){
	
	bool quiere_agregar;	
		if((*turnos != 25 && *turnos != 50 && *turnos != 75)){
			realizar_turno(juego, muertos, turnos);
			
		} else{
			preguntar_defensor_nuevo(&quiere_agregar, juego->torres.enanos_extra);
			if (quiere_agregar == true  && juego->torres.enanos_extra > 0 ){

				printf("MUERTOS TOTALES = %i\n", *muertos);
				printf("TURNO Nª%i", *turnos);
				do{
					pedir_coordenadas(&(juego->nivel));
				}
				while(agregar_defensor(&(juego->nivel),juego->nivel.defensores[juego->nivel.tope_defensores].posicion, ENANO) == -1);
				
				juego->torres.enanos_extra--;
				juego->torres.resistencia_torre_1 -= RESISTENCIA_PERDIDA_POR_DEFENSOR;
			}

			(*turnos)++;
		}
}

//PRECONDICION = Recibira una estructura valida con  el nivel ya inicializado.
//POSTCONDICION = Jugarà el nivel.

void jugar_nivel_dos(juego_t * juego, int * muertos, int *turnos){
	bool quiere_agregar;	

		printf("MUERTOS TOTALES = %i\n", *muertos);
		if(pide_defensor(*turnos) == false){
			realizar_turno(juego, muertos, turnos);

		} else{
			preguntar_defensor_nuevo_nivel_2(&quiere_agregar, juego->torres.elfos_extra);
			if (quiere_agregar == true && (juego->torres.elfos_extra > 0)){
				do{
					pedir_coordenadas(&(juego->nivel));
				}
				while(agregar_defensor(&(juego->nivel),juego->nivel.defensores[juego->nivel.tope_defensores].posicion, ELFO) == -1);
				*muertos = RESETEAR_MUERTOS;
				if(juego->nivel.defensores[juego->nivel.tope_defensores].tipo == ENANO){
					juego->torres.enanos_extra--;
					juego->torres.resistencia_torre_1 -= RESISTENCIA_PERDIDA_POR_DEFENSOR;
				} else {
					juego->torres.elfos_extra--;
					juego->torres.resistencia_torre_2 -= RESISTENCIA_PERDIDA_POR_DEFENSOR;
				}
				
			}
			(*turnos)++;
		}

}

//PRECONDICION = Recibira una estructura valida con  el nivel ya inicializado.
//POSTCONDICION = Jugarà el nivel.


void jugar_nivel_tres_cuatro(juego_t * juego, int * muertos, int *turnos ){
	bool quiere_agregar;		
	char nuevo_defensor;

		printf("MUERTOS TOTALES = %i\n", *muertos);
		if(pide_defensor(*turnos) == false){ 
			realizar_turno(juego, muertos, turnos);

		} else{
			preguntar_defensor_nuevo_nivel_3_4(&quiere_agregar, juego->torres.enanos_extra, juego->torres.elfos_extra);
			if (quiere_agregar == true && (juego->torres.elfos_extra > 0 || juego->torres.enanos_extra > 0)){
				nuevo_defensor = decidir_tipo_defensor(juego);
				do{
				 pedir_coordenadas(&(juego->nivel));
				}
				while(agregar_defensor(&(juego->nivel),juego->nivel.defensores[juego->nivel.tope_defensores].posicion, nuevo_defensor) == -1);
				*muertos = RESETEAR_MUERTOS;
				if(juego->nivel.defensores[juego->nivel.tope_defensores].tipo == ENANO){
					juego->torres.enanos_extra--;
					juego->torres.resistencia_torre_1 -= RESISTENCIA_PERDIDA_POR_DEFENSOR;
				} else {
					juego->torres.elfos_extra--;
					juego->torres.resistencia_torre_2 -= RESISTENCIA_PERDIDA_POR_DEFENSOR;
				}
				
			}
			(*turnos)++;
		}


}
//PRECONDICION = Recibira una estructura valida.
//POSTCONDICION = Ubica a las entradas y a las torres.

void entrada_torre(juego_t juego, coordenada_t *entrada_1, coordenada_t *torre_1, coordenada_t *entrada_2, coordenada_t *torre_2){

	if(juego.nivel_actual == NIVEL_UNO){

		entrada_1->fil = rand()%DIMENSION_NIVEL_1_2;
		entrada_1->col = COL_ENTRADA_NIVEL_1;
		torre_1->fil = rand()%DIMENSION_NIVEL_1_2;
		torre_1->col = COL_TORRE_NIVEL_1;

	} else if(juego.nivel_actual == NIVEL_DOS){
		
		entrada_2->fil = rand()%DIMENSION_NIVEL_1_2;
		entrada_2->col = COL_ENTRADA_NIVEL_2;
		torre_2->fil = rand()%DIMENSION_NIVEL_1_2;
		torre_2->col = COL_TORRE_NIVEL_2;

	} else if(juego.nivel_actual == NIVEL_TRES){	

		entrada_1->fil = FIL_ENTRADA_1_NIVEL_3;
		entrada_1->col = rand()%DIMENSION_NIVEL_3_4;
		torre_1->fil = FIL_TORRE_1_NIVEL_3; 
		torre_1->col = rand()%DIMENSION_NIVEL_3_4;
		entrada_2->fil = FIL_ENTRADA_2_NIVEL_3;
		entrada_2->col = rand()%DIMENSION_NIVEL_3_4;
		torre_2->fil = FIL_TORRE_2_NIVEL_3;
		torre_2->col = rand()%DIMENSION_NIVEL_3_4;

	} else if(juego.nivel_actual == NIVEL_CUATRO){

		entrada_1->fil = FIL_ENTRADA_1_NIVEL_4;
		entrada_1->col = rand()%DIMENSION_NIVEL_3_4;
		torre_1->fil = FIL_TORRE_1_NIVEL_4;
		torre_1->col = rand()%DIMENSION_NIVEL_3_4;
		entrada_2->fil = FIL_ENTRADA_2_NIVEL_4;
		entrada_2->col = rand()%DIMENSION_NIVEL_3_4;
		torre_2->fil = FIL_TORRE_2_NIVEL_4;
		torre_2->col = rand()%DIMENSION_NIVEL_3_4;
	}
}


//PRECONDICION = Recibira una estructura valida con coordenadas dentro del rango permitido.
//POSTCONDICION = Dejarà el nivel listo para ser jugado.
void inicializar_nivel(juego_t* juego, coordenada_t* entrada_1, coordenada_t* torre_1, coordenada_t* entrada_2, coordenada_t* torre_2, int *muertos, int *turnos){

	if(juego->nivel_actual == NIVEL_UNO){
		introduccion_uno(*juego);
	} else if(juego->nivel_actual == NIVEL_DOS){
		introduccion_dos();
	} else if(juego->nivel_actual == NIVEL_TRES){
		introduccion_tres();
	} else if(juego->nivel_actual == NIVEL_CUATRO){
		introduccion_cuatro();
	}

	entrada_torre(*juego, entrada_1, torre_1, entrada_2, torre_2);
	construir_camino(juego, *entrada_1, *torre_1, *entrada_2, *torre_2);
	inicializar_orcos(juego);
	posicionar_defensores(juego);
	mostrar_juego(*juego);
	*muertos = 0;
	*turnos = 1;

}

void verificar_si_gano(juego_t juego){
	if(estado_juego(juego) == GANO){
		printf("FELICITACIONES! Ganaste :)\n");
	} else {
		printf("Perdiste :(\n");
	}
}


int main(){
	srand((unsigned)time(NULL));
	int viento = 25;
	int humedad = 25;
	char gimli_humor = 'B';
	char legolas_humor = 'B';
	juego_t juego;
	coordenada_t entrada_1;
	coordenada_t torre_1;
	coordenada_t entrada_2;
	coordenada_t torre_2;
	bool nivel_1_inicializado = false;
	bool nivel_2_inicializado = false;
	bool nivel_3_inicializado = false;
	bool nivel_4_inicializado = false;
	animos(&viento, &humedad, &gimli_humor, &legolas_humor);
	introduccion_general();
	juego.nivel_actual = NIVEL_UNO;
	inicializar_juego(&juego, viento, humedad, legolas_humor, gimli_humor);
	int muertos = 0;
	int turnos = 1;
	while(estado_juego(juego) == JUGANDO){ 
		if(nivel_1_inicializado == false){
			inicializar_nivel(&juego, &entrada_1, &torre_1, &entrada_2, &torre_2, &muertos, &turnos);	
			nivel_1_inicializado = true;
		}
		if(estado_nivel(juego.nivel) == JUGANDO_NIVEL && juego.nivel_actual == NIVEL_UNO){ 
			jugar_nivel_uno(&juego, &muertos, &turnos);
		} else {
			
			if(nivel_2_inicializado == false){
				juego.nivel_actual = NIVEL_DOS;
				inicializar_nivel(&juego, &entrada_1, &torre_1, &entrada_2, &torre_2, &muertos, &turnos);	
				nivel_2_inicializado = true;
			}
			if(estado_nivel(juego.nivel) == JUGANDO_NIVEL && juego.nivel_actual == NIVEL_DOS){
				jugar_nivel_dos(&juego, &muertos, &turnos);
			} else {
				
				if(nivel_3_inicializado == false){
					juego.nivel_actual = NIVEL_TRES;
					inicializar_nivel(&juego, &entrada_1, &torre_1, &entrada_2, &torre_2, &muertos, &turnos);	
					nivel_3_inicializado = true;
				}
				if(estado_nivel(juego.nivel) == JUGANDO_NIVEL && juego.nivel_actual == NIVEL_TRES){
					jugar_nivel_tres_cuatro(&juego, &muertos, &turnos);	
				} else {
					
					if(nivel_4_inicializado == false){
						juego.nivel_actual = NIVEL_CUATRO;
						inicializar_nivel(&juego, &entrada_1, &torre_1, &entrada_2, &torre_2, &muertos, &turnos);	
						nivel_4_inicializado = true;
					}
					if(estado_nivel(juego.nivel) == JUGANDO_NIVEL && juego.nivel_actual == NIVEL_CUATRO){
						jugar_nivel_tres_cuatro(&juego, &muertos, &turnos);
					} 
				}
		 	}
		}
	} 
	verificar_si_gano(juego);
	return 0;
}