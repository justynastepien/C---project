
#include <stdio.h>
#include <stdlib.h>

typedef struct el_drzewa
{
    int w;
    struct el_drzewa *lewy, *prawy;
}el_drzewa;

void wstaw(struct el_drzewa **pocz, double war)
{
    struct el_drzewa *nowy, *ws = *pocz, *nastepny;
    nowy = malloc(sizeof(struct el_drzewa));
    nowy->w = war;
    nowy->lewy = nowy->prawy = 0;
    if (ws == 0)
        *pocz = nowy;
    else
    {
        while (1)
        {
            if (war < ws->w)
            {
                if (ws->lewy == 0)
                {
                    ws->lewy = nowy;
                    break;
                }
                else
                    ws = ws->lewy;
            }
            else
            {
                if (ws->prawy == 0)
                {
                    ws->prawy = nowy;
                    break;
                }
                else
                    ws = ws->prawy;
            }
        }
    }
}

void wypisz(struct el_drzewa *pocz)
{
    if (pocz == 0)
        return;
    wypisz(pocz->lewy);
    printf(" %d ", pocz->w);
    wypisz(pocz->prawy);
}

struct el_drzewa *w_glab(struct el_drzewa *pocz, int war)
{
    if (pocz == 0)  {printf("brak %d w drzewie\n", war); return;}
    if (pocz->w == war) {printf("Wartosc %d jest w drzewie\n",war);
        return pocz;}
    else if (pocz->w > war)
        w_glab(pocz->lewy, war);
    else
        w_glab(pocz->prawy, war);
}

int main(void)
{
    el_drzewa *el_drzewa;
    el_drzewa = NULL;
    wstaw(&el_drzewa, 5);
    wstaw(&el_drzewa, 1);
    wstaw(&el_drzewa, 2);
    wstaw(&el_drzewa, 8);
    wstaw(&el_drzewa, 3);
    wypisz(el_drzewa);
    printf("\n");
    w_glab(el_drzewa, 1);
    w_glab(el_drzewa, 4);

    return 0;
}
