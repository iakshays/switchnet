#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Blynk.h>
#define S1 14
#define R1 12

#define S2 1
#define R2 3




BlynkTimer timer;
int MODE = 0;
int switch_ON_Flag1_previous_I = 0;
int switch_ON_Flag2_previous_I = 0;

/*----------------------------------------------------------------------------------------*/

char ssid[] = "Akshay";
char pass[] = "akshayyy";
char auth[] = "FjK3y0dwCs_9IL22GuWn_8KVl7wQX5xk";

/*----------------------------------------------------------------------------------------*/
void setup()
{
  // Debug console
  Serial.begin(9600);
  
  pinMode(S1, INPUT);
  pinMode(R1, OUTPUT);
  pinMode(S2, INPUT);
  pinMode(R2, OUTPUT);

  //pinMode(MODE, INPUT);
  WiFi.begin(ssid, pass);
  timer.setInterval(3000L, checkBlynk); // check if connected to Blynk server every 3 seconds
  Blynk.config(auth);//, ssid, pass);
}

/*----------------------------------------------------------------------------------------*/
void checkBlynk() { // called every 3 seconds by SimpleTimer
bool isconnected = Blynk.connected();
  if (isconnected == false) {
    MODE = 1;
  }
  if (isconnected == true) {
    MODE = 0;
  }
}

/*----------------------------------------------------------------------------------------*/
void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Not Connected");
  }
  else
  {
    Serial.println(" Connected");
    delay (1000);
    Blynk.run();
  }

  timer.run(); // Initiates SimpleTimer
  if (MODE == 0)
    with_internet();
  else
    without_internet();
}

/*----------------------------------------------------------------------------------------*/

void without_internet()
{
  digitalWrite(R1, digitalRead(S1));
  digitalWrite(R2, digitalRead(S2));
}

/*----------------------------------------------------------------------------------------*/
void with_internet()
{
  if (digitalRead(S1) == LOW)
  {
    if (switch_ON_Flag1_previous_I == 0 )
    {
      digitalWrite(R1, LOW);
      Serial.println("Relay1- ON");
      Blynk.virtualWrite(V1, 0);
      switch_ON_Flag1_previous_I = 1;
    }
    Serial.println("Switch1 -ON");
 }
 
  if (digitalRead(S1) == HIGH )
  {
    if (switch_ON_Flag1_previous_I == 1)
    {
      digitalWrite(R1, HIGH);
     Serial.println("Relay1 OFF");
      Blynk.virtualWrite(V1, 1);
      switch_ON_Flag1_previous_I = 0;
    }
  }
   //Serial.println("Switch1 OFF");

   /* ****************************************************/
   if (digitalRead(S2) == LOW)
  {
    if (switch_ON_Flag2_previous_I == 0 )
    {
      digitalWrite(R2, LOW);
      Serial.println("Relay2- ON");
      Blynk.virtualWrite(V2, 0);
      switch_ON_Flag2_previous_I = 1;
    }
    Serial.println("Switch2 -ON");
 }
 
  if (digitalRead(S2) == HIGH )
  {
    if (switch_ON_Flag2_previous_I == 1)
    {
      digitalWrite(R2, HIGH);
     Serial.println("Relay2 OFF");
      Blynk.virtualWrite(V2, 1);
      switch_ON_Flag2_previous_I = 0;
    }
   //Serial.println("Switch1 OFF");
  }
 }


/*----------------------------------------------------------------------------------------*/


BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(R1, pinValue);
  // process received value
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(R2, pinValue);
  // process received value
}
