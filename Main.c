#include<stdio.h>
#include<stdlib.h>
#include "gamelib.h"



int main(){
int var_menu = 0;
system("clear");
printf( CYN "PER ELIMINARE BUG GRAFICI IMPOSTARE LA FINESTRA A SCHERMO INTERO\n");
printf("PREMI ENTER PER CONTINUARE...\n");
while((getchar()) != '\n');
do
{
    
titolo();
menu_principale();
scanf("%d", &var_menu);
while((getchar()) != '\n');
switch (var_menu){
    case 1:
        imposta_gioco();
        break;
    case 2:
        combatti();
        break;
    case 3:
        termina_gioco();
        break;
    case 4:
        storia();
        break;
    case 5:
        regole();
        break;

    case 6:
        trailer();
        break;    

    default:
        printf("[Errore] inserisci un comando valido...\n");
        break;
    }}while (var_menu != 3);
}
