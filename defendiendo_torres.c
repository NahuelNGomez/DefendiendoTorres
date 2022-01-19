#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "defendiendo_torres.h"
#define MAX_TERRENO 25
#define MAX_ENANOS 25
#define MAX_ELFOS 25

//ANIMOS
const char ANIMO_MALO = 'M';
const char ANIMO_REGULAR = 'R';
const char ANIMO_BUENO = 'B';
const int CRITICO_REGULAR = 10;
const int CRITICO_BUENO = 25;

//PERSONAJES
static const char ENANO = 'G';
static const char ELFO = 'L';
static const char ORCO = 'O';
static const int FUERZA_ATAQUE_ENANO = 60;
static const int FUERZA_CRITICO_ENANO = 100;
static const int FUERZA_ATAQUE_ELFO = 30;
static const int FUERZA_CRITICO_ELFO = 70;
static const int VIDA_MINIMA_ORCO = 1;
const int NO_HAY_CRITICO = 0;

//CAMINOS Y TORRES
const int CAMINO_UNO = 1;
const int CAMINO_DOS = 2;
const int TORRE_RESISTENCIA_INICIAL = 600;
const int UNIDADES_EXTRA_INICIAL = 10;
const int PRIMERA_POSICION_CAMINO = 0;
static const int VIDA_MINIMA_TORRE = 1;
static const int DIMENSION_NIVEL_1_2 = 15;
static const int DIMENSION_NIVEL_3_4 = 20;

//JUEGO
static const int NIVEL_UNO = 1;
static const int NIVEL_DOS = 2;
static const int NIVEL_TRES = 3;
static const int NIVEL_CUATRO = 4;
const int DOBLE = 2;
const int PERDIDO = -1;
static const int JUGANDO = 0;
const int GANADO = 1;
const int POS_POSIBLE = 0;
const int POS_INCORRECTA = -1;
const int MIN_DIST_MANHATTAN = 3;

//COLORES
#define ROJO_CLARO "\033[1m\33[31m"
#define MAGENTA "\033[1m\33[35m"
#define AMARILLO "\033[1m\33[33m"
#define AZUL "\033[1m\33[34m"
#define VERDE_CLARO "\033[1m\33[32m"
#define MARRON "\033[0m\33[33m"
#define FIN "\033[0m"
#define SILVER "\033[0m\33[37m"

//PRECONDICION = Recibirá la ubicacion de la torre dentro de la estructura.
//POSTCONDICION = Se pondran los puntos de vida y la unidades extra en cada torre.

void	inicializar_torres(torres_t* torres){

		torres->resistencia_torre_1 = TORRE_RESISTENCIA_INICIAL;
		torres->resistencia_torre_2 = TORRE_RESISTENCIA_INICIAL;
		torres->enanos_extra = UNIDADES_EXTRA_INICIAL;
		torres->elfos_extra = UNIDADES_EXTRA_INICIAL;

}

//PRECONDICION = Recibirá el ánimo válido de Gimli, además del juego con una estructura válida.
//POSTCONDICION = Se pondran los criticos de cada los enanos en la estructura del juego.

void inicializar_critico_enanos(juego_t*juego, char animo_gimli){

		if(animo_gimli == ANIMO_MALO){
			juego->critico_gimli = NO_HAY_CRITICO;	
		} else if(animo_gimli == ANIMO_REGULAR){
			juego->critico_gimli = CRITICO_REGULAR;
		} else if (animo_gimli == ANIMO_BUENO){
			juego->critico_gimli = CRITICO_BUENO;
		}
}


//PRECONDICION = Recibirá el ánimo válido de Legolas, además del juego con una estructura válida.
//POSTCONDICION = Se pondran los criticos de cada los enanos en la estructura del juego.

void inicializar_critico_elfos(juego_t*juego, char animo_legolas){

	if(animo_legolas == ANIMO_MALO){
		juego->critico_legolas = NO_HAY_CRITICO;	
	} else if(animo_legolas == ANIMO_REGULAR){
		juego->critico_legolas = CRITICO_REGULAR;
	} else if (animo_legolas == ANIMO_BUENO){
		juego->critico_legolas = CRITICO_BUENO;
	}
}

