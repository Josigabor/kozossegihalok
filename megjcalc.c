#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "debugmalloc.h"
#include "muveletek.h"


int diffelemek(network n){
    int out =0;
        for(int i = 0; i<n.esz; i++){
            if(n.tipus[i] == 1){out++;};
        }
        return out;
}

int numofconns(network n, int x){
        int cnt = 0;
        for(int i =0;i<x; i++){
            for(int j =0; j< n.esz-1-i;j++){
                    if(i+j+1==x && n.conns[i][j]==1){
                            cnt++;
                    }
            }
        }
        for(int i =0; i<n.esz-1-x;i++){
            if(n.conns[x][i]==1){
                cnt++;
            }
        }
        return cnt;
}

double prctgown(network n, int x){
    int cnt = 0, diff = 0;;
        for(int i =0;i<x; i++){
            for(int j =0; j< n.esz-1-i;j++){
                    if(i+j+1==x && n.conns[i][j]==1){
                            cnt++;
                            if(n.tipus[i]==1){
                                diff++;
                            }
                    }
            }
        }
        for(int i =0; i<n.esz-1-x;i++){
            if(n.conns[x][i]==1){
                cnt++;
            if(n.tipus[x+i+1]==1){
                diff++;
            }
            }
        }
        if(cnt>0){
        return diff/(double)cnt*100;
        }
        return 0.0;
}

double prctgweighted(network n){
        double accu =0,connaccu = 0;
        for(int i =0;i<n.esz; i++){
                connaccu += numofconns(n,i);
                accu += numofconns(n,i) * prctgown(n,i);
        }
        if(connaccu>0){
        return accu/connaccu;
        }else{
            return 0;
        }
}

double prctgavg(network n){
        double accu =0;
        for(int i =0;i<n.esz; i++){
                accu += prctgown(n,i);
        }
        return accu/n.esz;
}

double prctgglobal(network n){
    int diff = 0;;
        for(int i = 0; i<n.esz;i++){
            if(n.tipus[i] ==1){diff++;};
        }
    if(diff>0){
        return diff/(double)n.esz*100;
    }
    return 0.0;
}
