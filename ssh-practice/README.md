# Практика к докладу о SSH Secure Shell

Запись встречи ABC (Alfa Brain Community) от 05.12.24

Тема: SSH Secure Shell

Ссылка на Youtube: <https://www.youtube.com/watch?v=x92tPyBkmUk>
Ссылка на облако если youtube не работает: <https://disk.yandex.ru/i/_9mTmw2gLd7r0w>

## Практика Level 1

Для практики использования SSH нам понадобятся виртуальные машины. Но чтобы не тратить деньги на реальные облачные вычисления и не запускать полноценные тяжеловесные VM - мы воспользуемся Docker, а именно Docker Compose.

Использование Docker Compose для создания нескольких контейнеров позволяет быстро и удобно настроить окружение для практики с SSH. Вы можете создать сценарии для подключения к разным контейнерам, настройки ключей SSH, изменения портов и других связанных задач.

В текущей директории находится файл `docker-compose.yml` откройте его в текстовом редакторе и прочитайте содержимое.

## Пошаговое руководство для практики

### Запуск контейнеров

```sh
docker-compose up -d
```

Это создаст и запустит два SSH-сервера:

- ssh_server1 на порту 2222
- ssh_server2 на порту 2223

### Подключение к серверам

Попробуйте подключиться к каждому из серверов:

```sh
ssh root@localhost -p 2222
```

Пароль: `rootpassword1`

```sh
ssh root@localhost -p 2223
```

Пароль: `rootpassword2`

### Просмотр логов

Логи можно просматривать с помощью команды:

```sh
docker logs ssh_server1
```

### Остановка окружения

После завершения практики:

```sh
docker-compose down
```

## Практика Level 2

Дополнительно добавим настроенных пользователей и демонстрацию различных сценариев подключения.

Замените конфигурацию в файле `docker-compose.yml` текстом ниже:

```yml
version: '3.8'
services:
  ssh-server1:
    image: rastasheep/ubuntu-sshd:18.04
    container_name: ssh_server1
    restart: always
    ports:
      - "2222:22"
    environment:
      - ROOT_PASSWORD=rootpassword1
    volumes:
      - ./ssh-server1-config:/etc/ssh/
  ssh-server2:
    image: rastasheep/ubuntu-sshd:18.04
    container_name: ssh_server2
    restart: always
    ports:
      - "2223:22"
    environment:
      - ROOT_PASSWORD=rootpassword2
    volumes:
      - ./ssh-server2-config:/etc/ssh/
```

### Файлы для конфигурации SSH

Создайте папки `ssh-server1-config` и `ssh-server2-config` рядом с `docker-compose.yml`. В каждой папке создайте файл `sshd_config`, чтобы настроить серверы. Пример:

`ssh-server1-config/sshd_config`

```config
PermitRootLogin yes
PasswordAuthentication yes
PubkeyAuthentication yes
AllowUsers student1
```

`ssh-server2-config/sshd_config`

```config
PermitRootLogin yes
PasswordAuthentication yes
PubkeyAuthentication yes
AllowUsers student1
```

Сценарий и задания для практики:

### 1. Подключение к серверам

• Убедитесь, что оба сервера работают.
• Подключитесь к первому серверу:

```sh
ssh root@localhost -p 2222
```

Используйте пароль: `rootpassword1`.

• Подключитесь ко второму серверу:

```sh
ssh root@localhost -p 2223
```

Используйте пароль: `rootpassword2`.

### 2. Настройка SSH-ключей

• Создайте SSH-ключи на своей машине (если еще не созданы):

```sh
ssh-keygen -t rsa -b 4096 -f ~/.ssh/practice_key
```

• Копируйте публичный ключ на сервер:

```sh
ssh-copy-id -i ~/.ssh/practice_key.pub -p 2222 root@localhost
```

• Проверьте, что можете подключиться без пароля:

```sh
ssh -i ~/.ssh/practice_key root@localhost -p 2222
```

### 3. Изменение порта SSH

• Зайдите на сервер ssh_server1 и измените порт SSH в `/etc/ssh/sshd_config`:

```config
Port 2225
```

• Перезапустите службу SSH:

```sh
service ssh restart
```

• Попробуйте подключиться к новому порту:

```sh
ssh root@localhost -p 2225
```

### 4. Ограничение пользователей

• Добавьте нового пользователя `student1`:

```sh
adduser student1
```

• Убедитесь, что пользователь может подключаться:

```sh
ssh student1@localhost -p 2222
```

Пароль установите при создании пользователя.

• Настройте, чтобы только `student1` мог подключаться (в AllowUsers в sshd_config).

### 5. Работа с scp

• Скопируйте файл с локальной машины на сервер:

```sh
scp -P 2222 ./example.txt root@localhost:/root/
```

• Скопируйте файл с сервера на локальную машину:

```sh
scp -P 2223 root@localhost:/root/example.txt ./
```

### 6. Подключение через `~/.ssh/config`

