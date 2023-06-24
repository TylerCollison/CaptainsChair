/*
  Serial controller software for smart massage chair control platform. 

  Serial format: 
    <channel_number>:<power_percentage>

  power_percentage must be between 0 (off) and 100 (max power)
  channel_number must be between 0 and 3
*/

/// The maximum duty cycle value, quivalent to full power
const int MAX_DUTY_CYCLE = 255;

/// Channel IDs for control zone
enum Channel {
  UPPER_BACK,
  LOWER_BACK,
  BUTT,
  LEG
};

/// Channel control pins
const int UPPER_BACK_PIN = 11;
const int LOWER_BACK_PIN = 5;
const int BUTT_PIN = 9;
const int LEG_PIN = 3;

/// Maps the channel identifier to the corresponding control pin
/// \param channel The channel to map
int getChannelPin(Channel channel)
{
  switch(channel)
  {
    case UPPER_BACK:
    return UPPER_BACK_PIN;
    case LOWER_BACK:
    return LOWER_BACK_PIN;
    case BUTT:
    return BUTT_PIN;
    case LEG:
    return LEG_PIN;
    default:
    return -1;
  }

  return -1;
}

/// Sets the analog duty cycle of the output pin to the specified percentage (0-100)
/// \param pin The pin to set the duty cycle
/// \param power The power percentage to which to set the duty cycle (0-100)
void setPinPower(int pin, int power)
{
  // Ensure the power percentage is valid (between 0% and 100%)
  if (power < 0 || power > 100) { return; }
  float powerPercentage = (float)power / 100;
  int dutyCycle = MAX_DUTY_CYCLE * powerPercentage;

  analogWrite(pin, dutyCycle);
}

/// Sets serial settings
void setupSerial()
{
  Serial.begin(9600); // Initialize serial port to send and receive at 9600 baud
}

/// Sets channel pin settings
void setupChannelPins()
{
  pinMode(UPPER_BACK_PIN, OUTPUT);
  pinMode(LOWER_BACK_PIN, OUTPUT);
  pinMode(BUTT_PIN, OUTPUT);
  pinMode(LEG_PIN, OUTPUT);
}

/// Resets channel pins to starting state
void resetChannelPins()
{
  analogWrite(UPPER_BACK_PIN, 0);
  analogWrite(LOWER_BACK_PIN, 0);
  analogWrite(BUTT_PIN, 0);
  analogWrite(LEG_PIN, 0);
}

void setup() {
  // Setup the serial connection
  setupSerial();

  // Setup control pins
  setupChannelPins();

  // Reset control pins (off)
  resetChannelPins();
}

void loop() {
  // Wait for serial input
  while (Serial.available() == 0) {}  

  Serial.println("Getting Channel");

  // Get the channel from input
  Channel channel = Serial.parseInt();

  // Get the channel pin
  // If invalid, return and wait for a valid channel
  int channelPin = getChannelPin(channel);
  if (channelPin < 0) { return; }

  Serial.println("Channel valid: ");
  Serial.println(channelPin);

  // Expecting more data on the buffer (otherwise, input is invalid)
  // If invalid, return and wait for a valid channel
  if (Serial.available() == 0) { return; }

  Serial.println("Checking separator");

  // Get the separator token
  char separator = Serial.read();

  // If invalid, return and wait for valid input
  if (separator != ':') { return; }

  Serial.println("Separator valid");

  // Expecting more data on the buffer (otherwise, input is invalid)
  // If invalid, return and wait for a valid power level
  if (Serial.available() == 0) { return; }

  Serial.println("Getting power level");

  int powerPercentage = Serial.parseInt();

  // Apply the specified power level to the channel
  setPinPower(channelPin, powerPercentage);

  Serial.println("Power level set");
  Serial.println(powerPercentage);
}