//PRECONDICION = Recibirá los ánimos válidos de cada lider (Legolas y Gimli), además del juego con una estructura válida.
//POSTCONDICION = Se pondran los criticos de cada personaje en la estructura del juego.

void	inicializar_critico(juego_t*juego, char animo_legolas, char animo_gimli){

		inicializar_critico_enanos(juego, animo_gimli);
		inicializar_critico_elfos(juego, animo_legolas);

}
//PRECONDICION = Recibirá el juego con una estructura válida, ademas informacion sobre el viento y la humedad validos.
//POSTCONDICION = Se ubicaran la probabilidad de criticos de cada los personajes dentro de la estructura del juego.

void	inicializar_fallo(juego_t* juego, int viento, int humedad){

		juego->fallo_legolas = viento/DOBLE;
		juego->fallo_gimli = humedad/DOBLE;
}

void inicializar_juego(juego_t* juego, int viento, int humedad, char animo_legolas, char animo_gimli){

	inicializar_torres(&(juego->torres));  
	inicializar_critico(juego, animo_legolas, animo_gimli);
	inicializar_fallo(juego, viento, humedad);
	juego->nivel_actual = NIVEL_UNO;

}

void graficar_columnas(int tope){
		for(int i = 0; i < tope; i++){
		if ( i == 0){
			printf("         %i", i+1);
		} else if(i == tope-1){
			printf(" %i\n", i+1);
		} else if( i > 8){
			printf(" %i", i+1);
		} else {
			printf("  %i", i+1);
		}
	}
	if(tope == 15){
		printf("      ┌──────────────────────────────────────────────┐\n");	
	} else {
		printf("      ┌─────────────────────────────────────────────────────────────┐\n");
	}
	
}


void inicializar_mapa(int tope, nivel_t nivel, char terreno[MAX_TERRENO][MAX_TERRENO], int nivel_actual){

	for(int i = 0; i < tope; i++){
		for(int j = 0; j < tope; j++){
			terreno[i][j] = '*';
		}
	}

	if(nivel_actual == NIVEL_UNO){
		for(int i = 0; i < nivel.tope_camino_1; i++){
			terreno[nivel.camino_1[i].fil][nivel.camino_1[i].col] = '_';
		}	
	} else if(nivel_actual == NIVEL_DOS){
		for(int i = 0; i < nivel.tope_camino_2; i++){
			terreno[nivel.camino_2[i].fil][nivel.camino_2[i].col] = '-';
		}	
	} else if(nivel_actual == NIVEL_TRES || nivel_actual == NIVEL_CUATRO){
		for(int i = 0; i < nivel.tope_camino_1; i++){
			terreno[nivel.camino_1[i].fil][nivel.camino_1[i].col] = '_';
		}
		for(int i = 0; i < nivel.tope_camino_2; i++){
			terreno[nivel.camino_2[i].fil][nivel.camino_2[i].col] = '-';
		}	
	}
}

void mostrar_defensores(nivel_t nivel, char terreno[MAX_TERRENO][MAX_TERRENO]){

	for(int i = 0; i < nivel.tope_defensores; i++){
		if(nivel.defensores[i].tipo == ENANO){

		terreno[nivel.defensores[i].posicion.fil][nivel.defensores[i].posicion.col] = ENANO;
		} else if(nivel.defensores[i].tipo == ELFO){
			terreno[nivel.defensores[i].posicion.fil][nivel.defensores[i].posicion.col] = ELFO;
		}
		
	}


}

void orco_segundo_camino(int pos_orco, int pos_camino, int vida_orco, char terreno[MAX_TERRENO][MAX_TERRENO], juego_t juego){
		if((pos_camino == pos_orco) && vida_orco >= VIDA_MINIMA_ORCO){
		terreno[juego.nivel.camino_2[pos_camino].fil][juego.nivel.camino_2[pos_camino].col] = ORCO;
	}
}

