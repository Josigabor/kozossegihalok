#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include "debugmalloc.h"
#include "beolvasofgv.h"
#include "muveletek.h"
#include "megjelenites.h"
#include "sdl_init.h"

char* vegelevag(char*str, int x){;
        str[x] = 0;
        return str;
}
char* leptetes(char*str, int x){
        return str+x+1;
}


bool string_part_cmp(char* str, char* part){
        char buff[20];
        strcpy(buff,str);
        bool ki = !(strcmp(vegelevag(buff,strlen(part)), part));
        return ki;
}

void nyelvtaniertelmezo(char* nextC, network * n){
    char param1, param2, par1, par2;
    char buff[20];
    strcpy(buff,nextC);
    if(string_part_cmp(buff, "NODE")){
            strcpy(buff,leptetes(buff,strlen("NODE")));
          if(string_part_cmp(buff, "ADD")){
                strcpy(buff,leptetes(buff,strlen("ADD")));
                if(sscanf(buff, "%c %c",&param1, &param2 )==2){
                    if(param1 == 'N'){
                        if(param2 == '0'){
                            addnode(n,false,false);
                        }else if(param2 == 'A'){
                            addnode(n,false,true);
                        }else{printf("Hibas parameterezes");}
                    }else if(param1 =='D'){
                        if(param2 == '0'){
                            addnode(n,true,false);
                        }else if(param2 == 'A'){
                            addnode(n,true,true);
                        }else{printf("Hibas parameterezes");}
                    }else{printf("Hibas parameterezes");}
                }
        }else if(string_part_cmp(buff, "DELETE")){
                strcpy(buff,leptetes(buff,strlen("DELETE")));
                if(sscanf(buff, "%c ",&param1 )==1){
                        if(param1 == '*'){
                            deletenetwork(n); //                          itt még ki kell találni ezt hogy érzékeljük, mármint a törlést
                            return;
                        }else{
                                par1 = param1-'0';
                                if((par1 >=0&&par1<n->esz)){
                                        printf("%d", par1);
                                        deletenode(n, par1);
                                }else{printf("Hibas parameterezes");}
                        }
                    }else{printf("Hibas parameterezes");}
        } else if(string_part_cmp(buff, "SHOW")){
                strcpy(buff,leptetes(buff,strlen("SHOW")));
                if(sscanf(buff, "%c ",&param1 )==1){
                        if(param1 == '*'){
                            show(*(n));
                        }else{
                                par1 = param1-'0';
                                if((par1 >=0&&par1<n->esz)){
                                        showconns(*(n),par1);
                                }else{printf("Hibas parameterezes");}
                        }
                    }else{printf("Hibas parameterezes");}
        }else{printf("Hibas parancs");}
    }else if(string_part_cmp(buff, "CONN")){
            strcpy(buff,leptetes(buff,strlen("CONN")));
            printf("connlayer\n");
            printf("%s\n", buff);
          if(string_part_cmp(buff, "ADD")){
                strcpy(buff,leptetes(buff,strlen("ADD")));
                printf("addlayer\n");
                printf("%s\n", buff);
                if(sscanf(buff, "%c %c",&param1, &param2 )==2){
                    if(param1 == '*' &&param1 == '*' ){
                            addallconn(n);
                    }else{
                    par1 = param1-'0';
                    par2 = param2-'0';
                     if((par1 >=0&&par1<n->esz)&&(par2 >=0&&par2<n->esz)){
                            addconn(n,par1, par2);
                    }else{printf("Hibas parameterezes");}
                    }
                }
            }else  if(string_part_cmp(buff, "DELETE")){
                strcpy(buff,leptetes(buff,strlen("DELETE")));
                printf("addlayer\n");
                printf("%s\n", buff);
                if(sscanf(buff, "%c %c",&param1, &param2 )==2){
                    if(param1 == '*' &&param1 == '*' ){
                            deleteallconn(n);
                    }else{
                    par1 = param1-'0';
                    par2 = param2-'0';
                     if((par1 >=0&&par1<n->esz)&&(par2 >=0&&par2<n->esz)){
                            deleteconn(n,par1, par2);
                    }else{printf("Hibas parameterezes");}
                    }
                }
            }else  if(string_part_cmp(buff, "SHOW")){
                strcpy(buff,leptetes(buff,strlen("SHOW")));
                printf("showlayer\n");
                printf("%s\n", buff);
                if(sscanf(buff, "%c %c",&param1, &param2 )==2){
                    if(param1 == '*' &&param1 == '*' ){
                            allcons(*(n));
                    }else{
                    par1 = param1-'0';
                    par2 = param2-'0';
                     if((par1 >=0&&par1<n->esz)&&(par2 >=0&&par2<n->esz)){
                            isthereconn(*(n),par1, par2);
                    }else{printf("Hibas parameterezes");}
                    }
                }
            }

        }else if(string_part_cmp(buff, "WEB")){
            strcpy(buff,leptetes(buff,strlen("WEB")));
            printf("weblayer\n");
            printf("%s\n", buff);
          if(string_part_cmp(buff, "LOAD")){
                printf("addlayer\n");
                printf("%s\n", buff);
                load(n);
            }else  if(string_part_cmp(buff, "SAVE")){
                    save(*(n));
            }else  if(string_part_cmp(buff, "INV")){
                    inv(n);
            }
        }else{printf("Hibas entitasnev");}

}
