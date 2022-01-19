#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "defendiendo_torres.h"
#include "animos.h"
#include "utiles.h"

const int DIA_DEL_MES_MIN = 1;
const int DIA_DEL_MES_MAX = 30;

const char MANANA = 'M';
const char TARDE = 'T';
const char NOCHE = 'N';

const char PIE_DERECHO = 'D';
const char PIE_IZQUIERDO = 'I';
const char ENSALADA = 'E';
const char HAMBURGUESA = 'H';
const char PIZZA = 'P';
const char GUISO = 'G';

const int MAX_HORAS_DE_SUENO = 12;
const int MIN_HORAS_DE_SUENO = 0;

const int MIN_BUEN_HUMOR = 36;
const int MIN_REGULAR_HUMOR = 21;

const char BUEN_HUMOR = 'B';
const char REGULAR_HUMOR = 'R';
const char MAL_HUMOR = 'M';

#define VERDE_CLARO "\033[1m\33[32m"
#define AMARILLO "\033[1m\33[33m"
#define ROJO_CLARO "\033[1m\33[31m"
#define FIN "\033[0m"


void introduccion(){
	printf(VERDE_CLARO"							-------------------------------\n");
	printf("							BIENVENIDO A DEFENDIENDO TORRES \n");
	printf("							-------------------------------\n" );
	detener_el_tiempo(2);
	printf(AMARILLO "Señor, bienvenido al mundo de la tierra media. Para comenzar, le hare un par de preguntas para ir conociendonos... \n" FIN);
	detener_el_tiempo(3);


}

/*
Precondición: Un número entero
Postcondición: verifica que el numero se encuentra en los parametros establecidos.
*/
bool dia_del_mes(int dia){
	return (dia <= DIA_DEL_MES_MAX && dia>= DIA_DEL_MES_MIN);
}

/*
Precondición: Un caractér
Postcondición: Verifica si el caractér es igual a los pedidos.
*/
bool hora_del_dia(char hora){
	return (hora == MANANA || hora == TARDE || hora == NOCHE);
}

/*
Precondición: Un caractér
Postcondición: Verifica que el caractér sea igual a los pedidos. 
*/
bool pie(char pie){
	return (pie == PIE_IZQUIERDO || pie == PIE_DERECHO);
}

/*
Precondición: Un caractér
Postcondición: Verifica que el caractér esté entre los solicitados.
*/
bool cena(char cena){
	return (cena == ENSALADA || cena == HAMBURGUESA || cena == PIZZA || cena == GUISO);
}

/*
Precondición: un nùmero entero
Postcondición: verifica que el nùmero escaneado esté entre los parametros solicitados.
*/
bool horas_de_sueno(int horas_de_sueno){
	return (horas_de_sueno >= MIN_HORAS_DE_SUENO && horas_de_sueno<= MAX_HORAS_DE_SUENO);
}

/*
Precondición: Dirección de memoria
Postcondición: Introduce en la dirección de memoria el numero escaneado
*/
void preguntar_dia(int*dia){
	printf("Lo saludo cordialmente, el invierno se acerca y hay que estar listos a fines de este mes, junio. ¿Qué día del mes es señor? ");
	scanf(" %i", dia);
	while(dia_del_mes(*dia) == false){
		printf(ROJO_CLARO"señor, junio tiene 30 dias, por favor digame un número entre 1 y 30."FIN);
		scanf(" %i", dia);
	}
}
/*
Precondición: Dirección de memoria
Postcondición: Introduce en la dirección de memoria el caractér escaneado
*/
void preguntar_hora(char *hora){
	printf("Muchas gracias su alteza, ¿En qué hora del día exactamente?  (M = Mañana; T=Tarde; N=Noche) ");
	scanf(" %c", hora);
	while(hora_del_dia(*hora) == false){
		printf(ROJO_CLARO"M = Mañana, T=Tarde, N=Noche!!"FIN);
		scanf(" %c", hora);
		}
}

