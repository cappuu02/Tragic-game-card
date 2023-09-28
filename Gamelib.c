//Progetto Luca Capuccini 
//matricola: 347711




#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include "gamelib.h"

//DEFINIZIONE VARIABILI GLOBALI
struct Mago mago1;
struct Mago mago2;
static short int num_carte_mazzo;
static int a, b, c, d, x;
struct Carta *inizio_mazzo;
struct Carta *fine_mazzo;
static int turno = 0;
static int mark1 = 0;
static int point1 = 0;
static int count_pesca = 0;
static int count_attacca = 0;





//DICHIARAZIONE FUNZIONI
static void clear_buffer(void);
void system_clear(void);
static int cmpfunc(const void*, const void*);
static void stampa_mazzo(struct Mago*);
static void inserisci_carta(struct Mago*, int);
static void inserisci_tipi_carte(struct Mago*);
static void delete_mazzo(struct Mago*);
static void pesca(struct Mago*);
static void inserisci_mano(struct Mago*, struct Carta*);
static void stampa_mano(struct Mago*);
static void stampa_campo(struct Mago*);
static void gioca_carta(struct Mago*, struct Mago*);
static void attacca(struct Mago*, struct Mago*);
static void passa_turno(void);


//DEFINIZIONE FUNZIONI

//funzione trailer
void trailer(void){
printf(YEL"Prima di iniziare a giocare è consigliato vedere il trailer di Tragic\n");
printf("Per vedere il trailer: copia il link e inseriscilo nella barra di ricerca di un browser\n");
printf("Buona Visione :)\n");
printf(GRN"https://www.youtube.com/watch?v=eCTahElrHLQ\n");
printf(CYN"\n");
printf(RED"Per tornare al menu principale digitare [INVIO].\n");
clear_buffer();
system_clear();
}


//funzione che pulisce il terminale
void system_clear(void){
  system("clear");
}

//clear buffer
void clear_buffer(void){
  while ((getchar()) != '\n');
}


//funzione passa turno
void passa_turno(void){
  if(turno == 1){
    turno++;
  }
  else if(turno == 2){
    turno--;
  }
}

//funzione che attacca
void attacca(struct Mago* pmago, struct Mago* pmago2){
int a = 0;
int b = 0;
int z = 0;
int x = 0;
int campo_nemico = false;
int campo_alleato = false;
int point1 = 0;
int point2 = 0;
int point3 = 0;

    
if(pmago2->campo[0]==NULL && pmago2->campo[1]==NULL && pmago2->campo[2]==NULL && pmago2->campo[3]==NULL){
  campo_nemico = true;
  //campo nemico vuoto
}

if(pmago->campo[0]==NULL && pmago->campo[1]==NULL && pmago->campo[2]==NULL && pmago->campo[3]==NULL){
  campo_alleato = true;
  //campo alleato vuoto
}

if(campo_alleato == true){
    printf("Non puoi attaccare dato che non hai creature in campo\n");
}

else if(campo_alleato == false){
    printf("Hai creature in campo quindi puoi attaccare\n");
    do
    {
        printf("Chi vuoi attaccare?:\n1]creature del nemico\n2]Mago nemico\n");
        scanf("%d", &a);
        clear_buffer();
        switch (a){
        case 1:
            if (campo_nemico == false){
            do
            {
                printf("Quale creatura vuoi attaccare?: [0] - [1] - [2] - [3]\n");
                scanf("%d", &b);
                clear_buffer();
                if (pmago2->campo[b] != NULL)
                {         
                  point1 = 1;      
                    do
                    {
                        printf("Con quale creatura alleata vuoi attaccare?: [0] - [1] - [2] - [3]\n");
                        scanf("%d", &z);
                        clear_buffer();                       
                        if ((pmago->campo[z]) != NULL)
                        {
                            point2 = 1;
                            if ( ((pmago->campo[z])->pv_carta) > ((pmago2->campo[b])->pv_carta) )
                            {   
                                (pmago->campo[z])->pv_carta = ((pmago->campo[z])->pv_carta) - ((pmago2->campo[b])->pv_carta);
                                printf("La creatura con cui hai attaccato ha ora [%d] punti vita\n", (pmago->campo[z])->pv_carta);
                                printf("Creatura nemica distrutta con successo!\n");
                                free(pmago2->campo[b]);
                                pmago2->campo[b] = NULL;
                               
                                
                            }

                            else if( ((pmago->campo[z])->pv_carta) == ((pmago2->campo[b])->pv_carta) )
                            {
                                printf("Le creature hanno stessi punti vita, muoiono entrambe nello scontro\n");
                                free(pmago->campo[z]);
                                free(pmago2->campo[b]);
                                pmago->campo[z] = NULL;
                                pmago2->campo[b] = NULL;

                            }

                            else if( ((pmago->campo[z])->pv_carta) < ((pmago2->campo[b])->pv_carta) )
                            {
                                printf("La creatura con cui hai attaccato ha meno punti vita della creatura avversaria\nLa creatura alleta muore valorosamente in battaglia\n");
                                (pmago2->campo[b])->pv_carta = ((pmago2->campo[b])->pv_carta) - ((pmago->campo[z])->pv_carta);
                                printf("La creatura nemica ha ora %d punti vita\n", (pmago2->campo[b])->pv_carta);
                                free(pmago->campo[z]);
                                pmago->campo[z] = NULL;
                            }

                        }
                
                        else{
                            printf("Lo slot selezionato non contiene carte creatura\n");
                        }} while (point2 == 0);
            
                }

                else{
                    printf("Lo slot selezionato non contiene carte creatura\n");
                }} while (point1 == 0);
            }       

            else{
                printf("Non ci sono creature nel campo nemico da attaccare\n");
            }
            break;
        
        case 2:
            if (campo_nemico == true){
                printf("Il campo dell'avversario e' vuoto, puoi attaccare direttamente il mago avversario\n");
                do{
                    printf("Con quale creatura alleata vuoi attaccare il mago avversario?: [0] - [1] - [2] - [3]\n");
                    scanf("%d", &x);
                    clear_buffer();
                    if (pmago->campo[x] != NULL){
                      point3 = 1;
                        pmago2->pv_mago = (pmago2->pv_mago) - ((pmago->campo[x])->pv_carta);
                        if(pmago2->pv_mago < 0){
                          pmago2->pv_mago = 0;
                          printf("La vita del mago2 e': [%d]\n", pmago2->pv_mago);
                        }
                        else{
                          printf("La vita del mago2 e': [%d]\n", pmago2->pv_mago);
                        }
                    }
                    else{
                        printf("La carta selezionata non e' di tipo creatura\n");
                    }}while(point3 == 0);
    
            }

            else if(campo_nemico == false){
                printf("Non puoi attaccare direttamente il nemico quando ci sono della creature nel campo avversario\n");
            }

        break;

        default:
            printf("Digita correttamente...\n");
            break;
        }
    } while (a < 1 || a > 2);
    
    
    
}

}//fine funzione attacca

