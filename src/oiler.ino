#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;

#define RX_PIN 4
#define TX_PIN 3
SoftwareSerial ss(RX_PIN, TX_PIN);

#define DEBUG_PORT Serial

#define BUTTON_PIN 5
#define PUMP 2

unsigned long previousMillis = 0;
const unsigned int interval = 60000;
const unsigned int PUMP_TICK_MS = 35;

static void GPSloop()
{
  unsigned long chars;
  unsigned short sentences, failed;

  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      DEBUG_PORT.write(c);
    }
  }

  gps.stats(&chars, &sentences, &failed);
  DEBUG_PORT.print(" CHARS=");
  DEBUG_PORT.print(chars);
  DEBUG_PORT.print(" SENTENCES=");
  DEBUG_PORT.print(sentences);
  DEBUG_PORT.print(" CSUM ERR=");
  DEBUG_PORT.println(failed);
  if (chars == 0)
    DEBUG_PORT.println("** No characters received from GPS: check wiring **");
} // GPSloop

void setupGPS()
{
  DEBUG_PORT.begin(9600);
  ss.begin(9600);

  DEBUG_PORT.print("Simple TinyGPS library v. ");
  DEBUG_PORT.println(TinyGPS::library_version());
  DEBUG_PORT.println("by Mikal Hart");
  DEBUG_PORT.println();
}

void setupPump() {
  pinMode(PUMP, OUTPUT);
}

void setupButtons() {
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);
}

void setup() {
  setupPump();
  setupButtons();
  //setupGPS();
}


boolean handle_button()
{
  int button_pressed = !digitalRead(BUTTON_PIN); // pin low -> pressed
  return button_pressed;
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean button_pressed = handle_button();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    dropPump();
  }

  if (button_pressed) {
    onPump();
  }
  else {
    offPump();
  }
  //GPSloop();

  delay(20);
}

void onPump() {
  digitalWrite(PUMP, LOW);
}

void offPump() {
  digitalWrite(PUMP, HIGH);
}

void dropPump() {
  onPump();
  delay(PUMP_TICK_MS);
  offPump();
}