/*
Precondición: Direcciones de memoria correspondientes a Gimli
Postcondición: Introduce en las dirección de memoria lo propuesto por el usuario
*/
void info_legolas(char*pie_legolas, char*cena_legolas, int*horas_de_sueno_legolas){
	printf("Maravilloso, ahora necesito información del elfo Legolas. ¿Con qué pie se levantó? Derecho = D, izquierdo = I");
	scanf(" %c", pie_legolas);
	while(pie(*pie_legolas) == false){
		printf(ROJO_CLARO"D = Derecho, I=izquierdo!"FIN);
		scanf(" %c", pie_legolas);
	}
	printf("Se lo agradezco. Ahora digame lo que cenó. (ensalada (E), hamburguesa(H), pizza (P), guiso (G)) ");
	scanf(" %c", cena_legolas);
	while(cena(*cena_legolas) == false){
		printf(ROJO_CLARO"Escribe una incial! Ensalada (E), hamburguesa(H), pizza (P), guiso (G)!"FIN);
		scanf(" %c", cena_legolas);
	}
	printf("Por último, necesitaría saber las horas de sueño de Legolas (Entre 0 y 12 por favor)");
	scanf(" %i", horas_de_sueno_legolas);
	while(horas_de_sueno(*horas_de_sueno_legolas) == false){
		printf(ROJO_CLARO"un número entre 0 y 12 mi lord!"FIN);
		scanf(" %i", horas_de_sueno_legolas);
	}
}

/*
Precondición: Direcciones de memoria correspondientes a Gimli
Postcondición: Introduce en las dirección de memoria lo propuesto por el usuario
*/
void info_gimli(char*pie_gimli, char*cena_gimli, int*horas_de_sueno_gimli){
	printf("Ahora, necesito la misma información sobre el enano Gimli, ¿Con qué pie se levantó? Derecho = D, izquierdo = I");
	scanf(" %c", pie_gimli);
	while(pie(*pie_gimli) == false){
		printf(ROJO_CLARO"Escribir D(derecho) o I(izquierdo)!"FIN);
		scanf(" %c", pie_gimli);
	}
	printf("Se lo agradezco. Ahora digame lo que cenó el enano. (ensalada (E), hamburguesa(H), pizza (P), guiso (G)) ");
	scanf(" %c", cena_gimli);
	while(cena(*cena_gimli) == false){
		printf(ROJO_CLARO"Escribe una incial! Ensalada (E), hamburguesa(H), pizza (P), guiso (G)!"FIN);
		scanf(" %c", cena_gimli);
	}
	printf("Extraordinario. Por ultimo, digame las horas de sueño de Gimli (Entre 0 y 12 por favor)");
	scanf(" %i", horas_de_sueno_gimli);
	while(horas_de_sueno(*horas_de_sueno_gimli) == false){
		printf(ROJO_CLARO"un numero entre 0 y 12 mi lord!"FIN);
		scanf(" %i", horas_de_sueno_gimli);
	}
}

/*
Precondición: Información lograda
Postcondición: Muestra la información recolectada en un resumen
*/
void resumen_de_datos(int viento,int humedad, char legolas_humor, char gimli_humor){
	printf(" - Viento: %i km/h\n - Humedad: %i %% de humedad\n - Estado de animo de Legolas: %c\n - Estado de animo de Gimli: %c\n", viento, humedad, legolas_humor, gimli_humor);
	printf("Resumen: %i %i %c %c.",viento, humedad, legolas_humor, gimli_humor);
						
}

/*
Precondición: La fecha del mes entre los parametros solicitados
Postcondición: informaciòn sobre el porcentaje de viento
*/
void determinacion_viento(int dia, int *viento){
	if(dia<=10){
		*viento = 75;
	} else if ((dia<=20) && (dia>=11)){
		*viento = 50;
	} else if ((dia<=30) && (dia>=21)){
		*viento = 25;
	}
}

/*
Precondición: La hora del día entre los parametros solicitados
Postcondición: Informaciòn sobre el porcentaje de humedad
*/
void determinacion_humedad(char hora, int *humedad){
	if(hora == MANANA){
		*humedad = 75;
	} else if (hora == TARDE){
		*humedad = 25;
	} else if (hora == NOCHE){
		*humedad = 50;
	}
}