//funzione che gioca le carte
void gioca_carta(struct Mago* pmago, struct Mago* pmago2){
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int campo_nemico = false;
int campo_alleato = false;
int mark1 = 0; //utilizzato per rimuovi creatura
int mark2 = 0; //utilizzato per infliggi danno
int mark3 = 0; //utilizzato per guarisci danno

if(pmago2->campo[0]==NULL && pmago2->campo[1]==NULL && pmago2->campo[2]==NULL && pmago2->campo[3]==NULL){
  campo_nemico = true;
  //campo nemico vuoto
}

if(pmago->campo[0]==NULL && pmago->campo[1]==NULL && pmago->campo[2]==NULL && pmago->campo[3]==NULL){
  campo_alleato = true;
  //campo alleato vuoto
}

if(point1 == 1){
    printf("Hai già giocato una carta in questo turno\n");
}

else{
if(point1 == 0){
printf("Quale carta dalla mano vuoi giocare?\n[0] - [1] - [2] - [3] - [4] - [5]\n");
scanf("%d", &a);
clear_buffer();
do{
if(pmago->mano[a] != NULL){
switch(a){
    case 0:
    for (int i = 0; i < 4; i++){
      if(point1 == 1){
            break;
        }
        if(pmago->campo[i] == NULL){
            printf("slot [%d] del campo libero!\n", i);
            pmago->campo[i] = pmago->mano[0];
            pmago->mano[0] = NULL;
            point1++;

            //CASO RIMUOVI CREATURA
            if((pmago->campo[i])->tipo == rimuovi_creatura){
                if(campo_nemico == false){
                    do{
                        printf("Quale creatura dell'avversario vuoi rimuovere?\n[0] - [1] - [2] - [3]\n");
                        scanf("%d", &c);
                        clear_buffer();
                        if (pmago2->campo[c] != NULL){
                            mark1 = 1;
                            free(pmago2->campo[c]);
                            pmago2->campo[c] = NULL;
                            free(pmago->campo[i]);
                            pmago->campo[i] = NULL;
                            printf("Creatura nemica rimossa\n");
                            break;
                        }
                        else{
                            printf("La carta selezionata non e' di tipo creatura\n");
                        }}while(mark1 == 0);
                  }
           
                if(campo_nemico == true){
                    printf("Il campo nemico e' vuoto, non puoi rimuovere nessuna creatura\n");
                    printf("La carta verra' distrutta\n");
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                    break;
                }
            }//fine if rimuovi creatura



            //CASO CREATURA 
            else if((pmago->campo[i])->tipo == creatura){
                printf("La carta evocata e' di tipo creatura\n");
            }



            //CASO INFLIGGI DANNO
            else if ((pmago->campo[i])->tipo == infliggi_danno){
            do{
            printf("La carta e' di tipo infliggi danno, chi vuoi danneggiare?:\n");
            printf("1]Per danneggiare il mago nemico\n2] Per infliggere danno alle creature nemiche\n");
            scanf("%d", &b);
            clear_buffer();
            switch (b){
            case 1:{
              if(campo_nemico == true){
                pmago2->pv_mago = (pmago2->pv_mago) - ((pmago->campo[i])->pv_carta);
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                printf("Hai danneggiato il mago nemico\n");
                if(pmago2->pv_mago > 1000){
                  pmago2->pv_mago = 0;
                  printf("La nuova vita del mago avversario e': %d\n", pmago2->pv_mago);
                }
                else{
                  printf("La nuova vita del mago avversario e': %d\n", pmago2->pv_mago);
                }
              }
              else{
                printf("Non puoi attaccare direttamente il mago nemico dato che ha delle creature in campo\n");
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                break;
              }
                break;}
            case 2:
                if(campo_nemico == false){               
                do{
                printf("Quale creatura dell'avversario vuoi danneggiare?\n[0] - [1] - [2] - [3]\n");
                scanf("%d", &d);
                clear_buffer();
                if (pmago2->campo[d] != NULL){
                  mark2 = 1;
                    if (((pmago->campo[i])->pv_carta) >= ((pmago2->campo[d])->pv_carta)){
                        free(pmago2->campo[d]);
                        pmago2->campo[d] = NULL;
                        free(pmago->campo[i]);
                        pmago->campo[i] = NULL;
                        printf("la Creatura nemica e' stata distutta dalla carta infliggi danno\n");
                    }
                    else if(((pmago2->campo[d])->pv_carta) > ((pmago->campo[i])->pv_carta)){
                        (pmago2->campo[d])->pv_carta = ((pmago2->campo[d])->pv_carta) - ((pmago->campo[i])->pv_carta);
                        free(pmago->campo[i]);
                        pmago->campo[i] = NULL;
                        printf("La creatura nemica e' stata distrutta\n");
                        printf("La nuova vita della creatura nemica e': %d\n", (pmago2->campo[d])->pv_carta);
                    }
                  }
                else{
                  printf("La carta che vuoi danneggiare non e' di tipo creatura\n");
                }}while(mark2 == 0);
                }//fine if campo nemico == false

                else if(campo_nemico == true){
                    printf("Non puoi danneggiare nessuna creatura dato che il campo nemico e' vuoto\n");
                    printf("La carta giocata verra' distrutta\n");
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                }//fine if campo nemico == true
                break;
            
            default:
                printf("Digita corretamente\n");
                break;
            }}while(b < 1 || b > 2);
        }//fine if infliggi danno


        //CASO GUARISCI DANNO
        else if ((pmago->campo[i])->tipo == guarisci_danno){
            printf("La carta giocata e' di tipo guarisci danno, chi vuoi guarire?:\n");
            do{
            printf("1] Curare te stesso\n2] Curare una tua creatura");
            scanf("%d", &b);
            clear_buffer();
            switch (b){
            case 1:
                pmago->pv_mago = (pmago->pv_mago) + ((pmago->campo[i])->pv_carta);
                if(pmago->pv_mago < 100){
                  printf("ti sei curato, la tua nuova vita e': %d\n", pmago->pv_mago);
                }
                else if(pmago->pv_mago > 100){
                  pmago->pv_mago = 100;
                  printf("Hai sforato la vita massima\n");
                  printf("La tua vita e': %d\n", pmago->pv_mago);
                }
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                break;
            
            case 2:
            if(campo_alleato == false){
                do{
                  do{
                  printf("Quale creatura alleata vuoi curare?\n[0] - [1] - [2] - [3]\n");
                  scanf("%d", &d);
                  clear_buffer();
                  if(d < 0 || d > 3 ){
                    printf("digitare correttamente\n");
                  }}while(d < 0 || d > 3);
                  if(pmago->campo[d] != NULL){
                  if ((pmago->campo[d])->tipo == creatura){
                    mark3 = 1;
                    (pmago->campo[d])->pv_carta = ((pmago->campo[d])->pv_carta) + ((pmago->campo[i])->pv_carta);
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                    printf("La creatura nello slot %d del campo alleato ha ora %d punti vita\n", d, (pmago->campo[d])->pv_carta);
                  }
                  }
                  else if(pmago->campo[d] == NULL){
                    printf("La carta non e' di tipo creatura\n");
                  }}while(mark3 == 0);
            }

            else if(campo_alleato == true){
                printf("Non ci sono creature nel tuo campo da gioco, non puoi curare nessuno\n");
                printf("La carta verra' quindi distrutta\n");
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
            }
            break;
            
            default:
                printf("Digita correttamente\n");
                break;
            }}while(b < 1 || b > 2);
        }//fine if guarisci danno


        }//fine if
    }//fine for
    break;


     case 1:
        for (int i = 0; i < 4; i++){
          if(point1 == 1){
            break;
        }
        if(pmago->campo[i] == NULL){
            printf("slot [%d] del campo libero!\n", i);
            pmago->campo[i] = pmago->mano[1];
            pmago->mano[1] = NULL;
            point1++;

            //CASO RIMUOVI CREATURA
            if((pmago->campo[i])->tipo == rimuovi_creatura){
                if(campo_nemico == false){
                    do{
                        printf("Quale creatura dell'avversario vuoi rimuovere?\n[0] - [1] - [2] - [3]\n");
                        scanf("%d", &c);
                        clear_buffer();
                        if (pmago2->campo[c] != NULL){
                            mark1 = 1;
                            free(pmago2->campo[c]);
                            pmago2->campo[c] = NULL;
                            free(pmago->campo[i]);
                            pmago->campo[i] = NULL;
                            printf("Creatura nemica rimossa\n");
                            break;
                        }
                        else{
                            printf("La carta selezionata non e' di tipo creatura\n");                         
                        }}while(mark1 == 0);
                  }
           
                if(campo_nemico == true){
                    printf("Il campo nemico e' vuoto, non puoi rimuovere nessuna creatura\n");
                    printf("La carta verra' distrutta\n");
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                    break;
                }
            }//fine if rimuovi creatura



            //CASO CREATURA 
            else if((pmago->campo[i])->tipo == creatura){
                printf("La carta evocata e' di tipo creatura\n");
            }



             //CASO INFLIGGI DANNO
            else if ((pmago->campo[i])->tipo == infliggi_danno){
            do{
            printf("La carta e' di tipo infliggi danno, chi vuoi danneggiare?:\n");
            printf("1]Per danneggiare il mago nemico\n2] Per infliggere danno alle creature nemiche\n");
            scanf("%d", &b);
            clear_buffer();
            switch (b){
            case 1:{
              if(campo_nemico == true){
                pmago2->pv_mago = (pmago2->pv_mago) - ((pmago->campo[i])->pv_carta);
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                printf("Hai danneggiato il mago nemico\n");
                if(pmago2->pv_mago > 1000){
                  pmago2->pv_mago = 0;
                printf("La nuova vita del mago avversario e': %d\n", pmago2->pv_mago);
                }
                else{
                  printf("La nuova vita del mago avversario e': %d\n", pmago2->pv_mago);
                }
              }
              else{
                printf("Non puoi attaccare direttamente il mago nemico dato che ha delle creature in campo\n");
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                break;
              }
                break;}
            case 2:
                if(campo_nemico == false){               
                do{
                printf("Quale creatura dell'avversario vuoi danneggiare?\n[0] - [1] - [2] - [3]\n");
                scanf("%d", &d);
                clear_buffer();
                if (pmago2->campo[d] != NULL){
                  mark2 = 1;
                    if (((pmago->campo[i])->pv_carta) >= ((pmago2->campo[d])->pv_carta)){
                        free(pmago2->campo[d]);
                        pmago2->campo[d] = NULL;
                        free(pmago->campo[i]);
                        pmago->campo[i] = NULL;
                        printf("la Creatura nemica e' stata distutta dalla carta infliggi danno\n");
                    }
                    else if(((pmago2->campo[d])->pv_carta) > ((pmago->campo[i])->pv_carta)){
                        (pmago2->campo[d])->pv_carta = ((pmago2->campo[d])->pv_carta) - ((pmago->campo[i])->pv_carta);
                        free(pmago->campo[i]);
                        pmago->campo[i] = NULL;
                        printf("La creatura nemica e' stata distrutta\n");
                        printf("La nuova vita della creatura nemica e': %d\n", (pmago2->campo[d])->pv_carta);
                    }
                  }
                else{
                  printf("La carta che vuoi danneggiare non e' di tipo creatura\n");
                }}while(mark2 == 0);
                }//fine if campo nemico == false

                else if(campo_nemico == true){
                    printf("Non puoi danneggiare nessuna creatura dato che il campo nemico e' vuoto\n");
                    printf("La carta giocata verra' distrutta\n");
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                }//fine if campo nemico == true
                break;
            
            default:
                printf("Digita corretamente\n");
                break;
            }}while(b < 1 || b > 2);
        }//fine if infliggi danno


        //CASO GUARISCI DANNO
        else if ((pmago->campo[i])->tipo == guarisci_danno){
            printf("La carta giocata e' di tipo guarisci danno, chi vuoi guarire?:\n");
            do{
            printf("1] Curare te stesso\n2] Curare una tua creatura");
            scanf("%d", &b);
            clear_buffer();
            switch (b){
            case 1:
                pmago->pv_mago = (pmago->pv_mago) + ((pmago->campo[i])->pv_carta);
                if(pmago->pv_mago < 100){
                  printf("ti sei curato, la tua nuova vita e': %d\n", pmago->pv_mago);
                }
                else if(pmago->pv_mago > 100){
                  pmago->pv_mago = 100;
                  printf("Hai sforato la vita massima\n");
                  printf("La tua vita e': %d\n", pmago->pv_mago);
                }
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                break;
            
            case 2:
            if(campo_alleato == false){
                do{
                  do{
                  printf("Quale creatura alleata vuoi curare?\n[0] - [1] - [2] - [3]\n");
                  scanf("%d", &d);
                  clear_buffer();
                  if(d < 0 || d > 3 ){
                    printf("digitare correttamente\n");
                  }}while(d < 0 || d > 3);
                  if(pmago->campo[d] != NULL){
                  if ((pmago->campo[d])->tipo == creatura){
                    mark3 = 1;
                    (pmago->campo[d])->pv_carta = ((pmago->campo[d])->pv_carta) + ((pmago->campo[i])->pv_carta);
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                    printf("La creatura nello slot %d del campo alleato ha ora %d punti vita\n", d, (pmago->campo[d])->pv_carta);
                  }
                  }
                  else if(pmago->campo[d] == NULL){
                    printf("La carta non e' di tipo creatura\n");
                  }}while(mark3 == 0);
            }

            else if(campo_alleato == true){
                printf("Non ci sono creature nel tuo campo da gioco, non puoi curare nessuno\n");
                printf("La carta verra' quindi distrutta\n");
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
            }
            break;
            
            default:
                printf("Digita correttamente\n");
                break;
            }}while(b < 1 || b > 2);
        }//fine if guarisci danno


        }//fine if
    }//fine for
    break;

    case 2:
    for (int i = 0; i < 4; i++){
      if(point1 == 1){
            break;
        }
        if(pmago->campo[i] == NULL){
            printf("slot [%d] del campo libero!\n", i);
            pmago->campo[i] = pmago->mano[2];
            pmago->mano[2] = NULL;
            point1++;

            //CASO RIMUOVI CREATURA
            if((pmago->campo[i])->tipo == rimuovi_creatura){
                if(campo_nemico == false){
                    do{
                        printf("Quale creatura dell'avversario vuoi rimuovere?\n[0] - [1] - [2] - [3]\n");
                        scanf("%d", &c);
                        clear_buffer();
                        if (pmago2->campo[c] != NULL){
                            mark1 = 1;
                            free(pmago2->campo[c]);
                            pmago2->campo[c] = NULL;
                            free(pmago->campo[i]);
                            pmago->campo[i] = NULL;
                            printf("Creatura nemica rimossa\n");
                            break;
                        }
                        else{
                            printf("La carta selezionata non e' di tipo creatura\n");
                        }}while(mark1 == 0);
                  }
           
                if(campo_nemico == true){
                    printf("Il campo nemico e' vuoto, non puoi rimuovere nessuna creatura\n");
                    printf("La carta verra' distrutta\n");
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                    break;
                }
            }//fine if rimuovi creatura



            //CASO CREATURA 
            else if((pmago->campo[i])->tipo == creatura){
                printf("La carta evocata e' di tipo creatura\n");
            }



             //CASO INFLIGGI DANNO
            else if ((pmago->campo[i])->tipo == infliggi_danno){
            do{
            printf("La carta e' di tipo infliggi danno, chi vuoi danneggiare?:\n");
            printf("1]Per danneggiare il mago nemico\n2] Per infliggere danno alle creature nemiche\n");
            scanf("%d", &b);
            clear_buffer();
            switch (b){
            case 1:{
              if(campo_nemico == true){
                pmago2->pv_mago = (pmago2->pv_mago) - ((pmago->campo[i])->pv_carta);
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                printf("Hai danneggiato il mago nemico\n");
                if(pmago2->pv_mago > 1000){
                  pmago2->pv_mago = 0;
                printf("La nuova vita del mago avversario e': %d\n", pmago2->pv_mago);
                }
                else{
                  printf("La nuova vita del mago avversario e': %d\n", pmago2->pv_mago);
                }
              }
              else{
                printf("Non puoi attaccare direttamente il mago nemico dato che ha delle creature in campo\n");
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                break;
              }
                break;}
            case 2:
                if(campo_nemico == false){               
                do{
                printf("Quale creatura dell'avversario vuoi danneggiare?\n[0] - [1] - [2] - [3]\n");
                scanf("%d", &d);
                clear_buffer();
                if (pmago2->campo[d] != NULL){
                  mark2 = 1;
                    if (((pmago->campo[i])->pv_carta) >= ((pmago2->campo[d])->pv_carta)){
                        free(pmago2->campo[d]);
                        pmago2->campo[d] = NULL;
                        free(pmago->campo[i]);
                        pmago->campo[i] = NULL;
                        printf("la Creatura nemica e' stata distutta dalla carta infliggi danno\n");
                    }
                    else if(((pmago2->campo[d])->pv_carta) > ((pmago->campo[i])->pv_carta)){
                        (pmago2->campo[d])->pv_carta = ((pmago2->campo[d])->pv_carta) - ((pmago->campo[i])->pv_carta);
                        free(pmago->campo[i]);
                        pmago->campo[i] = NULL;
                        printf("La creatura nemica e' stata distrutta\n");
                        printf("La nuova vita della creatura nemica e': %d\n", (pmago2->campo[d])->pv_carta);
                    }
                  }
                else{
                  printf("La carta che vuoi danneggiare non e' di tipo creatura\n");
                }}while(mark2 == 0);
                }//fine if campo nemico == false

                else if(campo_nemico == true){
                    printf("Non puoi danneggiare nessuna creatura dato che il campo nemico e' vuoto\n");
                    printf("La carta giocata verra' distrutta\n");
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                }//fine if campo nemico == true
                break;
            
            default:
                printf("Digita corretamente\n");
                break;
            }}while(b < 1 || b > 2);
        }//fine if infliggi danno


        //CASO GUARISCI DANNO
        else if ((pmago->campo[i])->tipo == guarisci_danno){
            printf("La carta giocata e' di tipo guarisci danno, chi vuoi guarire?:\n");
            do{
            printf("1] Curare te stesso\n2] Curare una tua creatura");
            scanf("%d", &b);
            clear_buffer();
            switch (b){
            case 1:
                pmago->pv_mago = (pmago->pv_mago) + ((pmago->campo[i])->pv_carta);
                if(pmago->pv_mago < 100){
                  printf("ti sei curato, la tua nuova vita e': %d\n", pmago->pv_mago);
                }
                else if(pmago->pv_mago > 100){
                  pmago->pv_mago = 100;
                  printf("Hai sforato la vita massima\n");
                  printf("La tua vita e': %d\n", pmago->pv_mago);
                }
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                break;
            
            case 2:
            if(campo_alleato == false){
                do{
                  do{
                  printf("Quale creatura alleata vuoi curare?\n[0] - [1] - [2] - [3]\n");
                  scanf("%d", &d);
                  clear_buffer();
                  if(d < 0 || d > 3 ){
                    printf("digitare correttamente\n");
                  }}while(d < 0 || d > 3);
                  if(pmago->campo[d] != NULL){
                  if ((pmago->campo[d])->tipo == creatura){
                    mark3 = 1;
                    (pmago->campo[d])->pv_carta = ((pmago->campo[d])->pv_carta) + ((pmago->campo[i])->pv_carta);
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                    printf("La creatura nello slot %d del campo alleato ha ora %d punti vita\n", d, (pmago->campo[d])->pv_carta);
                  }
                  }
                  else if(pmago->campo[d] == NULL){
                    printf("La carta non e' di tipo creatura\n");
                  }}while(mark3 == 0);
            }

            else if(campo_alleato == true){
                printf("Non ci sono creature nel tuo campo da gioco, non puoi curare nessuno\n");
                printf("La carta verra' quindi distrutta\n");
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
            }
            break;
            
            default:
                printf("Digita correttamente\n");
                break;
            }}while(b < 1 || b > 2);
        }//fine if guarisci danno


        }//fine if
    }//fine for
    break;

     case 3:
    for (int i = 0; i < 4; i++){
      if(point1 == 1){
            break;
        }
        if(pmago->campo[i] == NULL){
            printf("slot [%d] del campo libero!\n", i);
            pmago->campo[i] = pmago->mano[3];
            pmago->mano[3] = NULL;
            point1++;

            //CASO RIMUOVI CREATURA
            if((pmago->campo[i])->tipo == rimuovi_creatura){
                if(campo_nemico == false){
                    do{
                        printf("Quale creatura dell'avversario vuoi rimuovere?\n[0] - [1] - [2] - [3]\n");
                        scanf("%d", &c);
                        clear_buffer();
                        if (pmago2->campo[c] != NULL){
                            mark1 = 1;
                            free(pmago2->campo[c]);
                            pmago2->campo[c] = NULL;
                            free(pmago->campo[i]);
                            pmago->campo[i] = NULL;
                            printf("Creatura nemica rimossa\n");
                            break;
                        }
                        else{
                            printf("La carta selezionata non e' di tipo creatura\n");
                        }}while(mark1 == 0);
                  }
           
                if(campo_nemico == true){
                    printf("Il campo nemico e' vuoto, non puoi rimuovere nessuna creatura\n");
                    printf("La carta verra' distrutta\n");
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                    break;
                }
            }//fine if rimuovi creatura



            //CASO CREATURA 
            else if((pmago->campo[i])->tipo == creatura){
                printf("La carta evocata e' di tipo creatura\n");
            }



             //CASO INFLIGGI DANNO
            else if ((pmago->campo[i])->tipo == infliggi_danno){
            do{
            printf("La carta e' di tipo infliggi danno, chi vuoi danneggiare?:\n");
            printf("1]Per danneggiare il mago nemico\n2] Per infliggere danno alle creature nemiche\n");
            scanf("%d", &b);
            clear_buffer();
            switch (b){
            case 1:{
              if(campo_nemico == true){
                pmago2->pv_mago = (pmago2->pv_mago) - ((pmago->campo[i])->pv_carta);
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                printf("Hai danneggiato il mago nemico\n");
                if(pmago2->pv_mago > 1000){
                  pmago2->pv_mago = 0;
                printf("La nuova vita del mago avversario e': %d\n", pmago2->pv_mago);
                }
                else{
                  printf("La nuova vita del mago avversario e': %d\n", pmago2->pv_mago);
                }
              }
              else{
                printf("Non puoi attaccare direttamente il mago nemico dato che ha delle creature in campo\n");
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                break;
              }
                break;}
            case 2:
                if(campo_nemico == false){               
                do{
                printf("Quale creatura dell'avversario vuoi danneggiare?\n[0] - [1] - [2] - [3]\n");
                scanf("%d", &d);
                clear_buffer();
                if (pmago2->campo[d] != NULL){
                  mark2 = 1;
                    if (((pmago->campo[i])->pv_carta) >= ((pmago2->campo[d])->pv_carta)){
                        free(pmago2->campo[d]);
                        pmago2->campo[d] = NULL;
                        free(pmago->campo[i]);
                        pmago->campo[i] = NULL;
                        printf("la Creatura nemica e' stata distutta dalla carta infliggi danno\n");
                    }
                    else if(((pmago2->campo[d])->pv_carta) > ((pmago->campo[i])->pv_carta)){
                        (pmago2->campo[d])->pv_carta = ((pmago2->campo[d])->pv_carta) - ((pmago->campo[i])->pv_carta);
                        free(pmago->campo[i]);
                        pmago->campo[i] = NULL;
                        printf("La creatura nemica e' stata distrutta\n");
                        printf("La nuova vita della creatura nemica e': %d\n", (pmago2->campo[d])->pv_carta);
                    }
                  }
                else{
                  printf("La carta che vuoi danneggiare non e' di tipo creatura\n");
                }}while(mark2 == 0);
                }//fine if campo nemico == false

                else if(campo_nemico == true){
                    printf("Non puoi danneggiare nessuna creatura dato che il campo nemico e' vuoto\n");
                    printf("La carta giocata verra' distrutta\n");
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                }//fine if campo nemico == true
                break;
            
            default:
                printf("Digita corretamente\n");
                break;
            }}while(b < 1 || b > 2);
        }//fine if infliggi danno


        //CASO GUARISCI DANNO
        else if ((pmago->campo[i])->tipo == guarisci_danno){
            printf("La carta giocata e' di tipo guarisci danno, chi vuoi guarire?:\n");
            do{
            printf("1] Curare te stesso\n2] Curare una tua creatura");
            scanf("%d", &b);
            clear_buffer();
            switch (b){
            case 1:
                pmago->pv_mago = (pmago->pv_mago) + ((pmago->campo[i])->pv_carta);
                if(pmago->pv_mago < 100){
                  printf("ti sei curato, la tua nuova vita e': %d\n", pmago->pv_mago);
                }
                else if(pmago->pv_mago > 100){
                  pmago->pv_mago = 100;
                  printf("Hai sforato la vita massima\n");
                  printf("La tua vita e': %d\n", pmago->pv_mago);
                }
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                break;
            
            case 2:
            if(campo_alleato == false){
                do{
                  do{
                  printf("Quale creatura alleata vuoi curare?\n[0] - [1] - [2] - [3]\n");
                  scanf("%d", &d);
                  clear_buffer();
                  if(d < 0 || d > 3 ){
                    printf("digitare correttamente\n");
                  }}while(d < 0 || d > 3);
                  if(pmago->campo[d] != NULL){
                  if ((pmago->campo[d])->tipo == creatura){
                    mark3 = 1;
                    (pmago->campo[d])->pv_carta = ((pmago->campo[d])->pv_carta) + ((pmago->campo[i])->pv_carta);
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                    printf("La creatura nello slot %d del campo alleato ha ora %d punti vita\n", d, (pmago->campo[d])->pv_carta);
                  }
                  }
                  else if(pmago->campo[d] == NULL){
                    printf("La carta non e' di tipo creatura\n");
                  }}while(mark3 == 0);
            }

            else if(campo_alleato == true){
                printf("Non ci sono creature nel tuo campo da gioco, non puoi curare nessuno\n");
                printf("La carta verra' quindi distrutta\n");
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
            }
            break;
            
            default:
                printf("Digita correttamente\n");
                break;
            }}while(b < 1 || b > 2);
        }//fine if guarisci danno


        }//fine if
    }//fine for
    break;

     case 4:
    for (int i = 0; i < 4; i++){
      if(point1 == 1){
            break;
        }
        if(pmago->campo[i] == NULL){
            printf("slot [%d] del campo libero!\n", i);
            pmago->campo[i] = pmago->mano[4];
            pmago->mano[4] = NULL;
            point1++;

            //CASO RIMUOVI CREATURA
            if((pmago->campo[i])->tipo == rimuovi_creatura){
                if(campo_nemico == false){
                    do{
                        printf("Quale creatura dell'avversario vuoi rimuovere?\n[0] - [1] - [2] - [3]\n");
                        scanf("%d", &c);
                        clear_buffer();
                        if (pmago2->campo[c] != NULL){
                            mark1 = 1;
                            free(pmago2->campo[c]);
                            pmago2->campo[c] = NULL;
                            free(pmago->campo[i]);
                            pmago->campo[i] = NULL;
                            printf("Creatura nemica rimossa\n");
                            break;
                        }
                        else{
                            printf("La carta selezionata non e' di tipo creatura\n");
                        }}while(mark1 == 0);
                  }
           
                if(campo_nemico == true){
                    printf("Il campo nemico e' vuoto, non puoi rimuovere nessuna creatura\n");
                    printf("La carta verra' distrutta\n");
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                    break;
                }
            }//fine if rimuovi creatura


            //CASO CREATURA 
            else if((pmago->campo[i])->tipo == creatura){
                printf("La carta evocata e' di tipo creatura\n");
            }



             //CASO INFLIGGI DANNO
            else if ((pmago->campo[i])->tipo == infliggi_danno){
            do{
            printf("La carta e' di tipo infliggi danno, chi vuoi danneggiare?:\n");
            printf("1]Per danneggiare il mago nemico\n2] Per infliggere danno alle creature nemiche\n");
            scanf("%d", &b);
            clear_buffer();
            switch (b){
            case 1:{
              if(campo_nemico == true){
                pmago2->pv_mago = (pmago2->pv_mago) - ((pmago->campo[i])->pv_carta);
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                printf("Hai danneggiato il mago nemico\n");
                if(pmago2->pv_mago > 1000){
                  pmago2->pv_mago = 0;
                printf("La nuova vita del mago avversario e': %d\n", pmago2->pv_mago);
                }
                else{
                  printf("La nuova vita del mago avversario e': %d\n", pmago2->pv_mago);
                }
              }
              else{
                printf("Non puoi attaccare direttamente il mago nemico dato che ha delle creature in campo\n");
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                break;
              }
                break;}
            case 2:
                if(campo_nemico == false){               
                do{
                printf("Quale creatura dell'avversario vuoi danneggiare?\n[0] - [1] - [2] - [3]\n");
                scanf("%d", &d);
                clear_buffer();
                if (pmago2->campo[d] != NULL){
                  mark2 = 1;
                    if (((pmago->campo[i])->pv_carta) >= ((pmago2->campo[d])->pv_carta)){
                        free(pmago2->campo[d]);
                        pmago2->campo[d] = NULL;
                        free(pmago->campo[i]);
                        pmago->campo[i] = NULL;
                        printf("la Creatura nemica e' stata distutta dalla carta infliggi danno\n");
                    }
                    else if(((pmago2->campo[d])->pv_carta) > ((pmago->campo[i])->pv_carta)){
                        (pmago2->campo[d])->pv_carta = ((pmago2->campo[d])->pv_carta) - ((pmago->campo[i])->pv_carta);
                        free(pmago->campo[i]);
                        pmago->campo[i] = NULL;
                        printf("La creatura nemica e' stata distrutta\n");
                        printf("La nuova vita della creatura nemica e': %d\n", (pmago2->campo[d])->pv_carta);
                    }
                  }
                else{
                  printf("La carta che vuoi danneggiare non e' di tipo creatura\n");
                }}while(mark2 == 0);
                }//fine if campo nemico == false

                else if(campo_nemico == true){
                    printf("Non puoi danneggiare nessuna creatura dato che il campo nemico e' vuoto\n");
                    printf("La carta giocata verra' distrutta\n");
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                }//fine if campo nemico == true
                break;
            
            default:
                printf("Digita corretamente\n");
                break;
            }}while(b < 1 || b > 2);
        }//fine if infliggi danno


       //CASO GUARISCI DANNO
        else if ((pmago->campo[i])->tipo == guarisci_danno){
            printf("La carta giocata e' di tipo guarisci danno, chi vuoi guarire?:\n");
            do{
            printf("1] Curare te stesso\n2] Curare una tua creatura");
            scanf("%d", &b);
            clear_buffer();
            switch (b){
            case 1:
                pmago->pv_mago = (pmago->pv_mago) + ((pmago->campo[i])->pv_carta);
                if(pmago->pv_mago < 100){
                  printf("ti sei curato, la tua nuova vita e': %d\n", pmago->pv_mago);
                }
                else if(pmago->pv_mago > 100){
                  pmago->pv_mago = 100;
                  printf("Hai sforato la vita massima\n");
                  printf("La tua vita e': %d\n", pmago->pv_mago);
                }
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                break;
            
            case 2:
            if(campo_alleato == false){
                do{
                  do{
                  printf("Quale creatura alleata vuoi curare?\n[0] - [1] - [2] - [3]\n");
                  scanf("%d", &d);
                  clear_buffer();
                  if(d < 0 || d > 3 ){
                    printf("digitare correttamente\n");
                  }}while(d < 0 || d > 3);
                  if(pmago->campo[d] != NULL){
                  if ((pmago->campo[d])->tipo == creatura){
                    mark3 = 1;
                    (pmago->campo[d])->pv_carta = ((pmago->campo[d])->pv_carta) + ((pmago->campo[i])->pv_carta);
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                    printf("La creatura nello slot %d del campo alleato ha ora %d punti vita\n", d, (pmago->campo[d])->pv_carta);
                  }
                  }
                  else if(pmago->campo[d] == NULL){
                    printf("La carta non e' di tipo creatura\n");
                  }}while(mark3 == 0);
            }

            else if(campo_alleato == true){
                printf("Non ci sono creature nel tuo campo da gioco, non puoi curare nessuno\n");
                printf("La carta verra' quindi distrutta\n");
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
            }
            break;
            
            default:
                printf("Digita correttamente\n");
                break;
            }}while(b < 1 || b > 2);
        }//fine if guarisci danno

        }//fine if
    }//fine for
    break;

     case 5:
    for (int i = 0; i < 4; i++){
      if(point1 == 1){
            break;
        }
        if(pmago->campo[i] == NULL){
            printf("slot [%d] del campo libero!\n", i);
            pmago->campo[i] = pmago->mano[5];
            pmago->mano[5] = NULL;
            point1++;

            //CASO RIMUOVI CREATURA
            if((pmago->campo[i])->tipo == rimuovi_creatura){
                if(campo_nemico == false){
                    do{
                        printf("Quale creatura dell'avversario vuoi rimuovere?\n[0] - [1] - [2] - [3]\n");
                        scanf("%d", &c);
                        clear_buffer();
                        if (pmago2->campo[c] != NULL){
                            mark1 = 1;
                            free(pmago2->campo[c]);
                            pmago2->campo[c] = NULL;
                            free(pmago->campo[i]);
                            pmago->campo[i] = NULL;
                            printf("Creatura nemica rimossa\n");
                            break;
                        }
                        else{
                            printf("La carta selezionata non e' di tipo creatura\n");
                        }}while(mark1 == 0);
                  }
           
                if(campo_nemico == true){
                    printf("Il campo nemico e' vuoto, non puoi rimuovere nessuna creatura\n");
                    printf("La carta verra' distrutta\n");
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                    break;
                }
            }//fine if rimuovi creatura



            //CASO CREATURA 
            else if((pmago->campo[i])->tipo == creatura){
                printf("La carta evocata e' di tipo creatura\n");
            }



             //CASO INFLIGGI DANNO
            else if ((pmago->campo[i])->tipo == infliggi_danno){
            do{
            printf("La carta e' di tipo infliggi danno, chi vuoi danneggiare?:\n");
            printf("1]Per danneggiare il mago nemico\n2] Per infliggere danno alle creature nemiche\n");
            scanf("%d", &b);
            clear_buffer();
            switch (b){
            case 1:{
              if(campo_nemico == true){
                pmago2->pv_mago = (pmago2->pv_mago) - ((pmago->campo[i])->pv_carta);
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                printf("Hai danneggiato il mago nemico\n");
                if(pmago2->pv_mago > 1000){
                  pmago2->pv_mago = 0;
                printf("La nuova vita del mago avversario e': %d\n", pmago2->pv_mago);
                }
                else{
                  printf("La nuova vita del mago avversario e': %d\n", pmago2->pv_mago);
                }
              }
              else{
                printf("Non puoi attaccare direttamente il mago nemico dato che ha delle creature in campo\n");
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                break;
              }
                break;}
            case 2:
                if(campo_nemico == false){               
                do{
                printf("Quale creatura dell'avversario vuoi danneggiare?\n[0] - [1] - [2] - [3]\n");
                scanf("%d", &d);
                clear_buffer();
                if (pmago2->campo[d] != NULL){
                  mark2 = 1;
                    if (((pmago->campo[i])->pv_carta) >= ((pmago2->campo[d])->pv_carta)){
                        free(pmago2->campo[d]);
                        pmago2->campo[d] = NULL;
                        free(pmago->campo[i]);
                        pmago->campo[i] = NULL;
                        printf("la Creatura nemica e' stata distutta dalla carta infliggi danno\n");

                    }
                    else if(((pmago2->campo[d])->pv_carta) > ((pmago->campo[i])->pv_carta)){
                        (pmago2->campo[d])->pv_carta = ((pmago2->campo[d])->pv_carta) - ((pmago->campo[i])->pv_carta);
                        free(pmago->campo[i]);
                        pmago->campo[i] = NULL;
                        printf("La creatura nemica e' stata distrutta\n");
                        printf("La nuova vita della creatura nemica e': %d\n", (pmago2->campo[d])->pv_carta);
                    }
                  }
                else{
                  printf("La carta che vuoi danneggiare non e' di tipo creatura\n");
                }}while(mark2 == 0);
                }//fine if campo nemico == false

                else if(campo_nemico == true){
                    printf("Non puoi danneggiare nessuna creatura dato che il campo nemico e' vuoto\n");
                    printf("La carta giocata verra' distrutta\n");
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                }//fine if campo nemico == true
                break;
            
            default:
                printf("Digita corretamente\n");
                break;
            }}while(b < 1 || b > 2);
        }//fine if infliggi danno


        //CASO GUARISCI DANNO
        else if ((pmago->campo[i])->tipo == guarisci_danno){
            printf("La carta giocata e' di tipo guarisci danno, chi vuoi guarire?:\n");
            do{
            printf("1] Curare te stesso\n2] Curare una tua creatura");
            scanf("%d", &b);
            clear_buffer();
            switch (b){
            case 1:
                pmago->pv_mago = (pmago->pv_mago) + ((pmago->campo[i])->pv_carta);
                if(pmago->pv_mago < 100){
                  printf("ti sei curato, la tua nuova vita e': %d\n", pmago->pv_mago);
                }
                else if(pmago->pv_mago > 100){
                  pmago->pv_mago = 100;
                  printf("Hai sforato la vita massima\n");
                  printf("La tua vita e': %d\n", pmago->pv_mago);
                }
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
                break;
            
            case 2:
            if(campo_alleato == false){
                do{
                  do{
                  printf("Quale creatura alleata vuoi curare?\n[0] - [1] - [2] - [3]\n");
                  scanf("%d", &d);
                  clear_buffer();
                  if(d < 0 || d > 3 ){
                    printf("digitare correttamente\n");
                  }}while(d < 0 || d > 3);
                  if(pmago->campo[d] != NULL){
                  if ((pmago->campo[d])->tipo == creatura){
                    mark3 = 1;
                    (pmago->campo[d])->pv_carta = ((pmago->campo[d])->pv_carta) + ((pmago->campo[i])->pv_carta);
                    free(pmago->campo[i]);
                    pmago->campo[i] = NULL;
                    printf("La creatura nello slot %d del campo alleato ha ora %d punti vita\n", d, (pmago->campo[d])->pv_carta);
                  }
                  }
                  else if(pmago->campo[d] == NULL){
                    printf("La carta non e' di tipo creatura\n");
                  }}while(mark3 == 0);
            }

            else if(campo_alleato == true){
                printf("Non ci sono creature nel tuo campo da gioco, non puoi curare nessuno\n");
                printf("La carta verra' quindi distrutta\n");
                free(pmago->campo[i]);
                pmago->campo[i] = NULL;
            }
            break;
            
            default:
                printf("Digita correttamente\n");
                break;
            }}while(b < 1 || b > 2);
        }//fine if guarisci danno


        }//fine if
    }//fine for
    break;


}}

else{
  printf("In quello slot della mano non e' presente nessuna carta\n");
}}while(a < 0 || a > 6);
}//fine if point == 0 
}//fine else
}//fine funzione gioca carta

