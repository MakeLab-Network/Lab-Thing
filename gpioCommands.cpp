#include "lab-thing.h"
byte pinMap[9] = {D0, D1, D2, D3, D4, D5, D6, D7, D8};
long digitalPinsNextActionsTimes[9] = {LONG_LIMIT_MAX, LONG_LIMIT_MAX, LONG_LIMIT_MAX, LONG_LIMIT_MAX, LONG_LIMIT_MAX, LONG_LIMIT_MAX, LONG_LIMIT_MAX, LONG_LIMIT_MAX, LONG_LIMIT_MAX};
long digitalPinsNearestActionTime = LONG_LIMIT_MAX;
bool digitalPinsNextActionsValues[9] = {false, false, false, false, false, false, false, false, false};
bool nextActionValue = 0;
byte nextPinForAction = 0;

void GPIOCmdWrite()
{
  server.client().setNoDelay(true); // disables Nagle's algorithm. everything is faster
  server.send(200, "text/plain", "");
  byte pinIndex = server.pathArg(0).toInt(); // pins like D0, D1 etc... NOT REAL GPIO NUMBER!
  bool pinValue = server.arg("val").toInt(); // 1 high, 0 low.
  Serial.printf("digitalWrite(%d, %d).\n", pinIndex, pinValue);
  pinMode(pinMap[pinIndex], OUTPUT);
  digitalWrite(pinMap[pinIndex], pinValue);
  if (server.hasArg("duration")) // set pin for specified duration or for good?
  {
    long currentActionTime = millis() + server.arg("duration").toInt(); // when we need to deal again with this pin it the future...
    digitalPinsNextActionsTimes[pinIndex] = currentActionTime;
    digitalPinsNextActionsValues[pinIndex] = !pinValue;                                        // change pin value in next action.
    if (currentActionTime < digitalPinsNearestActionTime || digitalPinsNearestActionTime == 0) // if this is the nearest action among digital pins.
    {
      digitalPinsNearestActionTime = currentActionTime;
      nextActionValue = !pinValue;
      nextPinForAction = pinIndex;
    }
    // explain to client: ?
    String message = "will turn pin" + String(pinIndex) + (!pinValue ? " HIGH" : " LOW") + " in " + String(currentActionTime - millis()) + " milliseconds";
    //      server.send(200, "text/plain", message);
    Serial.println(message);
  }
}
// this will not work with two pins with the same action time...
void LabThing::handleGPIO()
{
  if (millis() > digitalPinsNearestActionTime) // if this is the nearest action among digital pins.
  {
    digitalWrite(pinMap[nextPinForAction], nextActionValue); // take the action!!
    digitalPinsNextActionsTimes[nextPinForAction] = LONG_LIMIT_MAX;
    Serial.printf("pin %d just turnd %d!\n", nextPinForAction, nextActionValue);
    digitalPinsNearestActionTime = digitalPinsNextActionsTimes[0];
    nextPinForAction = 0;
    for (int pinIndex = 1; pinIndex < 9; pinIndex++)                                                                 // loop over 9 pins
      if (digitalPinsNextActionsTimes[pinIndex] < digitalPinsNearestActionTime && digitalPinsNearestActionTime != 0) // find the pin with the nearest action time.
      {
        digitalPinsNearestActionTime = digitalPinsNextActionsTimes[pinIndex];
        nextPinForAction = pinIndex;
        nextActionValue = digitalPinsNextActionsValues[pinIndex];
      }
  }
}