• Настройте файл `~/.ssh/config` для удобного подключения:

```sh
Host server1
  HostName localhost
  Port 2222
  User root
  IdentityFile ~/.ssh/practice_key

Host server2
  HostName localhost
  Port 2223
  User root
  IdentityFile ~/.ssh/practice_key
```

• Теперь можно подключаться так:

```sh
ssh server1
ssh server2
```

### 7. Отладка и логи

• Откройте логи на сервере для анализа:

```sh
docker logs ssh_server1
```

 • Или войдите в контейнер для диагностики:

```sh
docker exec -it ssh_server1 bash
```

Завершение работы

После выполнения заданий завершите работу с контейнерами:

```sh
docker-compose down
```

## Практика Level 3

Список дополнительных заданий, которые углубят знания и дадут студентам больше практических навыков работы с SSH.

## Дополнительные задания для практики SSH

### 1. Настройка ограничений по IP

• Настройте так, чтобы подключение к ssh_server1 было возможно только с определенного IP-адреса. Используйте файлы `/etc/hosts.allow` и `/etc/hosts.deny`.
• Пример для `hosts.allow`:

```sh
sshd: 192.168.1.0/24
```

• Пример для hosts.deny:

```sh
sshd: ALL
```

#### 2. Создание SSH-туннеля

• Подключитесь к `ssh_server1` через туннель и откройте доступ к службе, запущенной на сервере, на локальной машине.
 • Пример: перенаправление порта с удаленного сервера на локальный.

```sh
ssh -L 8080:localhost:80 root@localhost -p 2222
```

 • Проверьте, что локальный порт 8080 теперь доступен.

#### 3. Реверсивный SSH-туннель

 • Настройте реверсивный SSH-туннель с ssh_server2 на локальную машину.
 • Пример:

```sh
ssh -R 9000:localhost:22 root@localhost -p 2223
```

 • Проверьте, что через порт 9000 можно подключаться обратно к локальной машине.

#### 4. Настройка ssh-agent

 • Настройте ssh-agent на локальной машине, чтобы запоминать ключи и подключаться к серверам без необходимости вводить пароль или путь к ключу.

```sh
eval $(ssh-agent)
ssh-add ~/.ssh/practice_key
ssh-add -l
```

• Проверьте подключение после добавления ключа:

```sh
ssh root@localhost -p 2222
```

#### 5. Forwarding X11

 • Настройте X11 Forwarding, чтобы запустить графическое приложение с сервера на локальной машине (если есть GUI). Для этого:

##### 1. Включите X11Forwarding в sshd_config на сервере

X11Forwarding yes
X11DisplayOffset 10

##### 2. На локальной машине подключитесь с флагом -X

ssh -X root@localhost -p 2222

##### 3. Запустите простое графическое приложение, например, xclock (установите его, если нет)

#### 6. Восстановление доступа

 • Удалите ваш публичный ключ на сервере, а также запретите PasswordAuthentication. Затем найдите способ восстановить доступ через Docker, изменив файл sshd_config или добавив новый ключ.

#### 7. Мониторинг и аудит SSH

 • Подключитесь к серверу и выполните действия, которые записываются в логи SSH.

```sh
cat /var/log/auth.log
```

 • Изучите, какие команды и подключения были зафиксированы.

#### 8. Перенаправление сокетов (SSH SOCKS Proxy)

 • Настройте SOCKS-прокси через SSH для безопасного доступа в интернет через сервер.

```sh
ssh -D 1080 root@localhost -p 2222
```

 • Настройте браузер или другую программу для использования локального порта 1080 как прокси.

#### 9. Многопользовательский сценарий

 • Создайте несколько пользователей (student1, student2, admin) на сервере.
 • Настройте так, чтобы:
 • student1 мог только читать файлы в /home/student_data.
 • student2 мог писать в /home/student_data.
 • admin имел полный доступ.

#### 10. Сертификаты SSH

 • Настройте сервер для использования сертификатов SSH вместо обычных ключей.

##### 1. Создайте ключи для центра сертификации (CA)

```sh
ssh-keygen -t rsa -f ca_key
```

##### 2. Подпишите пользовательский ключ

```sh
ssh-keygen -s ca_key -I "user_cert" -n root -V +1d ~/.ssh/practice_key.pub
```

##### 3. Настройте сервер для доверия CA

#### 11. Изменение алгоримов шифрования

• На сервере измените настройки шифрования в sshd_config, оставив только определенные алгоритмы (например, aes256-ctr или chacha20-poly1305):

Ciphers aes256-ctr,chacha20-poly1305

 • Проверьте, что подключение все еще возможно:

```sh
ssh -c aes256-ctr root@localhost -p 2222
```

#### 12. Блокировка по тайм-ауту

• Настройте сервер так, чтобы он автоматически завершал неактивные сессии через 1 минуту.
В sshd_config добавьте:

```sh
ClientAliveInterval 60
ClientAliveCountMax 1
```

 • Проверьте, что сессия завершается после неактивности.