//funzione stampa campo
void stampa_campo(struct Mago* pmago){
  for (int i = 0; i < 4; i++){
      if (pmago->campo[i] == NULL){
        printf(YEL"slot [%d] del campo libero!\n", i);
      }
      else if(pmago->campo[i] != NULL){
        if ((pmago->campo[i])->tipo == creatura){
          printf(YEL"Carta: tipo [CREATURA] - pv [%d]\n", (pmago->campo[i])->pv_carta);
        }
        if ((pmago->campo[i])->tipo == guarisci_danno){
          printf(YEL"Carta: tipo [GUARISCI DANNO] - pv [%d]\n", (pmago->campo[i])->pv_carta);
        }
        if ((pmago->campo[i])->tipo == infliggi_danno){
          printf(YEL"Carta: tipo [INFLIGGI DANNO] - pv [%d]\n", (pmago->campo[i])->pv_carta);
        }
        if ((pmago->campo[i])->tipo == rimuovi_creatura){
          printf(YEL"Carta: tipo [RIMUOVI CREATURA] - pv [%d]\n"CYN, (pmago->campo[i])->pv_carta);
        }
      }
    }
  }



//funzione stampa mano
void stampa_mano(struct Mago* pmago){
for (int i = 0; i < 6; i++){
  if (pmago->mano[i] == NULL){
      printf(YEL"slot [%d] della mano libera!\n", i);
  }
  else{
    if ((pmago->mano[i])->tipo == creatura){
      printf(YEL"Carta: tipo [CREATURA] - pv [%d]\n", (pmago->mano[i])->pv_carta);
    }
    if ((pmago->mano[i])->tipo == guarisci_danno){
      printf(YEL"Carta: tipo [GUARISCI DANNO] - pv [%d]\n", (pmago->mano[i])->pv_carta);
    }
    if ((pmago->mano[i])->tipo == rimuovi_creatura){
      printf(YEL"Carta: tipo [RIMUOVI CREATURA] - pv [%d]\n", (pmago->mano[i])->pv_carta);
    }
    if ((pmago->mano[i])->tipo == infliggi_danno){
      printf(YEL"Carta: tipo [INFLIGGI DANNO] - pv [%d]\n", (pmago->mano[i])->pv_carta);
    }
  }
 }
}

