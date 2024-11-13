from http.server import SimpleHTTPRequestHandler, HTTPServer

class SimpleHandler(SimpleHTTPRequestHandler):
    def do_GET(self):
        # Устанавливаем код ответа 200 (ОК)
        self.send_response(200)
        # Указываем, что будет возвращен HTML-контент
        self.send_header("Content-type", "text/html")
        self.end_headers()
        
        # HTML-контент страницы
        html_content = b"""
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <title>Simple Web Page</title>
        </head>
        <body>
            <h1>Hello from Python HTTP Server!</h1>
            <p>This is a simple response from a Python server.</p>
        </body>
        </html>
        """
        
        # Отправляем HTML-контент в качестве ответа
        self.wfile.write(html_content)

# Настройки сервера
host = "localhost"
port = 8080

# Создаем и запускаем сервер
with HTTPServer((host, port), SimpleHandler) as server:
    print(f"Server started at http://{host}:{port}")
    server.serve_forever()
