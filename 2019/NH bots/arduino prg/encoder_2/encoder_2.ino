/**
 * Quadrature Encoder Demo
 * Author: Shawn Hymel (SparkFun Electronics)
 * Date: July 20, 2017
 *
 * Two photocells look for light changes through an encoder
 * disc (can be 3D printed or cut out of cardboard). As the
 * encoder disc spins in one direction, the connected LED
 * ("lamp") gets brighter. If the encoder dic is spun in the
 * other direction, the LED gets dimmer.
 *
 * License: Beerware (https://en.wikipedia.org/wiki/Beerware)
 */

// Parameters
const int threshold = 600;
const float multiplier = 1.4;

// Pins
const int i_pin = A1;
const int q_pin = A0;
const int led_pin = 8;
const int lamp_pin = 9;

// Globals
int i_prev = 0;
int q_prev = 0;
float brightness = 1;

void setup() {

  // Set up pins
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, HIGH);
  pinMode(lamp_pin, OUTPUT);

  // Set up Serial
  Serial.begin(9600);

  // Measure initial Q
  i_prev = (analogRead(i_pin) > threshold) ? 1 : 0;
}

void loop() {

  // Measure
  int i_state = (analogRead(i_pin) > threshold) ? 1 : 0;
  int q_state = (analogRead(q_pin) > threshold) ? 1 : 0;

  // Look for falling edge on I
  if ( (i_prev != i_state) && (i_state == 0) ) {

    // If I and Q are the same, CW, otherwise CCW
    if ( i_state == q_state ) {
      brightness *= multiplier;
      if ( brightness >= 255 ) brightness = 255;
    } else {
      brightness /= multiplier;
      if ( brightness <= 1 ) brightness = 1;
    }

    // Print counter
    Serial.println(brightness);

    // Set LED
    analogWrite(lamp_pin, (int)brightness);
  }

  // Save state for next sample
  i_prev = i_state;

  delay(10);
}
