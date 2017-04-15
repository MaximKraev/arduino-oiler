#define DEBUG_PORT Serial
#define PUMP_BUTTON 5
#define PUMP 2

const unsigned long interval = 90000;
const unsigned int PUMP_TICK_MS = 45;


unsigned long previousMillis = 0;
bool isPumpButtonPressed = false;

void setupPump() {
  pinMode(PUMP, OUTPUT);
  pumpOff();
}

void setupButtons() {
  pinMode(PUMP_BUTTON, INPUT);
  digitalWrite(PUMP_BUTTON, HIGH);
}

void setupDebug() {
  DEBUG_PORT.begin(9600);
  DEBUG_PORT.println("Setup");
}

void setup() {
  setupDebug();

  setupPump();
  setupButtons();
}


boolean handle_button()
{
  int button_pressed = !digitalRead(PUMP_BUTTON);
  return button_pressed;
}

void loop() {
  bool button_pressed = handle_button();
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    dropPump();
  }

  if (!isPumpButtonPressed && button_pressed) {
    pumpOn();
    isPumpButtonPressed = true;
  }

  if (isPumpButtonPressed && !button_pressed) {
    pumpOff();
    isPumpButtonPressed = false;
  }

  if (!isPumpButtonPressed) {
    delay(20);
  }
}

void pumpOn() {
  DEBUG_PORT.println("pumpOn");
  digitalWrite(PUMP, LOW);
}

void pumpOff() {
  DEBUG_PORT.println("pumpOff");
  digitalWrite(PUMP, HIGH);
}

void dropPump() {
  DEBUG_PORT.println("dropPump");
  pumpOn();
  delay(PUMP_TICK_MS);
  pumpOff();
}