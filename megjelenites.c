#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "debugmalloc.h"
#include "muveletek.h"
#include "megjcalc.h"

void megjelen(network n, SDL_Renderer *renderer, int width, int height){
        double pi = 3.1415;
        double fi = (2*pi)/n.esz;
        int x, y, xplus, yplus;
        int r =height*3/20 + width*3/20;
        int rplus = height*4/22 + width*4/22;
        char str[9] = {0};
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        for(int i = 0; i<n.esz;i++){
            //a k�r�k koordin�t�i
            x = round(width/2 + sin(-fi*i+pi)*r);
            y = round(height/2 +cos(-fi*i+pi)*r);
            //a saj�t %-ok koordin�t�i
            xplus = round(width/2 + sin(-fi*i+pi)*rplus)-width/50;
            yplus = round(height/2 +cos(-fi*i+pi)*rplus);
            //saj�t sz�zal�k beolvas�sa
            sprintf(str, "%.1lf %%", prctgown(n, i));
            //kirajzol�s
            if(n.tipus[i]==0){
            filledCircleRGBA(renderer, x, y, 25, 0, 0, 255, 255);
            stringRGBA(renderer, xplus, yplus, str, 0, 0, 255, 255);
            }else if(n.tipus[i]==1){
            filledCircleRGBA(renderer, x, y, 25, 255, 0, 0, 255);
            stringRGBA(renderer, xplus, yplus, str, 255, 0, 0, 255);
            }
            sprintf(str, "%d", i);
            stringRGBA(renderer, x, y, str, 0, 0, 0, 255);
        }
        //kapcsolatok kirajzol�sa
        for(int i =0;i<n.esz-1;i++){
            for(int j = 0; j<n.esz-i-1;j++){
                if(n.conns[i][j]==1){
                    int x1 = round(width/2 + sin(-fi*i+pi)*r);
                    int y1 = round(height/2 +cos(-fi*i+pi)*r);
                    int x2= round(width/2 + sin(-fi*(i+j+1)+pi)*r);
                    int y2 = round(height/2 +cos(-fi*(i+j+1)+pi)*r);
                    lineRGBA(renderer, x1, y1, x2, y2, 0, 255, 0, 200);
                }
            }
        }
        //egy�b kimutat�sik ki�r�sa
        sprintf(str, "%.1lf %%", prctgglobal(n));
        stringRGBA(renderer, 20, 20, str, 255, 255, 255, 255);
        sprintf(str, "%.1lf %%", prctgavg(n));
        stringRGBA(renderer, width-60, 20, str, 255, 255, 255, 255);
        sprintf(str, "%.1lf %%", prctgweighted(n));
        stringRGBA(renderer, width-60, height-20, str, 255, 255, 255, 255);
}
