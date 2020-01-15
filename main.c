//
//  main.c
//  projekti2
//
//  Created by Juan Fuentes on 01/04/2019.
//  Copyright © 2019 Juan Fuentes. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projekti.h"

//testi Githubia varten.


int luomaa(olympia* valtio, int num,char* nimi){
    int k = 0;
    int h = 0;
    int p = 0;
    valtio[num].kulta = k;
    valtio[num].hopea = h;
    valtio[num].pronssi = p;
    strcpy(valtio[num].maa, nimi);
    num++;
    return num;
}


void lisaamitalli(olympia* uusimaa,int k,int h,int p, char* nimi){
    int g = 0;
    int b = 0;
    while(uusimaa[g].maa[0] != 0){
        if(strcmp(uusimaa[g].maa, nimi) == 0){
            uusimaa[g].kulta = (uusimaa[g].kulta + (k));
            uusimaa[g].hopea = (uusimaa[g].hopea + (h));
            uusimaa[g].pronssi = (uusimaa[g].pronssi + (p));
            printf("Lisäys onnistui\n");
            return;
        }
        
        else{
            b++;
        }
        
        g++;
    }
    if(b == g){
        printf("Maata ei löydy\n");
    }
}

int tallennalista(char* filename, olympia* uusimaa){
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("ei onnistunut\n");
        return -1;
    }
    if (ferror(fp)) {
        printf("ei onnistunut\n");
        return -1;
    }
    int i;
    for(i=0; uusimaa[i].maa[0]!=0 ;i++) {
        fprintf(fp, "%s %d %d %d\n", uusimaa[i].maa, uusimaa[i].kulta, uusimaa[i].hopea,uusimaa[i].pronssi);
    }
    printf("Tallennus onnistui\n");
    fclose(fp);
    return 0;
    
}





void rearrange(olympia* uusimaa){
    int g = 0;
    while(uusimaa[g].maa[0] !=0){
        int i = 0;
        while(uusimaa[i+1].maa[0] != 0){
            if(uusimaa[i].kulta < uusimaa[i+1].kulta){
                olympia uus = uusimaa[i];
                uusimaa[i] = uusimaa[i+1];
                uusimaa[i+1] = uus;
        }
            if(uusimaa[i].kulta == uusimaa[i+1].kulta && uusimaa[i].hopea < uusimaa[i+1].hopea){
                olympia uus = uusimaa[i];
                uusimaa[i] = uusimaa[i+1];
                uusimaa[i+1] = uus;
            }
            if(uusimaa[i].kulta == uusimaa[i+1].kulta && uusimaa[i].hopea == uusimaa[i+1].hopea && uusimaa[i].pronssi < uusimaa[i+1].pronssi){
                olympia uus = uusimaa[i];
                uusimaa[i] = uusimaa[i+1];
                uusimaa[i+1] = uus;
            }
            i++;
        }
        g++;
    }
}

void printmaa(olympia* uusimaa){
    int g = 0;
    rearrange(uusimaa);
    while(uusimaa[g].maa[0] != 0){
        printf("%s %d %d %d\n",uusimaa[g].maa,uusimaa[g].kulta, uusimaa[g].hopea,uusimaa[g].pronssi);
        g++;
    }
}

olympia* luetiedosto(char* filename, olympia* uusimaa){
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Tiedostoa ei ole\n");
        return NULL;
    }
    if (ferror(fp)) {
        printf("Tiedostoa ei ole\n");
        return NULL;
    }
    
    char nimi[20];
    int a , b ,c;
    int k = 0;
    free(uusimaa);
    uusimaa = malloc(sizeof(olympia));
    while(fscanf(fp, "%s %d %d %d",nimi,&a,&b,&c) == 4){
        uusimaa = realloc(uusimaa, sizeof(olympia)*(2+k));
        uusimaa[k].kulta = a;
        uusimaa[k].hopea = b;
        uusimaa[k].pronssi = c;
        strcpy(uusimaa[k].maa, nimi);
        k++;
    }
    uusimaa[k].maa[0] = 0;
    printmaa(uusimaa);
    fclose(fp);
    return uusimaa;
}



void suoritus(olympia* uusimaa){
    int Q = 0;
    int f = 0;
    while(Q == 0){
        char a = '\0';
        scanf("%c",&a);
            if(a != 'A' && a != 'Q' && a != 'W' && a != 'O' && a != 'L' && a != 'M'){
            printf("Syötä jokin yllä mainituista merkeistä\n");
            }
            else if(a == 'A'){
                uusimaa = realloc(uusimaa, sizeof(olympia)*(f+2));
                char valtio[20];
                scanf("%s",valtio);
                luomaa(uusimaa, f, valtio);
                uusimaa[f+1].maa[0] = 0;
                printf("Lisäys onnistui\n");
                f++;
            }
            else if(a == 'M'){
                int k = 0, h = 0, p = 0;
                char valtio[20];
                scanf("%s %d %d %d",valtio,&k,&h,&p);
                lisaamitalli(uusimaa, k, h, p, valtio);
                
            
            }
            else if(a == 'Q'){
                printf("Lopetetaan ohjelma\n");
                Q++;
            }
            else if (a == 'L'){
                printmaa(uusimaa);
            }
            else if(a == 'W'){
                char tiedosto[20];
                scanf("%s",tiedosto);
                tallennalista(tiedosto, uusimaa);
            }
            else if(a == 'O'){
                char nimi[20];
                scanf("%s",nimi);
                uusimaa = luetiedosto(nimi, uusimaa);
                
        }
    }
    
    if(uusimaa != NULL){
    free(uusimaa);
    }
}


void ohjeet(void){
    printf("Lisää maa kirjoittamalla ensin A\n");
    printf("Päivitä mitalit kirjoittamalla ensin M\n");
    printf("Tulosta taulukko kirjoittamalla ensin L\n");
    printf("Tallenna taulukkoon kirjoittamalla ensin W\n");
    printf("Lataa taulukko kirjoittamalla ensin O\n");
    printf("Poistu ohjelmasta kirjoittamalla ensin Q\n");
}

void freememory(olympia* uusimaa){
    int i = 0;
    while(uusimaa[i].maa[0] != 0){
        free(uusimaa);
    }
}


int main(void) {
    ohjeet();
    olympia *uusimaa;
    uusimaa = malloc(sizeof(olympia));
    uusimaa->maa[0] = 0;
    suoritus(uusimaa);
    return 0;
}
