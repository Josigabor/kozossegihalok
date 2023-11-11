#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "debugmalloc.h"
#include "beolvasofgv.h"
#include "muveletek.h"
#include "megjelenites.h"
#include "sdl_init.h"




int main(int argc, char *argv[]) {
    /* ablak letrehozasa */
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width = 1140, height =900;
    TTF_Font *font;
    char tipus[] = "C:\\Windows\\Fonts\\Arial.ttf";
    sdl_init(width, height, tipus, &window, &renderer, &font);
    char nextC[20] ={0}; // következő parancsot tartalmazó string
    size_t hossz = 20;
    SDL_Rect teglalap = {20, height-40, 300, 40};
    SDL_Color fekete = {0, 0, 0};
    SDL_Color feher = {255, 255, 255};
    network x = ures();

    //network x = load();
    /*
    network x = ures();
    show(x);
    addnode( &x, true,true);
    show(x);
    addnode( &x, true,true);
    show(x);
    deletenode(&x, 1);
    show(x);
    deletenode(&x, 1);
    show(x);


    deleteconn(&x,0,1);
    show(x);
    addconn(&x, 1,0);
    show(x);
    //
    //show(x);

    */
    megjelen(x, renderer, width, height);
    SDL_RenderPresent(renderer);

    /* varunk a kilepesre */
    SDL_Event ev;
    char param1 = 0, param2 = 0;
    //int numparam = 0;
    char task[20] = {0};
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        printf("bent\n");
        input_text(nextC, hossz, teglalap, fekete,  feher, font , renderer);
        if(strstr(nextC,"NODEADD")==nextC){
            printf("bent2\n");
            if(sscanf(nextC, "%s %c %c",task, &param1, &param2 )==3){
                if(param1 == 'N'){
                    if(param2 == '0'){
                        addnode(&x,false,false);
                    }else if(param2 == 'A'){
                        addnode(&x,false,true);
                    }else{printf("Hibas parameterezes");}
                }else if(param1 =='D'){
                    if(param2 == '0'){
                        addnode(&x,true,false);
                    }else if(param2 == 'A'){
                        addnode(&x,true,true);
                    }else{printf("Hibas parameterezes");}
                }else{printf("Hibas parameterezes");}
            }

        }
        show(x);
        megjelen(x, renderer, width, height);
        SDL_RenderPresent(renderer);
    }//-----end of the main while
    deletenetwork(&x);//program végén elvégezzük a memória felszabadítást
    /* az elvegzett rajzolasok a kepernyore */
    TTF_CloseFont(font);


    /* ablak bezarasa */
    SDL_Quit();

    return 0;
}