//funzione pesca
void pesca(struct Mago* pmago){
struct Carta* ptemp = pmago->inizio_mazzo;
if(count_pesca == 0){
  if (ptemp == NULL)
    printf("Il gioco finisce, vince chi ha più PV\n");   
    else
      if (ptemp->carta_successiva == NULL) {
        printf("Ultima carta nel mazzo\n");
        inserisci_mano(pmago, ptemp);
        pmago->inizio_mazzo = NULL;
      }
      else {
        while((ptemp->carta_successiva) -> carta_successiva != NULL){
          ptemp = ptemp -> carta_successiva;
        }
          inserisci_mano(pmago, ptemp -> carta_successiva);
          ptemp -> carta_successiva = NULL;
      }
}
else if(count_pesca == 1){
  printf("Hai gia' pescato in questo turno\n");
}
}


//funzione che inserisce la carte nella mano
void inserisci_mano(struct Mago* pmago, struct Carta* carta_da_inserire) {
  int i = 0;
  for (i = 0; i < 6; i++){
    if (pmago->mano[i] == NULL) {
      pmago->mano[i] = carta_da_inserire;
      break;
    }
  }
  if (i == 6) {
    printf("mano finita, distruggo la carta\n");
    free(carta_da_inserire);
  }

}


//funzione che libera la mano dei maghi
void delete_mano(struct Mago* pmago){
  for(int i = 0; i < 6; i++){
    if(pmago->mano[i] != NULL){
      free(pmago->mano[i]);
      pmago->mano[i] = NULL;
    }
  }
}