void orco_primer_camino(int pos_orco, int pos_camino, int vida_orco, char terreno[MAX_TERRENO][MAX_TERRENO], juego_t juego){
	if((pos_camino == pos_orco) && vida_orco >= VIDA_MINIMA_ORCO){
		terreno[juego.nivel.camino_1[pos_camino].fil][juego.nivel.camino_1[pos_camino].col] = ORCO;
	}
}
void graficar_borde_inferior(int tope){
	if(tope == DIMENSION_NIVEL_1_2 ){
		printf("      └──────────────────────────────────────────────┘\n");	
	} else {
		printf("      └─────────────────────────────────────────────────────────────┘\n");
	}
	
}

void mostrar_juego(juego_t juego){

	system("clear");

	char terreno[MAX_TERRENO][MAX_TERRENO];
	int tope;
	if(juego.nivel_actual == NIVEL_UNO || juego.nivel_actual == NIVEL_DOS){
		tope = DIMENSION_NIVEL_1_2;
	} else {
		tope = DIMENSION_NIVEL_3_4;
	}

	graficar_columnas(tope);
	inicializar_mapa(tope, juego.nivel, terreno, juego.nivel_actual);
	mostrar_defensores(juego.nivel, terreno);


	if(juego.nivel_actual == NIVEL_UNO){
		for(int i = 0; i < juego.nivel.tope_camino_1-1; i++){
		 	for(int j = 0; j < juego.nivel.tope_enemigos; j++){
				orco_primer_camino(juego.nivel.enemigos[j].pos_en_camino, i, juego.nivel.enemigos[j].vida, terreno, juego);
		 	}
		}	
	} else if(juego.nivel_actual == NIVEL_DOS){
		for(int i = 0; i < juego.nivel.tope_camino_2-1; i++){
	 		for(int j = 0; j < juego.nivel.tope_enemigos; j++){
	 			if(juego.nivel.enemigos[j].camino == CAMINO_DOS){
	 				orco_segundo_camino(juego.nivel.enemigos[j].pos_en_camino, i, juego.nivel.enemigos[j].vida, terreno, juego);
	 			} 
	 		}
		}	
	} else if(juego.nivel_actual == NIVEL_TRES || juego.nivel_actual == NIVEL_CUATRO){
		for(int i = 0; i < juego.nivel.tope_camino_1-1; i++){
	 		for(int j = 0; j < juego.nivel.tope_enemigos; j++){ 
	 			if(juego.nivel.enemigos[j].camino == CAMINO_UNO){
				 orco_primer_camino(juego.nivel.enemigos[j].pos_en_camino, i, juego.nivel.enemigos[j].vida, terreno, juego);
	 			}
	 		}
		}
		for(int i = 0; i < juego.nivel.tope_camino_2-1; i++){
	 		for(int j = 0; j < juego.nivel.tope_enemigos; j++){ 
	 			if(juego.nivel.enemigos[j].camino == CAMINO_DOS){
			 		orco_segundo_camino(juego.nivel.enemigos[j].pos_en_camino, i, juego.nivel.enemigos[j].vida, terreno, juego);
				}
	 		}
	 	}
			
	}		


	if(juego.nivel_actual ==NIVEL_UNO){
	terreno[juego.nivel.camino_1[juego.nivel.tope_camino_1-1].fil][juego.nivel.camino_1[juego.nivel.tope_camino_1-1].col] = 'T';	
	terreno[juego.nivel.camino_1[0].fil][juego.nivel.camino_1[0].col] = 'E';
		for(int i = 0; i < tope; i++){
			if( i < 9){
				printf(" %i    │", i+1);	
			} else {
				printf(" %i   │", i+1);
			}
			for(int j = 0; j < tope; j++){
				if(terreno[i][j] == '_'){
					printf(ROJO_CLARO "  %c" FIN, terreno[i][j]);	
				}else if(terreno[i][j] == '-'){
					printf(SILVER "  %c" FIN, terreno[i][j]);
				} else if(terreno[i][j] == '*'){
					printf(VERDE_CLARO "  %c" FIN, terreno[i][j]);
				}else if ((terreno[i][j] == ORCO)){
					printf(MARRON "  %c" FIN, terreno[i][j]);
				} else{
					printf("  %c", terreno[i][j]);
				} if( j == tope-1){
					printf(" │");
				}
			}if(i == tope-1){
				printf(" VIDA DE TORRE = %i\n", juego.torres.resistencia_torre_1); 
			} else{
				printf("\n");
			}
		}
	

	} else if(juego.nivel_actual == NIVEL_DOS){
		terreno[juego.nivel.camino_2[juego.nivel.tope_camino_2-1].fil][juego.nivel.camino_2[juego.nivel.tope_camino_2-1].col] = 'T';
		
		terreno[juego.nivel.camino_2[0].fil][juego.nivel.camino_2[0].col] = 'E';
			for(int i = 0; i < tope; i++){
				if( i < 9){
					printf(" %i    │", i+1);	
				} else {
					printf(" %i   │", i+1);
				}
				for(int j = 0; j < tope; j++){
					if(terreno[i][j] == '_'){
						printf(ROJO_CLARO "  %c" FIN, terreno[i][j]);	
					}else if(terreno[i][j] == '-'){
						printf(SILVER "  %c" FIN, terreno[i][j]);
					} else if(terreno[i][j] == '*'){
					printf(VERDE_CLARO "  %c" FIN, terreno[i][j]);
					} else if(terreno[i][j] == ORCO){
					printf(MARRON "  %c" FIN, terreno[i][j]);
					} else{
						printf("  %c", terreno[i][j]);
					} if( j == tope-1){
						printf(" │");
					}			
				}if(i == tope-1){
					printf(" VIDA DE TORRE = %i\n", juego.torres.resistencia_torre_2);		
				} else {
					printf("\n");
				}
				
		}

	} 	 else if(juego.nivel_actual == NIVEL_TRES || juego.nivel_actual == NIVEL_CUATRO){
		terreno[juego.nivel.camino_1[juego.nivel.tope_camino_1-1].fil][juego.nivel.camino_1[juego.nivel.tope_camino_1-1].col] = 'T';	
		terreno[juego.nivel.camino_2[juego.nivel.tope_camino_2-1].fil][juego.nivel.camino_2[juego.nivel.tope_camino_2-1].col] = 'T';
		terreno[juego.nivel.camino_1[0].fil][juego.nivel.camino_1[0].col] = 'E';
		terreno[juego.nivel.camino_2[0].fil][juego.nivel.camino_2[0].col] = 'E';
		
			for(int i = 0; i < tope; i++){
				if( i < 9){
					printf(" %i    │", i+1);	
				} else {
					printf(" %i   │", i+1);
				}
				for(int j = 0; j < tope; j++){
					if(terreno[i][j] == '_'){
						printf(ROJO_CLARO "  %c" FIN, terreno[i][j]);	
					}else if(terreno[i][j] == '-'){
						printf(SILVER "  %c" FIN, terreno[i][j]);
					} else if(terreno[i][j] == '*'){
					printf(VERDE_CLARO "  %c" FIN, terreno[i][j]);
					} else if(terreno[i][j] == ORCO){
					printf(MARRON "  %c" FIN, terreno[i][j]);
					} else{
						printf("  %c", terreno[i][j]);
					} if( j == tope-1){
						printf(" │");
					}			
				}if(i == tope-1){
					printf(" VIDA DE TORRE_2 = %i\n", juego.torres.resistencia_torre_2);		
				} else if(i == tope-2){
					printf(" VIDA DE TORRE_1 = %i\n", juego.torres.resistencia_torre_1);
					
				} else{
					printf("\n");
				}

			}

		}

	graficar_borde_inferior(tope);


}



