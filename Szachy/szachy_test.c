#include <stdio.h>
#include <stdlib.h>
#define K 0
#define H 1
#define W 2
#define G 3
#define S 4
#define P 5
#define k_k 6
#define h_k 7
#define w_k 8
#define g_k 9
#define s_k 10
#define p_k 11
#define PUSTE 12
#define WYGRANA 1000
#define PRZEGRANA -1000


int MAX_KIER[] = {8, 8, 4, 4, 8, 3, 8, 8, 4, 4, 8, 3, 0};
int MAX_ODL[] = {2, 8, 8, 8, 2, 2, 2, 8, 8, 8, 2, 2, 0};

int WX[12][8] = {
    {0, 1, 1, 1, 0, -1, -1, -1},
    {0, 1, 1, 1, 0, -1, -1, -1},
    {0, 1, 0, -1},
    {1, 1, -1, -1},
    {1, 2, 2, 1, -1, -2, -2, -1},
    {-1, 0, 1},
    {0, 1, 1, 1, 0, -1, -1, -1},
    {0, 1, 1, 1, 0, -1, -1, -1},
    {0, 1, 0, -1},
    {1, 1, -1, -1},
    {1, 2, 2, 1, -1, -2, -2, -1},
    {-1, 0, 1}};

int WY[12][8] = {
    {-1, -1, 0, 1, 1, 1, 0, -1},
    {-1, -1, 0, 1, 1, 1, 0, -1},
    {-1, 0, 1, 0},
    {-1, 1, 1, -1},
    {-2, -1, 1, 2, 2, 1, -1, -2},
    {-1, -1, -1},
    {-1, -1, 0, 1, 1, 1, 0, -1},
    {-1, -1, 0, 1, 1, 1, 0, -1},
    {-1, 0, 1, 0},
    {-1, 1, 1, -1},
    {-2, -1, 1, 2, 2, 1, -1, -2},
    {1, 1, 1}};

    int plansza[8][8] = {
    {w_k,s_k,g_k,h_k,k_k,g_k,s_k,w_k},
    {p_k,p_k,p_k,p_k,p_k,p_k,p_k,p_k},
    {PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE},
    {PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE},
    {PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE},
    {PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE},
    {P,P,P,P,P,P,P,P},
    {W,S,G,H,K,G,S,W}};



void wypisz(int plansza[8][8]){
    printf("   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n");
    printf("---+---+---+---+---+---+---+---+---+\n");
    for (int i = 0; i < 8; i++)
    {
        printf(" %d |", i);
        for (int k = 0; k < 8; k++)
        {
            int field = plansza[i][k];
            printf(" %s |", figura(field));
        }
        printf("\n---+---+---+---+---+---+---+---+---+\n");
        printf("\n");
    }
}

int figura(int i){
if (i ==K)
        return "K";
    if (i == H)
        return "H";
    if (i == W)
        return "W";
    if (i == G)
        return "G";
    if (i== S)
        return "S";
    if (i == P)
        return "P";

    if (i == k_k)
        return "k";
    if (i == h_k)
        return "h";
    if (i == w_k)
        return "w";
    if (i == g_k)
        return "g";
    if (i == s_k)
        return "s";
    if (i == p_k)
        return "p";
    return " ";
}



int ocena(int pl[8][8])
{
int i,j,w=0;
int oc[]={PRZEGRANA,-9,-5,-4,-3,-1,WYGRANA,9,5,4,3,1,0};
  for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            w += oc[pl[i][j]];
    return w;
}