//funzione che libera il campo dei maghi
void delete_campo(struct Mago* pmago){
  for(int i = 0; i < 5; i++){
    if(pmago->campo[i] != NULL){
      free(pmago->campo[i]);
      pmago->campo[i] = NULL;
    }
  }
}


//funzione che libera la memoria deallocata dinamicamente
void delete_mazzo(struct Mago* pmago){
    if (pmago->inizio_mazzo == NULL){
      printf("non ci sono carte nel mazzo");
    }
    else{
      struct Carta* ptemp = pmago->inizio_mazzo;
      struct Carta* pscan = ptemp->carta_successiva;
      while(pscan != NULL){
        free(ptemp);
        ptemp = pscan;
        pscan = ptemp->carta_successiva;        
      }
      free(pscan);
      free(ptemp);
      pmago->inizio_mazzo = NULL;
     }    
  }




//effetti in base alla classe scelta dai maghi
void effetto_classe(struct Mago* pmago){
struct Carta* ptemp = pmago->inizio_mazzo;
if (pmago->classe == vita){ 
  while (ptemp != NULL){
    if(ptemp->tipo == creatura){
      ptemp->pv_carta = (ptemp->pv_carta + (int) (ptemp->pv_carta/2));
      ptemp = ptemp->carta_successiva;
    }
    else{
      ptemp = ptemp->carta_successiva;
    }
   } 
 }
if (pmago->classe == tenebre){
  while (ptemp!= NULL){
    if(ptemp->tipo == infliggi_danno){
      ptemp->pv_carta = ptemp->pv_carta * 2;
      ptemp = ptemp->carta_successiva;
    }
    else{
      ptemp = ptemp->carta_successiva;
    }
  } 
}
if (pmago->classe == luce){ 
  while (ptemp != NULL){
    if(ptemp->tipo == guarisci_danno){
      ptemp->pv_carta = (ptemp->pv_carta * 3) + (int) (ptemp->pv_carta/2);
      ptemp = ptemp->carta_successiva;
    }
    else{
      ptemp = ptemp->carta_successiva;
    }
   } 
 }
}


  
//funzione utilizzata per qsort
int cmpfunc(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b);
}



