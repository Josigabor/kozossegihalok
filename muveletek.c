#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include "muveletek.h"



network ures(){
    network ures;
    ures.esz =2;
    ures. conns = malloc((ures.esz-1) * sizeof(int*));
    ures.conns[0] = (int*) calloc(ures.esz-1, sizeof(int));
    ures.tipus = calloc(ures.esz, sizeof(int));
     return ures;
}

void show(network n){
     for(int i =0;i<n.esz-1;i++){
            printf("%d. NODE: %d --- ",i, n.tipus[i]);
            for(int j = 0; j<n.esz-i-1;j++){
                printf("%d ", n.conns[i][j]);
                }
                printf("\n");
            }

    printf("%d. NODE: %d\n",n.esz-1,n.tipus[n.esz-1]);
}

void addnode(network * n, bool t, bool c){// ha t igaz akkor megkülömböztetett lesz az elem, ha c igaz akkor minden kapcsolatot megteremt,
        n->esz++;
        n->conns = realloc(n->conns,n->esz * sizeof(int*));
        for (int i = 0; i < n->esz-2; i++){
            n->conns[i] = realloc(n->conns[i],(n->esz-i-1) * sizeof(int));
            if(c){
            n->conns[i][n->esz-i-2]=1;
            }else{
            n->conns[i][n->esz-i-2]=0;
            }
        }
        n->conns[n->esz-2] = (int*) calloc(1, sizeof(int));
        if(c){
            n->conns[n->esz-2][0]=1;
        }
        n->tipus = realloc(n->tipus, n->esz * sizeof(int));
        if(t){
            n->tipus[n->esz-1] = 1;
        }else{
            n->tipus[n->esz-1] = 0;
        }
}

void deletenode(network * n, int x){
    int * ptr;
        n->esz--;
        for(int i = 0; i<n->esz; i++){
            if(i==x){
                ptr = n->conns[x];
            }
            if( i>=x){
                n->conns[i] = n->conns[i+1];
            }

        }
        free(ptr);
        n->conns = realloc(n->conns,n->esz * sizeof(int*));
        for (int i = 0; i < n->esz-1; i++){
            for(int j = 0; j<n->esz-1-i;j++){
            if( i<x && i+j+1>=x){
                n->conns[i][j] = n->conns[i][j+1];
            }
            }
            if(i<x){
            n->conns[i] = realloc(n->conns[i],(n->esz-i+1) * sizeof(int));
            }
            if(i>=x){
                n->conns[i] = realloc(n->conns[i],(n->esz-i+1) * sizeof(int));
            }
        }
        for(int i = 0; i<n->esz; i++){
            if( i>=x){
                n->tipus[i] = n->tipus[i+1];
            }
        }
        n->tipus = realloc(n->tipus, n->esz * sizeof(int));
}

void addconn(network * n, int x, int y){
    if(x==y){
        printf("Önmagával nem kapcsolható egy elem.");
        return;
    }
    if(y>x){
        n->conns[x][y-x-1] = 1;
    }else if(x>y){
        n->conns[y][x-y-1] = 1;
    }
}
void deleteconn(network * n, int x, int y){
    if(x==y){
        printf("Önmagával nem kapcsolható egy elem.");
        return;
    }
    if(y>x){
        n->conns[x][y-x-1] = 0;
    }else if(x>y){
        n->conns[y][x-y-1] = 0;
    }
}


network load(){
        FILE* save;
        network n;
        save = fopen("mentes.txt", "r");
        if (save != NULL) {
            fscanf(save,"%d\n", &n.esz);
            char* str = malloc((n.esz+2)*sizeof(char));
            n.tipus = malloc((n.esz+2)*sizeof(int));
            fgets(str,n.esz+2,save);
            for(int i = 0; i<n.esz;i++){
                if(str[i]=='0'){
                        n.tipus[i] = 0;
                    }else if(str[i]=='1'){
                        n.tipus[i] = 1;
                    }
            }
            n.conns =malloc((n.esz-1) * sizeof(int*));
            for(int i =0;i<n.esz-1;i++){
                n.conns[i] = malloc((n.esz-i)*sizeof(int));
                fgets(str,n.esz-i+1,save);
                for(int j =0; j<n.esz-i-1;j++){
                    if(str[j]=='0'){
                        n.conns[i][j] = 0;
                    }else if(str[j]=='1'){
                        n.conns[i][j] = 1;
                    }
                }
            }
            fclose(save);
            free(str);
            return n;
        }
        else {
            perror("Nem sikerült megnyitni a fájlt");
            return ures();
    }
}

void save(network n){
        FILE* save;
        save = fopen("mentes.txt", "w");
            fprintf(save,"%d\n", n.esz);
            for(int i = 0; i<n.esz;i++){
                fprintf(save, "%d",n.tipus[i]);
            }
            fprintf(save,"\n");
            for(int i =0;i<n.esz-1;i++){
                for(int j =0; j<n.esz-i-1;j++){
                    fprintf(save, "%d", n.conns[i][j]);
                }
                fprintf(save,"\n");
            }
            fclose(save);

}

void inv(network * n){
        for(int i = 0;i<n->esz;i++){
            for(int j = 0;j<n->esz-i-1;j++){
                if(n->conns[i][j] == 0){
                    n->conns[i][j] = 1;
                }else if(n->conns[i][j] == 1){
                    n->conns[i][j] = 0;
                }
            }
        }
}

void deletenetwork(network * n){
        for(int i =0; i< n->esz-1;i++){ // felszabadítás a bezárás elõtt
        free(n->conns[i]);
    }
    free(n->tipus);
    free(n->conns);
    n->esz = 0;
}
