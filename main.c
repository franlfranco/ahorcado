/*
1) Hacer una función que permita ingresar tantas palabras como quiera el usuario o 100 palabras como máximo.
2) Hacer una función que teniendo en cuenta la longitud de un palabra, inicialice un segundo arreglo con el carácter “-”. (Pista: primero hay que copiar la palabra en el segundo arreglo y luego modificarlo).
3) Hacer una función que teniendo la posición de la letra copie esa letra en otro arreglo inicializado con la función anterior en la misma posición que la palabra original.
4) Hacer una función que reciba como parámetro el arreglo con la palabra, el arreglo inicializado en “-”
y una letra, por cada coincidencia de la letra en el arreglo con la palabra,
llame la función anterior para actualizar la letra en el arreglo con -.
Esta función debe retornar la cantidad de veces que se repite la letra o 0 en caso que
la letra no esté en la palabra.
5) Hacer una función que cuente y retorne la cantidad de elementos de una pila.
6) Hacer una función “juego” donde seleccione una palabra al azar (usando rand)
y le permita al usuario poder jugar al ahorcado utilizando las funciones anteriores,
el jugador tiene un total de 4 intentos, si no acierta todas las letras pierde y
se apila en una pila de partidas perdidas un 1, en caso de acertar todas las letras y
adivinar la palabra, se apila en una pila de partidas ganadas un 1.
7) Cuando el jugador decide no jugar más el sistema le muestra cuantas veces gano y cuantas perdió.
*/

#include "pila.c"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <term.h>
#include <stdbool.h>

const int maxPal=100;//Maximo de palabras a ingresar
const int maxChar=30;//Maximo de caracteres por palabra
const int vidas =4;

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

//Funcion del ejercicio 1
int cargarPalabras(char palabras[maxPal][maxChar], int dim){
  int cant=0;
  char control ='s';
  while(control=='s'&&cant<dim){
    printf("Ingrese una palabra: " );
    fflush(stdin);
    scanf("%s",palabras[cant]);
    printf("Desea ingresar otra palabra? s/n\n" );
    fflush(stdin);
    scanf(" %c",&control );
    cant ++;
  }
  return cant;
}
void mostrarPalabras(char palabras[maxPal][maxChar], int cant){
  printf("LAS PALABRAS POSIBLES SON:\n" );
  for (int i = 0; i < cant; i++) {
    printf("- %s\n",palabras[i] );
  }
}

//Funcion del ejercicio 2
void taparPalabra(char str1[maxChar], char str2[maxChar]){
  int cant = strlen(str1);
  for(int i=0;i<cant;i++){
    str2[i] = '-';
  }
  //printf("%s\n", str2);
}

//Funcion del ejercicio 3
void copiarLetra(char destino[maxChar], char original[maxChar], int pos){
  destino[pos] = original[pos];
  //printf("%s\n",destino );
}

//Funcion del ejercicio 4
int coincidencia(char original[maxChar],char destino[maxChar], char letra){
  int largo = strlen(original);
  int cont =0;
  for(int i =0;i<largo;i++){
    if(original[i]==letra){
      copiarLetra(destino,original,i);
      cont++;
    }
  }
  return cont;
}

int contarPila(Pila *p){
  int cont = 0;
  Pila aux;
  inicpila(&aux);
  while(!pilavacia(p)){
    apilar(&aux,desapilar(p));
    cont++;
  }
  while(!pilavacia(&aux)){
    apilar(p,desapilar(&aux));
  }
  return cont;
}

bool buscarLetra(char letras[], char letra){
  bool flag=0;
  int i=0;
  int max = strlen(letras);
  while(!flag&&i<max-1){
    if(letras[i]==letra){
      flag=1;
    }
    i++;
  }
  return flag;
}

void cargarLetra(char letras[], char letra){
  int pos = strlen(letras);
  letras[pos] = letra;
}

//Funcion del ejercicio 6
void juego(char palabras[maxPal][maxChar], int cant, char original[maxChar], char destino[maxChar],Pila *g, Pila *p){
  char letras[maxChar]=" ";
  char letra;
  int coin=0;
  int intentos=0;
  original = palabras[rand()%cant];
  taparPalabra(original,destino);
  printf("%s son %i letras putito\n", destino,strlen(destino));
  while(intentos<vidas&&coin<strlen(original)){
    printf("Ingresa una letra, MUERTO: " );
    fflush(stdin);
    scanf(" %c",&letra);
    cargarLetra(letras,letra);
    if(!buscarLetra(letras, letra)){
      if(!coincidencia(original,destino,letra)){
        intentos++;
      }else{
        coin += coincidencia(original,destino,letra);
        }
      printf("%s\n",destino);
    }else{
      printf("Ya ingresaste esa letra LADRON!\n");
    }
  }
    if(intentos<vidas){
        apilar(g,1);
        printf("\nQue ojete tenes, ganaste\n" );
      }else{
        apilar(p,1);
        printf("\nPerdiste por puto y cagon :) \n" );
        printf("La palabra era: %s\n",original );
      }
  }


int main(){
  char palabras[maxPal][maxChar]={" "};
  char str1[maxChar] = " ";//Pruebas
  char str2[maxChar];
  char control ='s';
  int posiciones[maxChar];
  int cant, coin;
  Pila ganadas, perdidas;
  inicpila(&ganadas); inicpila(&perdidas);
  srand(time(NULL));


  printf("EL AHORCADO\n\n" );
  cant = cargarPalabras(palabras,maxPal);
  //mostrarPalabras(palabras,cant);
  clearScreen();
  while(control=='s'){
    printf("EL AHORCADO\n\n" );
    juego(palabras,cant,str1,str2,&ganadas,&perdidas);
    printf("Queres jugar otra partida? O se te enfrio el pecho? s/n\n" );
    fflush(stdin);
    scanf(" %c", &control);
    clearScreen();
  }
  printf("EL AHORCADO\n\n" );
  printf("\nPartidas ganadas: %i\nPartidas perdidas: %i\n",contarPila(&ganadas),contarPila(&perdidas));
  return 0;
}
