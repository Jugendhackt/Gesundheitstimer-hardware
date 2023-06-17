#include "netzwerk.hpp"
void netzwerk::Sendewasserstand(float wasser_in_g){
   if (client.connect(serverIP, serverPort)) {
    String postData = "gewicht=" + String(wasser_in_g);

    client.println("POST " + String(endpointWasser) + " HTTP/1.1");
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

void netzwerk::Sendepotiwert(float wasser_in_prozent){
   if (client.connect(serverIP, serverPort)) {
    String postData = "menge_ml=" + String(wasser_in_prozent);

    client.println("POST " + String(endpointpoti) + " HTTP/1.1");
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
void netzwerk::SendeAlarm (float _0_oder_1_){
   if (client.connect(serverIP, serverPort)) {
    String postData = "0oder1=" + String(_0_oder_1_);

    client.println("POST " + String(endpointAlarm) + " HTTP/1.1");
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




>>>>>>> e7e22c7094906aa784ebe3c8c73ed3f6f4591533
