#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "entradas_datos.c"

#define BARCO 64
#define MAR 126

int x = 0, y = 0, n_jugador = 0, mapa1[20][20], n_barco1 = 0, mapa2[20][20], n_barco2 = 0;

int N_jugador() {
  int i = 0;
  printf("\n¿Con quien desea jugar?\n\n");
  printf("Si desea jugar contra la computadora presione 1\n");
  printf("Si desean jugar 2 personas presione 2\n");
  get_num(&n_jugador);
  while(i <= 1) {
    if(n_jugador == 1) {
      printf("respuesta 1\n");
      break;
    } else if(n_jugador == 2) {
      printf("respuesta 2\n");
      break;
    } else {
      n_jugador = 0;
      error();
    }
    
    get_num(&n_jugador);
  }
  return 0;
}

int datos_mapa() {
  int ae, ai;
  printf("\n¿cuantas filas desea que tenga su juego?(min 3, max 20) \t");
  get_num(&x);
  while(1) { /* verifica si respuesta x cumple las restricciones */
    if(x >= 3 && x <= 20) break;
    x = 0;
    printf("Respuesta no valida, vuelva a intentarlo\n");
    get_num(&x);
  }

  printf("¿cuantas columnas desea que tenga su juego?(min 3, max 20) \t");
  get_num(&y);
  while (1){ /*verifica si respuesta y cumple las restricciones*/
    if(y >= 3 && y <= 20) break;
    y = 0;
    printf("Respuesta no valida, vuelva a intentarlo\n");
    get_num(&y);
  }

  for(ae=0; ae <= y; ae++) { /*crea el mar designando ascii 126*/
    for(ai=0; ai <= x; ai++) {
      mapa1[ai][ae] = MAR;
      mapa2[ai][ae] = MAR;
    }
  }

  return 0;
}

int representacion_mapa1() {
  int i, e, ii = 65, ee = 0, l= 1;

  ee = x + ii;
  
  printf("\n\n Mapa1 \n\n");
  printf("    ");

  for(; ii < ee; ii++) /*hubica letras*/
    printf("%c   ",ii );

  for(e=0; e < y; e++) { /*Hubica letra y numero*/
    /*Hubica numero*/
    if(l <= 9)
      printf("\n 0%d ",l);
    else
      printf("\n %d ",l);

    for(i=0; i < x; i++)
      printf("%c   ", mapa1[i][e]);

    l++;
  }

  printf("\n\nAsi a quedado su mapa\nLos @ representan los barcos\n");
  printf("Los X representan los barcos eliminados\n\n");
  return 0;
}

int representacion_mapa2() {
  int i, e, ii = 65, ee = 0, l= 1;

  ee = x + ii;
  printf("\n\n Mapa2 \n\n");
  printf("    ");

  for(; ii < ee; ii++) /*hubica letras*/
    printf("%c   ",ii );

  for(e=0; e < y; e++) { /*Hubica letra y numero*/
    /*Hubica numero*/
    if(l <= 9)
      printf("\n 0%d ",l);
    else
      printf("\n %d ",l);

    for(i=0; i < x; i++)
      printf("%c   ", mapa2[i][e]);

    l++;
  }

  printf("\n\nAsi a quedado su mapa\nLos @ representan los barcos\nLos X representan los barcos eliminados\n\n");
  return 0;
}

int ubicar_barco() {
  int i, ii, iii = 0, f = 0, ff;

  for(i=1; i <= n_jugador; i++) {
    printf("Vamos a ubicar los barcos del %d° jugador, son %d barcos que debe hubicar\n", i, n_barco1);
    for(ii=1; ii <= n_barco1; ii++) { /* aqui no se requiere diferencia de n_barco ya que la cantidad no varia en este punto*/
      printf("Introdusca las cordenadas del %d° barco(A,1)\n", ii);
      printf("Primero la letra\t");
      entrada_letra(&iii, x);

      printf("Segundo el numero\t");
      entrada_numero(&f, x);

      printf("iii = %d f = %d\n",iii,f);

      f--;
      if(i == 1) {
        mapa1[iii][f] = BARCO;
        representacion_mapa1();
      } else if(i == 2) {
        mapa2[iii][f] = BARCO;
        representacion_mapa2();
      }

      iii = 0;
      f = 0;

      for(ff=0; ff >= 30; ff++) printf("\n");
    }
    ii = 1;
    iii = 0;
    f = 0;
  }

  return 0;
}

int atacar(int player) {
  int ii, iii, o, acierto = 0;
  printf("Primero la letra\t");
  entrada_letra(&ii, x);

  printf("Segundo el numero\t");
  entrada_numero(&iii, x);

  if(player == 1)
    o = mapa1[ii][iii];
  else if(player == 2)
    o = mapa2[ii][iii];
  
  if(o == 64) acierto = 1;

  return acierto;
}

int ataque() {
  int i = 1;

  while(1) {
    printf("es turno del %d° jugador\n", i);
    printf("Introdusca cordenada de ataque(A,1)\n");

    if(atacar(i)){
      printf("Ha hundido un barco a su oponente, le quedan ");
      if(i == 1)
        printf("%d\n", n_barco2);
      else
        printf("H%d\n", n_barco1);
    } else
      printf("A fallado\n");

    if(n_barco1 == 0){ /*elige ganador*/
      printf("A ganado el 2° jugador\n");
      break;
    }
    if(n_barco2 == 0){ /*elige ganador*/
      printf("A ganado el 1° jugador\n");
      break;
    } 
    
    if(i == 1)
      i++;
    else if(i == 2)
      i--;
    n_barco2 = 0; /* esto solo es para evitar que se cree un bucle infinito */
  }

  return 0;
}
int calcular_n_barcos() {
  int num = (x * y) / 9;
  return num;
}

int main() {
  printf("\nBienvenidos a combate naval\n");
  N_jugador();
  datos_mapa();
  representacion_mapa1();
  if(n_jugador > 1)
    representacion_mapa2();

  n_barco2 = calcular_n_barcos();
  n_barco1 = calcular_n_barcos();
  ubicar_barco();
  representacion_mapa1();
  ataque();
  return EXIT_SUCCESS;
}