void inicializar_bool_enanos(bool enano_ataco[MAX_ENANOS], int tope){
	for(int i = 0; i < tope; i++){
		enano_ataco[i] = false;
	}
}

//PRECONDICION = Recibira una posicion del enano y del enemigo.
//POSTCONDICION = Verificara si esta en rango.

bool enemigo_en_rango(coordenada_t posicion_enano, coordenada_t posicion_orco){
	if((posicion_enano.fil)+1 == posicion_orco.fil || posicion_orco.fil == (posicion_enano.fil) || posicion_orco.fil == (posicion_enano.fil)-1){
		if(posicion_enano.col+1 == posicion_orco.col || posicion_orco.col == (posicion_enano.col) || posicion_orco.col == (posicion_enano.col)-1){

			return true;
		}
	}
	return false;
}



void danio_enano(juego_t * juego, int enemigo, int defensor, bool enano_ataco[MAX_ENANOS]){
	int numero_aleatorio;
	numero_aleatorio = rand()%100;

	if(numero_aleatorio >= juego->fallo_gimli){
		 numero_aleatorio = rand()%100;
		 if(numero_aleatorio < juego->critico_gimli){
	 		juego->nivel.enemigos[enemigo].vida -=FUERZA_CRITICO_ENANO;
		 	printf("CRITICO\n");
			enano_ataco[defensor] = true;
		 } else{
		 	juego->nivel.enemigos[enemigo].vida -=FUERZA_ATAQUE_ENANO;
		 	printf("NORMAL\n");
			enano_ataco[defensor] = true;
		 }
	}
	enano_ataco[defensor] = true;
}