//funzione stampa mazzo
void stampa_mazzo(struct Mago *pmago){
  if (pmago->inizio_mazzo == NULL)
  {
    printf(YEL"non ci sono carte nel mazzo\n");
  }
  else
  {
    struct Carta *ptemp = pmago->inizio_mazzo;
    while (ptemp != NULL)
    {
      if (ptemp->tipo == creatura)
      {
        printf(YEL"Carta: tipo [CREATURA] - Pv [%d]\n", ptemp->pv_carta);
      }
      if (ptemp->tipo == rimuovi_creatura)
      {
        printf(YEL"Carta: tipo [RIMUOVI CREATURA] - Pv [%d]\n", ptemp->pv_carta);
      }
      if (ptemp->tipo == infliggi_danno)
      {
        printf(YEL"Carta: tipo [INFLIGGI DANNO] - Pv [%d]\n", ptemp->pv_carta);
      }
      if (ptemp->tipo == guarisci_danno)
      {
        printf(YEL"Carta: tipo [GUARISCI DANNO] - Pv [%d]\n", ptemp->pv_carta);
      }
      ptemp = ptemp->carta_successiva;

    } 
  }  
} 

//inserisci carta
void inserisci_carta(struct Mago *pmago, int vita_carta){
struct Carta *nuova_carta = (struct Carta*) malloc(sizeof(struct Carta));
  
  nuova_carta->pv_carta = vita_carta;
  nuova_carta->carta_successiva = NULL;
  if (pmago->inizio_mazzo == NULL){
    pmago->inizio_mazzo = nuova_carta;
  }
  else{
    struct Carta *ptemp = pmago->inizio_mazzo;
    while (ptemp->carta_successiva != NULL){
      ptemp = ptemp->carta_successiva;
    }
    ptemp->carta_successiva = nuova_carta;
  }
 
}

