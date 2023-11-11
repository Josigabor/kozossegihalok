#ifndef MUVELETEK_H_INCLUDED
#define MUVELETEK_H_INCLUDED

typedef struct network{
        int ** conns;
        int * tipus;
        int esz;

}network;

network ures();

void show(network n);

void addnode(network * n, bool t, bool c);

void deletenode(network * n, int x);

void addconn(network * n, int x, int y);

void deleteconn(network * n, int x, int y);

network load();

void save(network n);

void inv(network * n);

void deletenetwork(network * n);
#endif // MUVELETEK_H_INCLUDED