//PRECONDICION = Recibira una estructura valida .
//POSTCONDICION = Los enanos haran su ataque dependiendo si estan en rango de algun enemigo.

void ataque_enano(juego_t *juego){
	bool enano_ataco[MAX_ENANOS];
	inicializar_bool_enanos(enano_ataco, juego->nivel.tope_defensores);
	for(int i = 0; i < juego->nivel.tope_defensores; i++){ 
		if(juego->nivel.defensores[i].tipo == ENANO){
			for(int j = 0; j < juego->nivel.tope_enemigos; j++){ 
				if(juego->nivel.enemigos[j].vida >= VIDA_MINIMA_ORCO && (enano_ataco[i] != true)){
					 for(int k = 0; k < juego->nivel.tope_camino_1; k++){
							if((k == juego->nivel.enemigos[j].pos_en_camino) ){
								if(juego->nivel.enemigos[j].camino == CAMINO_UNO){
									if(enemigo_en_rango(juego->nivel.defensores[i].posicion, juego->nivel.camino_1[k]) == true){
										danio_enano(juego, j, i, enano_ataco);
									}
										
								}
								
							}
						}
					for(int k = 0; k < juego->nivel.tope_camino_2; k++){
						if(juego->nivel.enemigos[j].camino == CAMINO_DOS){
							if((k == juego->nivel.enemigos[j].pos_en_camino) && (enano_ataco[i] != true)){
								if(enemigo_en_rango(juego->nivel.defensores[i].posicion, juego->nivel.camino_2[k]) == true){
									danio_enano(juego, j, i, enano_ataco);
								}
							}
						}	
					}	
				}
			}
		}
	}
}		

//PRECONDICION = Recibira una posicion del elfo y del enemigo.
//POSTCONDICION = Verificara si esta en rango.

int distancia_manhattan(int fila_elfo, int col_elfo, int fila_orco, int col_orco){
	int distancia = 0;
	distancia = (abs((fila_elfo)-fila_orco)) + (abs((col_elfo)-col_orco));
	return distancia;
}

//PRECONDICION = Recibira una estructura valida.
//POSTCONDICION = Los elfos haran su ataque dependiendo si estan en rango de algun enemigo.



void danio_elfo(juego_t *juego, int enemigo){
	int numero_aleatorio;
	numero_aleatorio = rand()%100;

		if(numero_aleatorio >= juego->fallo_legolas){
			numero_aleatorio = rand()%100;
			if(numero_aleatorio < juego->critico_legolas){
				juego->nivel.enemigos[enemigo].vida -= FUERZA_CRITICO_ELFO;
				printf("CRITICO\n");

			} else {
				juego->nivel.enemigos[enemigo].vida -= FUERZA_ATAQUE_ELFO;
				printf("NORMAL\n");

			}
		}

}

