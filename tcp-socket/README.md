# Интерфейс Socket

Этот раздел создан для изучения сетевого интерфейса Socket.

В директории **tcp-client** находится код на **C** - это простейший **http** клиент.

**Задача 1**: Перейдите в директорию **tcp-client** и следуя инструкциям в файле README.md скомпилируйте свой http клиент.

В директории **python-server** находится простейший http сервер.

**Задача 2**: Следуя инструкциям в файле README.md, запустите сервер на Python и протестируйте работу в браузере. Остановите сервер.

В директории **node-serverr** находится простейший http сервер. Просто на другом языке - для вариативности.

**Задача 3**: Следуя инструкциям в файле README.md, запустите сервер на NodeJS и протестируйте работу в браузере. Остановите сервер.

**Задача 4**: Запустите сервер на Python. Используя скомпилированный http клиент, обратитесь сначала к серверу на Python.
Затем погасите сервер на Pytnon и запустите сервер на NodeJS. Используя скомпилированный http клиент, обратитесь к серверу на NodeJS. Остановите сервер. Удедитесь что в ответах от обоих серверов возвращался текст соотвтетствующих веб-страниц.

**Задача 5**: Изучите код программы **http_client.c**. Обратите внимание на создание интерфейса сокета (socket), создание подключения (connect) и запрос (send).