#include <stdio.h>
#include "fonction.h"

int main() {
    printf("Hello, World!\n");
    T_ABR *a= malloc(sizeof(T_ABR));
    T_ABR *g= malloc(sizeof(T_ABR));
    T_ABR *d= malloc(sizeof(T_ABR));

    strcpy(g->date, "2021-05-02");
    strcpy(a->date, "2021-06-02");
    strcpy(d->date, "2021-07-02");

    T_ABR * s = search_geq(a, "2021-07-02");

    printf("%s", s->date);
    return 0;
}
