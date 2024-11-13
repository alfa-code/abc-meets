#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 4096

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    const char *hostname = "localhost";
    const char *port = "8080";
    const char *path = "/";

    struct addrinfo hints, *res;
    int sockfd;

    // Установка параметров для адреса
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // Получаем адрес сервера
    if (getaddrinfo(hostname, port, &hints, &res) != 0)
    {
        error("Ошибка получения адреса сервера");
    }

    // Создаем сокет
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0)
    {
        error("Ошибка создания сокета");
    }

    // Подключаемся к серверу
    if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0)
    {
        error("Ошибка подключения к серверу");
    }

    // Формируем HTTP GET запрос
    char request[BUFFER_SIZE];
    snprintf(request, sizeof(request),
             "GET %s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Connection: close\r\n\r\n",
             path, hostname);

    // Отправляем запрос
    if (send(sockfd, request, strlen(request), 0) < 0)
    {
        error("Ошибка отправки запроса");
    }

    // Получаем и выводим ответ
    char response[BUFFER_SIZE];
    ssize_t bytes_received;
    while ((bytes_received = recv(sockfd, response, sizeof(response) - 1, 0)) > 0)
    {
        response[bytes_received] = '\0';
        printf("%s", response);
    }

    if (bytes_received < 0)
    {
        error("Ошибка получения данных");
    }

    // Закрываем сокет
    close(sockfd);
    freeaddrinfo(res);
    return 0;
}
