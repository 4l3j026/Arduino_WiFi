//Load Wi-Fi Library.
#include <ESP8266WiFi.h>

WiFiServer server(80);

//Replace with network credentials. 
const char* network = "Motorola";
const char* password = "262001Mech";
int cont = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("Conectandose a red : ");
  Serial.print(network);
  Serial.print("\n\r");
  WiFi.begin(network, password); //Conexión a la red
  while (WiFi.status() != WL_CONNECTED) //Mientras no esté conectado imprime por el puerto serial
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n\r");
  Serial.print("WiFi conectado"); //La conexión se completó exitosamente
  Serial.print("\n\r");
  server.begin(); //Iniciamos el servidor
  Serial.print("Servidor Iniciado");
  Serial.print("\n\r");
  Serial.print("Ingrese desde un navegador web usando la siguiente IP:");
  Serial.print("\n\r");
  Serial.print(WiFi.localIP()); //Obtenemos la IP  //La ip local del cliente (ESP12-E)
  Serial.print("\n\r");
}

void loop() {
  WiFiClient client = server.available();
  if (client) { //Si hay un cliente presente
    //    Serial.println("Nuevo Cliente");
    while (!client.available() && client.connected()) {
      delay(1);
    }
    // Leemos la primera línea de la petición del cliente.
    String linea1 = client.readStringUntil('r');
    //    Serial.print(linea1);
    //    Serial.print("\n\r");
    if (linea1.indexOf("boton=a") > 0) //Buscamos un LED=ON en la 1°Linea
    {
      Serial.print("a");
      Serial.print("\n\r");
    }
    if (linea1.indexOf("boton=b") > 0) //Buscamos un LED=OFF en la 1°Linea
    {
      Serial.print("b");
      Serial.print("\n\r");
    }
    client.flush();

    //    Serial.print("Enviando respuesta...");
    //    Serial.print("\n\r");
    //Encabezado http
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");// La conexión se cierra después de finalizar de la respuesta
    client.println();
    //Pagina html  para en el navegador
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head><title>ESP12-F Platform Research</title>");
    client.println("<body>");
    client.println("<h1 align='center'>Platform Robotic - IoT(ESP8266)</h1>");
    client.println("<div style='text-align:center;'>");
    client.println("<br />");
    client.println("<button onClick=location.href='./?boton=a'>Forward</button>");
    client.println("<button onClick=location.href='./?boton=b'>Move Backward</button>");
    client.println("<button onClick=location.href='./?boton=c'>Move Right</button>");
    client.println("<button onClick=location.href='./?boton=d'>Move Left</button>");
    client.println("<br />");
    client.println("</div>");
    client.println("</body>");
    client.println("</html>");

    delay(1);
    //    Serial.print("respuesta enviada");
    //    Serial.print("\n\r");
  }

  cont++;
  Serial.print(cont);
  Serial.print("\n\r");
  delay(1000);
}
