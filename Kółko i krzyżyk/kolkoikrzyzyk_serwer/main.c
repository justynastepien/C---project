#include <stdio.h>
#include <WinSock2.h>
#include <string.h>
#define WYGRANA 1
#define PRZEGRANA -1



int ocena(char pl[3][3])
 {
     for(int i=0;i<3;i++)
    {if(pl[i][0]=='x'&&pl[i][1]=='x'&&pl[i][2]=='x') return WYGRANA;
    if(pl[0][i]=='x'&&pl[1][i]=='x'&&pl[2][i]=='x') return WYGRANA;
    if(pl[0][i]=='o'&&pl[1][i]=='o'&&pl[2][i]=='o') return PRZEGRANA;
    if(pl[i][0]=='o'&&pl[i][1]=='o'&&pl[i][2]=='o') return PRZEGRANA;
    }
    if(pl[0][0]=='x'&&pl[1][1]=='x'&&pl[2][2]=='x') return WYGRANA;
    if(pl[2][0]=='x'&&pl[1][1]=='x'&&pl[0][2]=='x') return WYGRANA;
    if(pl[0][0]=='o'&&pl[1][1]=='o'&&pl[2][2]=='o') return PRZEGRANA;
    if(pl[2][0]=='o'&&pl[1][1]=='o'&&pl[0][2]=='o') return PRZEGRANA;
    return 0;
 }

int druch(char pl[3][3],int i,int *x,int *y)
  {
   int w, wmax,wmin,px,py,rx,ry,brak_ruchu=1;
   w=ocena(pl);
   if(i<=0||w==WYGRANA||w==PRZEGRANA)
     return w;
    if(i%2==0){
       for(px=0,wmax=2*PRZEGRANA;px<3;px++)
         for(py=0;py<3;py++)

               if(pl[px][py]==' '){
                pl[px][py]='x';
                w=druch(pl,i-1,&rx,&ry);
                pl[px][py]=' ';
                if(w>wmax){wmax=w;*x=px;*y=py;}
                brak_ruchu=0;
               }
              if(brak_ruchu==1) return 0;
             else return wmax;
            }

        else{
          for(px=0,wmin=2*WYGRANA;px<3;px++)
            for(py=0;py<3;py++)
               if(pl[px][py]==' '){
                pl[px][py]='o';
                w=druch(pl,i-1,&rx,&ry);
                pl[px][py]=' ';
                if(w<wmin){wmin=w;*x=px;*y=py;}
                brak_ruchu=0;
                }
               if(brak_ruchu==1) return 0;
             else return wmin;
              }
  }




int main ()
{
   int status, dlugosc, end = 0;
    SOCKET gniazdo, gniazdo2;
    struct sockaddr_in srv, cli;
    char buf[9];
    int buf1;

    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 0), &wsadata)) {
        return 0;}

        gniazdo = socket(AF_INET, SOCK_STREAM, 0);
        if (gniazdo == -1)
        {
            printf("Blad Socket\n");
            return 0;
        }

        srv.sin_family = AF_INET;
        srv.sin_port = htons(9000);
        srv.sin_addr.s_addr = inet_addr("192.168.0.11");

        status = bind(gniazdo, (struct sockaddr *)&srv, sizeof srv);
        if (status == -1)
        {
            printf("Blad Bind!\n");
            return 0;
        }

        status = listen(gniazdo, 10);
        if (status == -1)
        {
            printf("Blad Listen\n");
            return 0;
        }
     //------------------------------
  char pl[3][3];
  int x,y,n=0,p=0,o;

    for(int x1=0;x1<3;x1++)
      for(int y1=0;y1<3;y1++)
        pl[x1][y1]=' ';

         while (1) {
            dlugosc = sizeof cli;
            gniazdo2 = accept(gniazdo, (struct sockaddr *)&cli, (int *)&dlugosc);
            if (gniazdo2 == -1)
            {
                printf("Accept error!\n");
                return 0;
            }
            status = recv(gniazdo2, buf, sizeof buf, 0);
            buf[status] = '\0';
              x=buf[0]-'0';
              y=buf[2]-'0';
                pl[x][y]='o';
                n++;
                p=0;
                  for(int i=0;i<3;i++)
                     for(int k=0;k<3;k++)
                         {buf[p]=pl[i][k];
                         p++;}

                        o=ocena(pl);
                     if(o==WYGRANA||o==PRZEGRANA)
                         {
                          sprintf(buf,"W");
                          send(gniazdo2, buf, strlen(buf), 0);
                          closesocket(gniazdo2);
                          break;
                         }
                       if(n==9)
                       {
                          sprintf(buf,"R");
                          send(gniazdo2, buf, strlen(buf), 0);
                          closesocket(gniazdo2);
                          break;
                       }

                       druch(pl,10,&x,&y);
                       pl[x][y]='x'; n++;
                       p=0;
                       for(int i=0;i<3;i++)
                          for(int k=0;k<3;k++)
                         {buf[p]=pl[i][k];
                         p++;}
                       o=ocena(pl);
                     if(o==WYGRANA||o==PRZEGRANA)
                        {
                          sprintf(buf,"P");
                          send(gniazdo2, buf, strlen(buf), 0);
                          closesocket(gniazdo2);
                          break;}
                          send(gniazdo2, buf, strlen(buf), 0);

      }
     closesocket(gniazdo);
     WSACleanup();
}