int druch(int plansza[8][8], int tryb, int *x, int *y, int *k, int *o)
{
 int px_pom,py_pom,k_pom,o_pom,px,py,dx,dy,kierunek,odleglosc;
       int wynik = ocena(plansza),wmax,wmin,ruch_fig,bita_fig;

if (tryb == 0 || wynik > WYGRANA || wynik < PRZEGRANA)
        return wynik;

    if (tryb % 2 == 0)
    {
        for (px = 0, wmax = 100 * PRZEGRANA; px < 8; px++)
            for (py = 0; py < 8; py++)

                if (plansza[px][py] >= 6 && plansza[px][py] <= 12)
                    for (kierunek = 0; kierunek < MAX_KIER[plansza[px][py]]; kierunek++)
                        for (odleglosc = 1; kierunek < MAX_ODL[plansza[px][py]]; odleglosc++)
                        {
                            dx = (odleglosc - 1) * WX[plansza[px][py]][kierunek];
                            dy = (odleglosc - 1) * WY[plansza[px][py]][kierunek];
                            if (odleglosc >= 2 && plansza[px + dx][py + dy] !=PUSTE)
                                break;
                            dx = odleglosc * WX[plansza[px][py]][kierunek];
                            dy = odleglosc * WY[plansza[px][py]][kierunek];

                            if (px + dx >= 0 && px + dx < 8 && py + dy >= 0 && py + dy < 8)

                                if (plansza[px + dx][py + dy] == ' ' || plansza[px + dx][py + dy] <= 5)

                                    if (plansza[px][py] != 11 || (plansza[px + dx][py + dy] == PUSTE && dx == 0) || (plansza[px + dx][py + dy] !=PUSTE && dx != 0))
                                    {
                                        ruch_fig = plansza[px][py];
                                        bita_fig = plansza[px + dx][py + dy];
                                        plansza[px + dx][py + dy] = plansza[px][py];
                                        plansza[px][py] =PUSTE;
                                        if (plansza[px + dx][py + dy] == 11 && py + dy == 7)
                                            plansza[px + dx][py + dy] = 7;
                                        wynik = druch(plansza, tryb - 1, &px_pom, &py_pom, &k_pom, &o_pom);

                                        plansza[px][py] = ruch_fig;
                                        plansza[px + dx][py + dy] = bita_fig;
                                        if (wynik >= wmax)
                                        {
                                            wmax = wynik;
                                            *x = px;
                                            *y = py;
                                            *k = kierunek;
                                            *o = odleglosc;
                                        }
                                    }
                        }
        return wmax;
    }
    else
    {
        for (px = 0, wmin = 100 * WYGRANA; px < 8; px++)
            for (py = 0; py < 8; py++)

                if (plansza[px][py] <= 5)
                    for (kierunek = 0; kierunek < MAX_KIER[plansza[px][py]]; kierunek++)
                        for (odleglosc = 1; odleglosc < MAX_ODL[plansza[px][py]]; odleglosc++)
                        {
                            dx = (odleglosc - 1) * WX[plansza[px][py]][kierunek];
                            dy = (odleglosc - 1) * WY[plansza[px][py]][kierunek];

                            if (odleglosc >= 2 && plansza[px + dx][py + dy] !=PUSTE)
                                break;
                            dx = odleglosc * WX[plansza[px][py]][kierunek];
                            dy = odleglosc * WY[plansza[px][py]][kierunek];

                            if (px + dx >= 0 && px + dx < 8 && py + dy >= 0 && py + dy < 8)

                                if (plansza[px + dx][py + dy] >= 6)

                                    if (plansza[px][py] != 5 || (plansza[px + dx][py + dy] ==PUSTE && dx == 0) || (plansza[px + dx][py + dy] !=PUSTE && dx != 0))
                                    {
                                        ruch_fig = plansza[px][py];
                                        bita_fig = plansza[px + dx][py + dy];
                                        plansza[px + dx][py + dy] = plansza[px][py];
                                        plansza[px][py] = ' ';

                                        if (plansza[px + dx][py + dy] == 5 && py + dy == 0)
                                            plansza[px + dx][py + dy] = 1;
                                        wynik = druch(plansza, tryb - 1, &px_pom, &py_pom, &k_pom, &o_pom);

                                        plansza[px][py] = ruch_fig;
                                        plansza[px + dx][py + dy] = bita_fig;
                                        if (wynik <= wmin)
                                        {
                                            wmin = wynik;
                                            *x = px;
                                            *y = py;
                                            *k = kierunek;
                                            *o = odleglosc;
                                        }
                                    }
                                }
                             return wmin;
                       }
                     }


int main()
{

int ko= 0,r = 0,p=1;
    wypisz(plansza);
    while (1)
    {
        int x = 0, y = 0, k = 0, o = 0,xp,yp,xt,yt;

        printf("TWOJ RUCH Z...DO:\n");
        scanf("%d%d%d%d",&xp,&yp,&xt,&yt);
        plansza[xt][yt]=plansza[xp][yp];
        plansza[xp][yp]=PUSTE;
        wypisz(plansza);

        r=druch(plansza, 6, &x, &y, &k, &o);

        plansza[x + WX[plansza[x][y]][k]][y + WY[plansza[x][y]][k]] = plansza[x][y];
        plansza[x][y] = PUSTE;
        wypisz(plansza);
    }

    return 0;
    }

