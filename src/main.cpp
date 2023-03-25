#include <Arduino.h>

const int RELAY_PIN = 2;
bool finished = false;
int trigger_delay_ms = 100;
int contact_gap_ms = 500;


void relay_open()
{
  digitalWrite(RELAY_PIN, LOW);
}

void relay_close()
{
  digitalWrite(RELAY_PIN, HIGH);
}

void trigger_relay()
{  
  relay_open();
  delay(100);
  relay_close();
}


// The FI indicator light (LED) emits service code(s) to show
// the problem(s) which the DFI system, and ignition system
// has at the moment of diagnosis.
void dealer_mode_one()
{
  relay_close();
}

// The FI indicator light (LED) emits service code(s) to show
// the problem(s) which the DFI system, and ignition system
// had in the past.

// Manual reference.
// To enter the self-diagnosis dealer mode 2, open [B] and
// ground [A] the lead more than five times [F] within 2 sec-
// onds [C] after the lead is first grounded, and then keep it
// grounded continuously [D] for more than 2 seconds.
void dealer_mode_two()
{
  trigger_relay();
  delay(contact_gap_ms);

  trigger_relay();
  delay(contact_gap_ms);

  trigger_relay();
  delay(contact_gap_ms);

  trigger_relay();
  delay(contact_gap_ms);

  trigger_relay();
  delay(contact_gap_ms);

  // This is the sixth contact and keeps the circuit closed.
  relay_open();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  

  digitalWrite(RELAY_PIN, HIGH); 
  pinMode(RELAY_PIN, OUTPUT);
  
}

void loop() {
  if (!finished) 
  {
    delay(2000);
    dealer_mode_two();
    finished = true;
  }
}