void ataque_elfo(juego_t *juego){

	for(int i = 0; i < juego->nivel.tope_defensores; i++){
		if(juego->nivel.defensores[i].tipo == ELFO){
			for(int j = 0; j < juego->nivel.max_enemigos_nivel; j++){ 
				if(juego->nivel.enemigos[j].vida >= VIDA_MINIMA_ORCO){
					for(int k = 0; k < juego->nivel.tope_camino_1; k++){
					 	if(juego->nivel.enemigos[j].camino == CAMINO_UNO){
							if(k == juego->nivel.enemigos[j].pos_en_camino){
								if(distancia_manhattan(juego->nivel.defensores[i].posicion.fil,juego->nivel.defensores[i].posicion.col, juego->nivel.camino_1[k].fil, juego->nivel.camino_1[k].col) <= MIN_DIST_MANHATTAN){
									danio_elfo(juego, j);	
								}
							}
						}
					} 
					for(int k = 0; k < juego->nivel.tope_camino_2; k++){
						if(juego->nivel.enemigos[j].camino == CAMINO_DOS){
							if(k == juego->nivel.enemigos[j].pos_en_camino){
								if(distancia_manhattan(juego->nivel.defensores[i].posicion.fil,juego->nivel.defensores[i].posicion.col, juego->nivel.camino_2[k].fil, juego->nivel.camino_2[k].col) <= MIN_DIST_MANHATTAN){
									danio_elfo(juego, j);
								}
							}
						}
					}
				}
			}	
		}
	}	
}		

//PRECONDICION = Recibira el juego con sus estrucuturas validas.
//POSTCONDICION = Posicionara al enemigo en la primemra posicion del camino.

void primera_posicion_orco(juego_t * juego){
	if(juego->nivel_actual == NIVEL_UNO){
		juego->nivel.enemigos[juego->nivel.tope_enemigos].camino = CAMINO_UNO;
		juego->nivel.enemigos[juego->nivel.tope_enemigos].pos_en_camino = PRIMERA_POSICION_CAMINO;
		juego->nivel.enemigos[juego->nivel.tope_enemigos].vida = 200+ rand()%100;	
	} else if(juego->nivel_actual == NIVEL_DOS){
		juego->nivel.enemigos[juego->nivel.tope_enemigos].camino = CAMINO_DOS;
		juego->nivel.enemigos[juego->nivel.tope_enemigos].pos_en_camino = PRIMERA_POSICION_CAMINO;
		juego->nivel.enemigos[juego->nivel.tope_enemigos].vida = 200+ rand()%100;
	} else{
		juego->nivel.enemigos[juego->nivel.tope_enemigos].camino = CAMINO_UNO;
		juego->nivel.enemigos[juego->nivel.tope_enemigos].pos_en_camino = PRIMERA_POSICION_CAMINO;
		juego->nivel.enemigos[juego->nivel.tope_enemigos].vida = 200+ rand()%100;	
		juego->nivel.enemigos[juego->nivel.tope_enemigos+1].camino = CAMINO_DOS;
		juego->nivel.enemigos[juego->nivel.tope_enemigos+1].pos_en_camino = PRIMERA_POSICION_CAMINO;
		juego->nivel.enemigos[juego->nivel.tope_enemigos+1].vida = 200+ rand()%100;			
	}

	
}


//PRECONDICION = Recibe el juego con una estructura válida.
//POSTCONDICION = Avanza una casilla al orco, dependiendo si está vivo.


void mover_orcos_vivos(nivel_t *nivel, int posicion){
		if(nivel->enemigos[posicion].vida >= VIDA_MINIMA_ORCO){
					(nivel->enemigos[posicion].pos_en_camino)++;
				}
}

void movimiento_orcos(juego_t *juego){ 
	
	if(juego->nivel_actual == NIVEL_UNO || juego->nivel_actual == NIVEL_DOS){

		if(juego->nivel.tope_enemigos < juego->nivel.max_enemigos_nivel){ 
			primera_posicion_orco(juego);	
			juego->nivel.tope_enemigos++;

			for(int j = 0; j < juego->nivel.tope_enemigos-1; j++){ 
				mover_orcos_vivos(&(juego->nivel), j);
			}
		}
		if(juego->nivel.tope_enemigos == juego->nivel.max_enemigos_nivel){
			for(int j = 0; j < juego->nivel.tope_enemigos; j++){ 
				mover_orcos_vivos(&(juego->nivel), j);	
			}
		} 
	} else{

		if(juego->nivel.tope_enemigos < juego->nivel.max_enemigos_nivel){ 
			primera_posicion_orco(juego);
			juego->nivel.tope_enemigos++;
			juego->nivel.tope_enemigos++;
			
			for(int j = 0; j < juego->nivel.tope_enemigos-2; j++){
				mover_orcos_vivos(&(juego->nivel), j);
			}

		} else{
			for(int j = 0; j < juego->nivel.tope_enemigos; j++){ 
				mover_orcos_vivos(&(juego->nivel), j);		
			}	
		}
				
	}	
}	

