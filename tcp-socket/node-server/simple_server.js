const http = require('http');

// HTML-контент для ответа
const htmlContent = `
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Simple Web Page</title>
</head>
<body>
    <h1>Hello from Node.js HTTP Server!</h1>
    <p>This is a simple response from a Node.js server.</p>
</body>
</html>
`;

// Настройки сервера
const host = '0.0.0.0';
const port = 8080;

// Создаем сервер
const server = http.createServer((req, res) => {
    // Устанавливаем заголовок и статус ответа
    res.writeHead(200, { 'Content-Type': 'text/html' });
    // Отправляем HTML-контент
    res.end(htmlContent);
});

// Запуск сервера
server.listen(port, host, () => {
    console.log(`Server started at http://${host}:${port}`);
});
