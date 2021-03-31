#include <Arduino.h>
#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//ssid ip address กับ password ของ wifi ที่สร้าง

const char* ssid = "Phornnipha-wifi";                           //ตั้งชื่อ wifi                        
const char* password = "987654321";                             //ตั้ง password

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

int cnt = 0;

void setup(void){
     Serial.begin(115200);                                        // เริ่มการทำงาน Serial Monitor(การกำหนดอัตรการส่งข้อมูล)

     pinMode(0, INPUT);                                           //การกำหนดขาที่เชื่อมต่อวงจรให้เป็นพอร์ต input
     pinMode(2, OUTPUT);                                          //การกำหนดขาที่เชื่อมต่อวงจรให้เป็นพอร์ต output
        
     Serial.println("\n\n\n");                               
     int val = digitalRead(0);                                     //กำหนดให้ val = ค่าที่อ่านข้อมูลเข้าพอร์ตที่input
     Serial.printf("read=== %d\n", val);                           //แสดงค่าออกมา val = 0 หรือ 1 ตามค่าที่อ่านข้อมูลเข้าพอร์ตที่input
          
        if(val==1) 
               Serial.println("---input---");                      //การพิมพ์ข้อมูลไปยังพอร์ตและขึ้นบรรทัดใหม่
               Serial.begin(115200);

                WiFi.softAP(ssid, password);
                WiFi.softAPConfig(local_ip, gateway, subnet);
                delay(1000);                                      //เป็นการหน่วงเวลาตามค่าที่กำหนด มีหน่วยเป็น ms

                server.onNotFound([]() {
                        server.send(404, "text/plian", "Path Not Found");
               });
               server.on("/", []() {
                        cnt++;
                        String msg = "Hello cnt: ";
                        msg += cnt;
                        server.send(200, "text/plain", msg);
                        digitalWrite(2, LOW);                  //เขียนข้อมูลออกพอร์ตที่output
                        delay(1000);         
                });
                
                server.begin();
                Serial.println("server started");    
        
        } else {
               Serial.println("---no input---");
               Serial.begin(115200);
        
               cnt++;
               Serial.printf("number:%d\n",cnt);
               if(cnt % 2) {
                      Serial.println("==LED ON==");
                      digitalWrite(2, HIGH);
               } else {
                      Serial.println("==LED OFF==");
                      digitalWrite(2, LOW);
               }
               int p = (cnt % 4)+1;
               int s = p * 1000;
               delay(s);
	             
        }
}

void loop(){
	server.handleClient();
	
}