//PRECONDICION = Recibirá la estructura del juego, con las posiciones de los orcos validas, dentro de cada camino.
//POSTCONDICION = Verificara si existe algun enemigo en el lugar de la torre y a partir de eso, verifica si la ataca.

void danio_torres(juego_t* juego){ 
	if(juego->nivel_actual == NIVEL_UNO){
		for(int i = 0; i < juego->nivel.tope_enemigos; i++){
			if(juego->nivel.enemigos[i].camino == CAMINO_UNO){	
				if(juego->nivel.enemigos[i].pos_en_camino == (juego->nivel.tope_camino_1)-1 ){
					juego->torres.resistencia_torre_1 -= juego->nivel.enemigos[i].vida;
					juego->nivel.enemigos[i].vida = 0;
				}
			}
		}
	} else if (juego->nivel_actual == NIVEL_DOS){
		for(int i = 0; i < juego->nivel.tope_enemigos; i++){
			if(juego->nivel.enemigos[i].camino == CAMINO_DOS){
				if(juego->nivel.enemigos[i].pos_en_camino == (juego->nivel.tope_camino_2)-1 ){
					juego->torres.resistencia_torre_2 -= juego->nivel.enemigos[i].vida;
					juego->nivel.enemigos[i].vida = 0;
				}			
			}
		}
	} else if (juego->nivel_actual == NIVEL_TRES || juego->nivel_actual == NIVEL_CUATRO){
		for(int i = 0; i < juego->nivel.tope_enemigos; i++){
			if(juego->nivel.enemigos[i].camino == CAMINO_UNO){
					if(juego->nivel.enemigos[i].pos_en_camino == ((juego->nivel.tope_camino_1)-1)){
						juego->torres.resistencia_torre_1 -= juego->nivel.enemigos[i].vida;
						juego->nivel.enemigos[i].vida = 0;
					}
			} else if(juego->nivel.enemigos[i].camino == CAMINO_DOS){
				if(juego->nivel.enemigos[i].pos_en_camino == (juego->nivel.tope_camino_2)-1 ){
					juego->torres.resistencia_torre_2 -= juego->nivel.enemigos[i].vida;
					juego->nivel.enemigos[i].vida = 0;
				}
			}
		}	
	}
}

void jugar_turno(juego_t *juego){ 

			if(juego->nivel.tope_enemigos != 0){
				ataque_enano(juego);
				ataque_elfo(juego);
				movimiento_orcos(juego);
				danio_torres(juego);
				printf("enemigos =%i\n", juego->nivel.tope_enemigos);	

			} else {
				if(juego->nivel_actual == NIVEL_UNO || juego->nivel_actual == NIVEL_DOS){
					primera_posicion_orco(juego);
					(juego->nivel.tope_enemigos)++;

				} else {
					primera_posicion_orco(juego);
					(juego->nivel.tope_enemigos)++;
					(juego->nivel.tope_enemigos)++;

				}
				
			}
}

bool gano(juego_t juego, int vivos){
	return (juego.nivel_actual == NIVEL_CUATRO) && (juego.torres.resistencia_torre_1 >= VIDA_MINIMA_TORRE) && (juego.torres.resistencia_torre_2 >= VIDA_MINIMA_TORRE) && (vivos < 1);

	
}

int estado_juego(juego_t juego){
	int vivos = 0;
	int estado = JUGANDO;
	for(int i = 0; i < juego.nivel.max_enemigos_nivel; i++){			
		if(juego.nivel.enemigos[i].vida >= VIDA_MINIMA_ORCO){
			vivos++;
		}
	}
	if(gano(juego, vivos) == true){
			estado = GANADO;
	}

	if(juego.torres.resistencia_torre_1 < VIDA_MINIMA_TORRE || juego.torres.resistencia_torre_2 < VIDA_MINIMA_TORRE){
		estado = PERDIDO;
	}

	return estado;
}

