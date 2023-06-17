#include "netzwerk.hpp"
void netzwerk::Sendewasserstand(float wasser_in_g){
   if (client.connect(serverIP, serverPort)) {
    String postData = "gewicht=" + String(wasser_in_g);

    client.println("POST " + String(endpoint) + " HTTP/1.1");
    client.println("Host: " + String(serverUrl));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
    client.println(postData);
    client.println();

    Serial.println("Variable sent to server");

    // Hier kannst du weitere Aktionen ausführen, nachdem die Variable gesendet wurde

    client.stop();
  } else {
    Serial.println("Failed to connect to server");
  }

}
