#include <stdio.h>
#include <WinSock2.h>
#include <string.h>

void wypisz(char pl[9]){

  for(int i=0;i<9;i++)
        {printf(" %c ",pl[i]);
         if(i==2||i==5)
          printf("\n--+--+--\n");}

      printf("\n");

}




int main()
{
    int status, dlugosc, nr = 0, end = 1;
    SOCKET gniazdo, gniazdo2;
    struct sockaddr_in srv, cli;
    char buf[200];

    WSADATA wsadata;

    if (WSAStartup(MAKEWORD(2, 0), &wsadata)) {
        return 0;}
   while(1)
    {gniazdo = socket(AF_INET, SOCK_STREAM, 0);
        if (gniazdo == -1)
        {
            printf("Blad socket\n");
            return 0;
        }

        srv.sin_family = AF_INET;
        srv.sin_port = htons(9000);
        srv.sin_addr.s_addr = inet_addr("192.168.0.11");

        status = connect(gniazdo, (struct sockaddr *)&srv, sizeof srv);

        if (status < 0)
        {
            printf("Blad connect\n");
            return 0;
        }
            printf("TWOJ RUCH:");
        fgets(buf, sizeof buf, stdin);
        printf("%s",buf);
        send(gniazdo, buf, strlen(buf), 0);
        status=recv(gniazdo, buf, sizeof buf, 0);
         buf[status] = '\0';
         if(buf[0]=='R')
            {printf("REMIS!"); closesocket(gniazdo);break;}

         if(buf[0]=='P')
            {printf("RRZEGRANA!"); closesocket(gniazdo);break;}
         if(buf[0]=='W')
            {printf("WYGRANA!"); closesocket(gniazdo);break;}
          wypisz(buf);


        closesocket(gniazdo);}
        WSACleanup();
}