int estado_nivel(nivel_t nivel){
	int orcos_muertos = 0;
	bool empezo_nivel = false;

	for(int i = 0; i < nivel.max_enemigos_nivel; i++){
		if(nivel.enemigos[i].vida <= 0){
			orcos_muertos++;
			empezo_nivel = true;
		}
	}
	if(orcos_muertos == nivel.max_enemigos_nivel && empezo_nivel == true){
		return 1;
	} else {
		return 0;
	}
}


//PRECONDICION = Recibirá una posicion donde se quiere agregar al nuevo defensor.
//POSTCONDICION = Verificará si no existen defensores posicionados en el mismo lugar.. 

void verificar_lugar_ocupado(bool *lugar_ocupado, int fil_actual, int col_actual, nivel_t nivel){

	for (int i = 0; i < (nivel.tope_defensores); i++){
		if(nivel.defensores[i].posicion.fil == fil_actual && nivel.defensores[i].posicion.col == col_actual){
			*lugar_ocupado = true;
		}
	}

}

//PRECONDICION = Recibirá una posicion donde se quiere agregar al nuevo defensor
//POSTCONDICION = Verificará si es posible colocar al defensor en la posición solicitada. 

bool posicion_incorrecta(nivel_t nivel, int fil_actual, int col_actual){

	int cant_elfo = 0;
	int cant_enano = 0;
	bool lugar_ocupado = false;
	for(int i = 0; i < nivel.tope_defensores; i++){
		if(nivel.defensores[i].tipo == ELFO){
			cant_elfo++;
		} else if(nivel.defensores[i].tipo == ENANO){
			cant_enano++;
		}
	}

	if(cant_elfo == 0){ //ES NIVEL 1.
		for (int i = 0; i < nivel.tope_camino_1; i++){
			if(nivel.camino_1[i].fil == fil_actual && nivel.camino_1[i].col == col_actual){
				lugar_ocupado = true;
			}
		}

	} else if(cant_enano == 0){ // ES NIVEL 2.
		for (int i = 0; i < nivel.tope_camino_2; i++){
			if(nivel.camino_2[i].fil == fil_actual && nivel.camino_2[i].col == col_actual){
				lugar_ocupado = true;
			}
		}

	} else { // ES NIVEL 3 O 4.
		for (int i = 0; i < nivel.tope_camino_1; i++){
			if(nivel.camino_1[i].fil == fil_actual && nivel.camino_1[i].col == col_actual){
				lugar_ocupado = true;
			}
		}
		for (int i = 0; i < nivel.tope_camino_2; i++){
			if(nivel.camino_2[i].fil == fil_actual && nivel.camino_2[i].col == col_actual){
				lugar_ocupado = true;
			}
		}
	}
	verificar_lugar_ocupado(&lugar_ocupado, fil_actual, col_actual, nivel);
	
		return lugar_ocupado;
}

//PRECONDICION = Recibirá una posición válida para ubicar al defensor. 
//POSTCONDICION = Ubićará al defensor y le asignará una fuerza, dependiendo su tipo. 

void inicializar_defensor(nivel_t* nivel, coordenada_t posicion, char tipo){

		nivel->defensores[nivel->tope_defensores].posicion.fil = posicion.fil;
		nivel->defensores[nivel->tope_defensores].posicion.col = posicion.col;
		nivel->defensores[nivel->tope_defensores].tipo = tipo;
		if(tipo == ENANO){
			nivel->defensores[nivel->tope_defensores].fuerza_ataque = FUERZA_ATAQUE_ENANO;
		} else {
			nivel->defensores[nivel->tope_defensores].fuerza_ataque = FUERZA_ATAQUE_ELFO;
		}
		(nivel->tope_defensores)++;
}

int agregar_defensor(nivel_t* nivel, coordenada_t posicion, char tipo){
	int colocacion;
	if(posicion_incorrecta(*nivel, posicion.fil, posicion.col) == false){
		inicializar_defensor(nivel, posicion, tipo);
		colocacion = POS_POSIBLE;
	} else{
		colocacion = POS_INCORRECTA;
		printf("HOLA");
	}
	return colocacion;
}