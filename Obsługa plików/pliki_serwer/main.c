#include <stdio.h>
#include <WinSock2.h>
#include <string.h>

int main(void)
{

    int status, dlugosc;
    SOCKET gniazdo, gniazdo2;
    struct sockaddr_in srv, cli;
    char buf[1025];
    WSADATA wsadata;

    if (WSAStartup(MAKEWORD(2, 0), &wsadata)) {
        return 0;
    }
    while (1)
    {
        gniazdo = socket(AF_INET, SOCK_STREAM, 0);
        if (gniazdo == -1)
        {
            printf("Blad socket\n");
            return 0;
        }

        srv.sin_family = AF_INET;
        srv.sin_port = htons(9000);
        srv.sin_addr.s_addr = inet_addr("192.168.0.11");

        status = bind(gniazdo, (struct sockaddr *)&srv, sizeof srv);
        if (status == -1)
        {
            printf("Blad bind\n");
            return 0;
        }

        status = listen(gniazdo, 10);
        if (status == -1)
        {
            printf("Blad listen\n");
            return 0;
        }

        while (1)
        {
            dlugosc = sizeof cli;
            gniazdo2 = accept(gniazdo, (struct sockaddr *)&cli, (int *)&dlugosc);
            if (gniazdo2 == -1)
            {
                printf("Blad accept\n");
                return 0;
            }
            status = recv(gniazdo2, buf, sizeof buf, 0);
            buf[status] = '\0';
            printf("%s", buf);

            FILE *plik;
            plik = fopen(strtok(buf, "\n"), "r");

            if (plik == 0) {
                sprintf(buf, "Blad otwierania pliku\n");
                send(gniazdo2, buf, strlen(buf), 0);
                closesocket(gniazdo2);
                continue;
            }
            fgets(buf, 1024, (FILE*)plik);
            fclose(plik);

            send(gniazdo2,buf, strlen(buf), 0);
            closesocket(gniazdo2);
            break;
        }
        closesocket(gniazdo);
    }
    return 0;
}