//funzione che inserisce il tipo alle carte del mazzo
void inserisci_tipi_carte(struct Mago *pmago){
  struct Carta *ptemp = pmago->inizio_mazzo;
  while (ptemp != NULL)
  {
    x = (rand() % 100 + 1);
    if (x >= 1 && x < 41)
    {
      ptemp->tipo = creatura;
    }
    if (x >= 41 && x < 66)
    {
      ptemp->tipo = rimuovi_creatura;
    }
    if (x >= 66 && x < 86)
    {
      ptemp->tipo = infliggi_danno;
    }
    if (x >= 86 && x <= 100)
    {
      ptemp->tipo = guarisci_danno;
    }
    ptemp = ptemp->carta_successiva;
  }
}

//funzione menu principale
void menu_principale(void){
  printf(CYN"\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("                  _,-'|   \t\t******************************\n");
  printf("               ,-'._  |   \t\t|    -------------------     |\n");
  printf("     .||,      |####| |   \t\t|   | 1] Imposta Gioco  |    |\n");
  printf("     .'',      |####| |   \t\t|   | 2] Combatti       |    |\n");
  printf("    = ,. =      |###| |   \t\t|   | 3] Termina Gioco  |    |\n");
  printf("      ||      ,-'|_|,'`.  \t\t|   | 4] Storia         |    |\n");
  printf("      ||     ,'   `,,. `. \t\t|   | 5] Regole         |    |\n");
  printf("     ,|____,' , ,;'   | | \t\t|   | 6] Trailer Tragic |    |\n");
  printf("     (3||    _/|/'   _| | \t\t|    -------------------     |\n");
  printf("      ||/,-''  | >-'' _,| \t\t******************************\n");
  printf("      ||'      ==  ,-'  ,                                                          \n");
  printf("      ||       |  V | ,|                                                           \n");
  printf("      ||       |    |` |                                                           \n");
  printf("      ||       |    |  |                                                           \n");
  printf("      ||       |    |  |                                                           \n");
  printf("      ||       |    |  |                                                           \n");
  printf("      ||        .==. .=.                                                           \n");
}

//funzione titolo
void titolo(void){
  printf( BCYN".----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.\n");
  printf(     " .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------.  \n");
  printf(     " |  _________   | || |  _______     | || |      ____    | || |    ______    | || |     _____    | || |     ______   | |\n");
  printf(     " | |   ___   |  | || | |_   __  |   | || |     / _  |   | || |  .' ___  |   | || |    |_   _|   | || |   .' ___  |  | |\n");
  printf(     " | |_| | | |_|  | || |   | |__) |   | || |    / / | |   | || | / .'   |_|   | || |      | |     | || |  / .'   |_|  | | \n");
  printf(     " |     | |      | || |   |  __ /    | || |   / ____ |   | || | | |    ___   | || |      | |     | || |  | |         | |\n");
  printf(     " |    _| |_     | || |  _| |  | |_  | || | _/ /   | |   | || | | |__  | |   | || |     _| |_    | || |  | `.___.'|  | |\n");
  printf(     " |   |_____|    | || | |____| |___| | || ||___|  |__|   | || | |________|   | || |    |_____|   | || |   `._____.'  | |\n");
  printf(     " |              | || |              | || |              | || |              | || |              | || |              | |\n");
  printf(     " |'--------------'|| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
  printf(     " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'\n");
  
    
}

//funzione imposta_gioco
void imposta_gioco(void){
  static time_t t;
  srand((unsigned)time(&t));
  mago1.pv_mago = 20;
  mago2.pv_mago = 20;
  int flag1 = false; //usato per i nomi dei maghi
  int flag2 = false; //usato per classe mago1
  int flag3 = false; //usato per classe mago3
  
  do{
    system_clear();
    titolo();
    printf("\n");
    printf( GRN"!! Per proseguire nella creazione dei mazzi si deve !!\ninserire i nomi dei maghi & scegliere la classe dei maghi\n");
    printf("\n");
    printf( "Scegli cosa fare:\n1] imposta nome dei maghi\n2] scegli classe dei due maghi\n");
    scanf("%d", &b);
    while((getchar()) != '\n');
    switch (b){
    case 1:
      do{
        system_clear();
        titolo();
        printf("\n");
        printf(CYN"inserisci nome player1: ");
        scanf("%s", mago1.nome_mago);
        printf(YEL"\nnome player1: %s\n", mago1.nome_mago);
        printf(CYN"\n");
        printf("inserisci nome player2: ");
        scanf("%s", mago2.nome_mago);
        printf(YEL"\nnome player2: %s\n", mago2.nome_mago);
        printf(CYN"\n");
        flag1 = true;
      } while (flag1 == false);
      break;

    case 2:
      do{
        system_clear();
        titolo();
        printf("\n");
        printf(CYN"scegli classe mago del Mago1\n");
        printf("1] Tenebre\n2] Vita\n3] Luce\n");
        scanf("%d", &c);
        while((getchar()) != '\n');
        
        if (c == 1){
          mago1.classe = tenebre;
          printf(YEL"Hai scelto la classe [TENEBRE]\n");
          printf(CYN"\n");
          flag2 = true;
        }

        else if (c == 2){
            mago1.classe = vita;
            printf(YEL"Hai scelto la classe [VITA]\n");
            printf("\n");
            flag2 = true;
        }
          
        else if (c == 3){
            mago1.classe = luce;
            printf(YEL"Hai scelto la classe [LUCE]\n");
            printf("\n");
            flag2 = true;
        }
       

    
        
      }while(flag2 == false || (c < 1 || c > 3));

      do{
        printf("scegli classe mago del Mago2\n");
        printf("1] Tenebre\n2] Vita\n3] Luce\n");        
        scanf("%d", &d);
        while((getchar()) != '\n');
        if (d == 1){
          mago2.classe = tenebre;
          printf(YEL"Hai scelto la classe [TENEBRE]\n");
          printf("\n");
          flag3 = true;
        }
        else if (d == 2){
            mago2.classe = vita;
            printf(YEL"Hai scelto la classe [VITA]\n");
            printf("\n");
            flag3 = true;
        }
        else if (d == 3){
            mago2.classe = luce;
            printf(YEL"Hai scelto la classe [LUCE]\n");
            printf("\n");
            flag3 = true;
        }
          
      }while (flag3 == false || (d < 1 || d > 3));

      break;

    default:
      printf(RED"[ERRORE] Digitare Correttamente...\n");
    break;

  }}while (flag1 == false || flag2 == false || flag3 == false);
  

  do{
    printf(CYN"Digita:\n1] per creare i mazzi\n2] stampa i mazzi\n3] Re-imposta il gioco\n4] Torna al menu\n");
    printf("\n");
    scanf("%d", &a);
    while((getchar()) != '\n');
    switch(a){
    case 1:{
      do{
        printf("Dammi il numero delle carte dei mazzi dei due maghi\n");
        printf("[Max] Carte: 50 | [Min] Carte: 10\n");
        scanf("%hu", &num_carte_mazzo);
        clear_buffer();
        if (num_carte_mazzo >= 10 && num_carte_mazzo <= 50){
          printf("Num Carte dei mazzi: [%hu]\n", num_carte_mazzo);         
        }
        else if (num_carte_mazzo <= 9 || num_carte_mazzo >= 51){
          printf("[Errore] Digitare un numero corretto di carte\n");
        }

      }while (num_carte_mazzo < 10 || num_carte_mazzo > 50);

      int mazzo1[num_carte_mazzo];
      int mazzo2[num_carte_mazzo];

      //riempo gli array con un valore casuale
      for (int i = 0; i < num_carte_mazzo; i++){
        mazzo1[i] = (rand() % 8 + 1);
        mazzo2[i] = (rand() % 8 + 1);
      }
      
      //ordino i valori dei punti vita delle carte
      qsort(mazzo1, num_carte_mazzo, sizeof(int), cmpfunc);
      qsort(mazzo2, num_carte_mazzo, sizeof(int), cmpfunc);



      //inserimento carte in coda al mazzo del mago1
      for (int i = 0; i < num_carte_mazzo; i++){
        inserisci_carta(&mago1, mazzo1[i]);
      }

      //inserimento carte in coda al mazzo del mago2
      for (int i = num_carte_mazzo-1; i >= 0; i--){
        inserisci_carta(&mago2, mazzo2[i]);
      }

      inserisci_tipi_carte(&mago1);
      inserisci_tipi_carte(&mago2);
      
      effetto_classe(&mago1);
      effetto_classe(&mago2);
      mark1 = 1;

      
      break;}

    case 2:{
      //stampa dei due mazzi da gioco
      printf( BCYN"Mazzo di [%s]\n", mago1.nome_mago);
      printf("\n");
      stampa_mazzo(&mago1);
      printf( "------------------------\n");
      printf(BCYN"Mazzo di [%s]\n", mago2.nome_mago);
      printf("\n");
      stampa_mazzo(&mago2);
      break;}

    case 3:{
      delete_mazzo(&mago1);
      delete_mazzo(&mago2); 
      printf("premi invio per continuare\n");
      clear_buffer();
      mark1 = 0;  
      system_clear();
      break;}

    case 4:{
      system("clear");
      break;}
      
    default:{
      printf("[ERRORE]Digitare correttamente...");
      break;}
    }} while ((a < 1 || a > 4) || (a==1 || a == 2));
} 




void combatti(void){ 
  int n = 0;
  int a = 0;

  
  //si effettua il controllo per vedere se il giocatore ha impostato in precedenza il gioco
  if (mark1 == 0){
    printf("[ERRORE] Per giocare si deve prima impostare il gioco\n");
    do{
    printf("Digita:\n1] Per impostare il gioco\n");
    scanf("%d", &n);
    clear_buffer();
    switch (n){
    case 1:
      imposta_gioco();
      break;   
    default:
      printf("[Errore] digita correttamete...\n");
      break;
    }
  }while(n < 1 || n > 1);
}//fine if

if (mark1 == 1){
  printf("Hai impostato correttamente il gioco\n");
}

//generazione numero casuale per decidere chi dei due maghi iniziera per primo
  turno = (rand() % 2+1);

//inserimento carte dal mazzo alla mano da gioco del mago1
for (int i = 0; i < 5; i++){
  pesca(&mago1);
}

//inserimento carte dal mazzo alla mano da gioco del mago2
for (int i = 0; i < 5; i++){
  pesca(&mago2);
}

//while che gestisce i turni dei due maghi
system_clear();
titolo();
while (mago1.pv_mago > 0 && mago2.pv_mago > 0){
if(mago1.inizio_mazzo == NULL){
  printf("Il gioco termina dato che il mago1 non ha piu' carte nel mazzo\n");
  printf("Vince chi ha piu' punti vita\n");
  break;
}
else if(mago2.inizio_mazzo == NULL){
  printf("Il gioco termina dato che il mago2 non ha piu' carte nel mazzo\n");
  printf("Vince chi ha piu' punti vita\n");
  break;
}

if (turno == 1){
  printf("Mago1: [%s] ora e' il tuo turno!\n", mago1.nome_mago);
  do{
  printf("Cosa vuoi fare:\n1]Pesca Carta\n2]Gioca Carta\n3]Attacca\n4]Passa Turno\n5]Stampa Mano\n6]Stampa Campo\n7] Vedi vita Maghi\n");
  printf("\n");
  scanf("%d", &a);
  clear_buffer();
  switch (a){
    case 1:
      pesca(&mago1);
      printf(CYN"\n");
      if(count_pesca == 0){
        count_pesca++;
      }
    break;

    case 2:
      gioca_carta(&mago1, &mago2);
      printf(CYN"\n");
    break;

    case 3:
    if(count_attacca == 4){
        printf("Hai gia' attaccato il max. di volte in un turno\n");
        break;
      }
      attacca(&mago1, &mago2);
      printf(CYN"\n");
    break;

    case 4:
      passa_turno();
      if(point1 == 1){
        point1--;
      }
      if(count_pesca == 1){
        count_pesca--;
      }
      count_attacca = 0;
      system_clear();
      titolo();
      printf(CYN"\n");
    break;

    case 5:
      stampa_mano(&mago1);
      printf(CYN"\n");
    break;

    case 6:
      stampa_campo(&mago1);
      printf(CYN"\n");
    break;

    case 7:
    printf(YEL"Vita mago1 [%s]: %d pv\n", mago1.nome_mago, mago1.pv_mago);
    printf("Vita mago2 [%s]: %d pv\n", mago2.nome_mago, mago2.pv_mago);
    printf(CYN"\n");
    break;


default:
printf("Digita correttamente...\n");
  break;
}}while(a!=4);
}
else{
  printf("Mago2: [%s] ora e' il tuo turno!\n", mago2.nome_mago);
  do{
  printf("Cosa vuoi fare:\n1]Pesca Carta\n2]Gioca Carta\n3]Attacca\n4]Passa Turno\n5]Stampa Mano\n6]Stampa Campo\n7] Vedi vita maghi\n");
  printf("\n");
  scanf("%d", &a);
  clear_buffer();
  switch (a){
  
  case 1:
      pesca(&mago2);
      printf(CYN"\n");
      if(count_pesca == 0){
        count_pesca++;
      }
    break;

    case 2:
      gioca_carta(&mago2, &mago1);
      printf(CYN"\n");
    break;

    case 3:
      if(count_attacca == 4){
        printf("Hai gia' attaccato il max. di volte in un turno\n");
        break;
      }
      attacca(&mago2, &mago1);
      count_attacca++;
      printf(CYN"\n");
    break;

    case 4:
      passa_turno();
      if(point1 == 1){
        point1--;
      }
      if(count_pesca == 1){
        count_pesca--;
      }
      count_attacca = 0;
      system_clear();
      titolo();
      printf(CYN"\n");
    break;

    case 5:
      stampa_mano(&mago2);
      printf(CYN"\n");
    break;

    case 6:
      stampa_campo(&mago2);
      printf(CYN"\n");
    break;

    case 7:
    printf("Vita mago1 [%s]: %d pv\n", mago1.nome_mago, mago1.pv_mago);
    printf("Vita mago2 [%s]: %d pv\n", mago2.nome_mago, mago2.pv_mago);
    printf("\n");
    break;

  default:
    printf("Digita correttamente...\n");
  break;
  
  
  }}while(a!=4);
}

}//fine while

//parte che dichiara chi ha vinto in base hai punti vita
printf("Vita mago1 [%s]: %d pv\n", mago1.nome_mago, mago1.pv_mago);
printf("Vita mago2 [%s]: %d pv\n", mago2.nome_mago, mago2.pv_mago);
if(mago1.pv_mago > mago2.pv_mago){
  printf("Ha vinto il Mago1, Complimenti!!!!\n");
}

else if(mago1.pv_mago < mago2.pv_mago){
  printf("Ha vinto il Mago2, Complimenti!!!\n");
}


else if(mago1.pv_mago == mago2.pv_mago){
  printf("La partita e' finita in pareggio\n");
}

delete_campo(&mago1);
delete_campo(&mago2);
delete_mano(&mago1);
delete_mano(&mago2);
delete_mazzo(&mago1);
delete_mazzo(&mago2);


printf("Digita [INVIO] per tornare al menu' principale");
clear_buffer();
system_clear();

} //fine funzione combatti




void termina_gioco(void){
  delete_campo(&mago1);
  delete_campo(&mago2);
  delete_mano(&mago1);
  delete_mano(&mago2);
  delete_mazzo(&mago1);
  delete_mazzo(&mago2);
  printf("\n");
  printf("Grazie per aver giocato a TRAGIC!!\n");
}

void storia(void){
  printf(YEL"Due maghi si affrontano in un duello uno-contro-uno su una piana ventosa vicina ad Ravnika, la Città delle Gilde.\nGli incantesimi che possono lanciare sono rappresentati da un mazzo di carte ciascuno.\n");
  printf("\n");
  printf(RED"Digita [INVIO] per continuare...\n");
  clear_buffer();
  system_clear();
}

void regole(void){
  printf("Regole Tragic:\n");
  printf(GRN"1]");
  printf(YEL" Prima di iniziare a combattere si deve impostare il gioco\n");
  printf(GRN"2]");
  printf(YEL" Il primo turno di gioco viene deciso in modo casuale\n");
  printf(GRN"3]");
  printf(YEL" Il gioco termina nel momento in cui: uno dei due maghi arriva a 0 punti vita oppure se uno dei due maghi termina le carte nel mazzo\n");
  printf(GRN"4]");
  printf(YEL" le carte rimuovi creatura, guarisci danno e infliggi danno nel momento in cui vengono giocate devono scegliere un bersaglio dato che non possono restare nel campo\n");
  printf(GRN"5]");
  printf(YEL" Le carte creatura quando vengono giocate in campo non devono scegliere un bersaglio. Sceglieranno il bersaglio nel momento in cui attaccheranno\n");
  printf(GRN"6]");
  printf(YEL" Un giocatore in un turno puo' sia pescare che giocare una carta che attaccare (o nessuna di queste)\n");
  printf(GRN"7] ");
  printf(YEL" Quando il gioco termina vince il mago che ha piu' punti vita\n");
  printf(RED"Digita [INVIO] per continuare...\n");
  clear_buffer();
  system_clear();
}
