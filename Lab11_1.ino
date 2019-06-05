#include <LWiFi.h>
#include "MCS.h"

char _lwifi_ssid[] = "Big";
char _lwifi_pass[] = "00000001";
MCSDevice mcs("Db0s0gxq", "3l2z6NhntDDTcup1");

MCSControllerOnOff led("7697");
MCSDisplayOnOff remote("7777");

void setup()
{
  Serial.begin(9600);

  Serial.println("Connect to Wifi");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) {
    Serial.println("Wifi Reconnecting..");
    delay(1000);
  }

  Serial.println("Connect to MCS...");
  while (!mcs.connected()) {
    Serial.println("MCS Reconnecting..");
    mcs.connect();
  }
  Serial.println("MCS Connected!");
  mcs.addChannel(led);
  mcs.addChannel(remote);

  pinMode(7, OUTPUT);

}


void loop()
{
  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) {
      Serial.println("MCS Reconnect");
    }
  }
  mcs.process(1000);
  while(!led.valid())
{
    Serial.println("read LED value from MCS...");
    led.value();   
}
Serial.print("done, LED value = ");
Serial.println(led.value());  

  if (led.value() == 1) {
    digitalWrite(7, HIGH);

  } else {
    digitalWrite(7, LOW);

  }
  if(!remote.set(led.value()))
    {
      Serial.print("Failed to update remote");
      Serial.println(remote.value());
    }

  delay(200);
}
