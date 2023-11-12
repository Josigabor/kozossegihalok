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

void addallconn(network*n);

void deleteconn(network * n, int x, int y);

void deleteallconn(network*n);

void showconns(network n, int x);

void load(network * n);

void save(network n);

void inv(network * n);

void deletenetwork(network * n);

void isthereconn(network n, int x, int y);

void allcons(network n);
#endif // MUVELETEK_H_INCLUDED
