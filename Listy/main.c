#include <stdio.h>
#include <stdlib.h>

struct el_listy
{
    int w;
    struct el_listy *nast;
};

void dopisz(struct el_listy **pocz, double war)
{
    struct el_listy *nowy,
        *ww = *pocz;
    nowy = malloc(sizeof(struct el_listy));
    nowy->w = war;
    nowy->nast = 0;
    if (ww == 0)
        *pocz = nowy;
    else
    {
        while (ww->nast)
            ww = ww->nast;
        ww->nast = nowy;
    }
}

void wypisz(struct el_listy *pocz)
{
    while (pocz)
    {
        printf("%d ", pocz->w);
        pocz = pocz->nast;
    }
    printf("\n");
}

void wstaw(struct el_listy **pocz, double war)
{
    struct el_listy *nowy,
        *ww = *pocz;
    nowy = malloc(sizeof(struct el_listy));
    nowy->w = war;
    if (ww == 0 || war < ww->w)
    {
        nowy->nast = ww;
        *pocz = nowy;
    }
    else
    {
        while (ww->nast != 0 && war > ww->nast->w)
            ww = ww->nast;
        nowy->nast = ww->nast;
        ww->nast = nowy;
    }
}

void usun(struct el_listy **pocz, double war)
{
    struct el_listy *pom,
        *ww = *pocz;
    if (ww == 0)
        return;
    if (war == ww->w)
    {
        pom = ww;
        *pocz = ww->nast;
        free(pom);
    }
    else
    {
        while (ww->nast != 0 && war != ww->nast->w)
            ww = ww->nast;
        if (ww->nast != 0 && war == ww->nast->w)
        {
            pom = ww->nast;
            ww->nast = ww->nast->nast;
            free(pom);
        }
    }
}

void znajdz(struct el_listy *pocz, double war)
{
    while (pocz && pocz->w != war)
        pocz = pocz->nast;
    if (pocz->w == war)
{ printf("W liscie znajduje sie %d\n",war); return; }
         printf("Nie znaleziono %d\n",war);
    return *pocz;
}

struct el_listy *kopiuj(struct el_listy *pocz)
{
    struct el_listy *nowy,
        *poprzedni,
        *lista2 = 0,
        *ww = pocz;
    while (pocz)
    {
        nowy = malloc(sizeof(struct el_listy));
        nowy->w = pocz->w;
        if (lista2 == 0)
            lista2 = nowy;
        else
            poprzedni->nast = nowy;
        poprzedni = nowy;
        pocz = pocz->nast;
    }
    if (lista2)
        nowy->nast = 0;
    return lista2;
}

struct el_listy *dodaj(struct el_listy *pocz1, struct el_listy *pocz2)
{
    struct el_listy *kop1,
        *kop2,
        *pom;
    kop1 = kopiuj(pocz1);
    kop2 = kopiuj(pocz2);
    if (kop1 == 0)
        return kop2;
    pom = kop1;
    while (pom->nast)
        pom = pom->nast;
    pom->nast = kop2;
    return kop1;
}

void zwolnij(struct el_listy *pocz)
{
    struct el_listy *pom,
        *ww = pocz;
    while (ww->nast)
    {
        pom = ww;
        ww = ww->nast;
        free(pom);
    }
}

int main(void)
{
    struct el_listy *ws = 0;
    dopisz(&ws, 12);
    dopisz(&ws, 42);
    dopisz(&ws, 8);
    dopisz(&ws, 6);
    dopisz(&ws, 2);
    wypisz(ws);

    usun(&ws,6);
     wypisz(ws);
    struct el_listy *ws2 = kopiuj(ws);
    wypisz(ws2);
    dopisz(&ws2, 24);
    dopisz(&ws2, 4);

    wypisz(ws2);
    znajdz(&ws,8);

    printf("\n");
    return 0;
}