/*
Precondición: información de cada personaje dentro de los parametros solicitados
Postcondición: Suma de puntos a partir de la información
*/
int conteo(char pie, char cena, int horas_de_sueno){
	int conteo = 0;
	if (pie == PIE_DERECHO){
		conteo = conteo + 10;
	} else conteo = conteo + 0;

	if (cena == ENSALADA){
		conteo = conteo + 20;
	} else if (cena == HAMBURGUESA){
		conteo = conteo + 15;
	} else if (cena == PIZZA){
		conteo = conteo + 10;
	} else if (cena == GUISO){
		conteo = conteo + 5;
	}
	if (horas_de_sueno <=4){
		conteo = conteo + 0;
	} else if ((horas_de_sueno <= 8) && horas_de_sueno >= 5){
		conteo = conteo + 10;
	} if (horas_de_sueno > 8){
		conteo = conteo + 20;
	}
	return conteo;
}

/*
Precondición: Suma total de puntos conseguida por el conteo
Postcondición: Define el estado de animo de Legolas
*/
void animo_legolas(char pie_legolas, char cena_legolas, int horas_de_sueno_legolas, char *legolas_humor){

	if (conteo(pie_legolas, cena_legolas, horas_de_sueno_legolas) < MIN_REGULAR_HUMOR){
		*legolas_humor = MAL_HUMOR;

	} else if ((conteo(pie_legolas, cena_legolas, horas_de_sueno_legolas) < MIN_BUEN_HUMOR) && ((conteo(pie_legolas, cena_legolas, horas_de_sueno_legolas) >= MIN_REGULAR_HUMOR))){
		*legolas_humor = REGULAR_HUMOR;

	} else if (conteo(pie_legolas, cena_legolas, horas_de_sueno_legolas) >= MIN_BUEN_HUMOR){
		*legolas_humor = BUEN_HUMOR;
	}
}

/*
Precondición: Suma total de puntos conseguida por el conteo
Postcondición: Define el estado de animo de Gimli
*/
void animo_gimli(char pie_gimli, char cena_gimli, int horas_de_sueno_gimli, char *gimli_humor){
		
	if (conteo(pie_gimli, cena_gimli, horas_de_sueno_gimli) < MIN_REGULAR_HUMOR){
		*gimli_humor = MAL_HUMOR;

	} else if ((conteo(pie_gimli, cena_gimli, horas_de_sueno_gimli) < MIN_BUEN_HUMOR) && ((conteo(pie_gimli, cena_gimli, horas_de_sueno_gimli) >= MIN_REGULAR_HUMOR))){
		*gimli_humor = REGULAR_HUMOR;

	} else if (conteo(pie_gimli, cena_gimli, horas_de_sueno_gimli) >= MIN_BUEN_HUMOR){
		*gimli_humor = BUEN_HUMOR;
	}

}

void animos(int* viento, int* humedad, char* legolas_humor, char* gimli_humor) {

	int dia;
	char hora;


	char pie_legolas;
	char cena_legolas;
	int horas_de_sueno_legolas;

	char pie_gimli;
	char cena_gimli;
	int horas_de_sueno_gimli;

	introduccion();
	preguntar_dia(&dia);
	preguntar_hora(&hora);
	info_legolas(&pie_legolas, &cena_legolas, &horas_de_sueno_legolas);
	info_gimli(&pie_gimli, &cena_gimli, &horas_de_sueno_gimli);

	determinacion_viento(dia, viento);
	determinacion_humedad(hora, humedad);

	animo_legolas(pie_legolas,cena_legolas, horas_de_sueno_legolas, legolas_humor);
	animo_gimli(pie_gimli, cena_gimli, horas_de_sueno_gimli, gimli_humor);
	
	resumen_de_datos(*viento, *humedad, *legolas_humor, *gimli_humor);
	printf("\n");

}