#include <Arduino.h>

/**
 * @file UltraSensor.h
 * 
 * @brief Ultrassonic Sensor settings library
 */
class UltraSensor
{
private:
    int _triggerPin; // Pin for triggering the sensor
    int _echoPin;    // Pin for receiving the echo

    long lastUpdate = 50; // Last update time in milliseconds
    const unsigned long _updateInterval = 100; // Update interval in milliseconds    
public:
    float lastdistance = 0; // Last measured distance
    UltraSensor(); // Constructor with default value
    void begin(int triggerPin, int echoPin);
    float update();
};
UltraSensor::UltraSensor() {}

/**
 * @file UltraSensor.cpp
 * @brief Ultrassonic sensor begin
 * 
 * @param triggerPin Utrassonic digital pin trig
 * @param echoPin Ultrassonic digital pin echo
 */
void UltraSensor::begin(int triggerPin, int echoPin){
    _triggerPin = triggerPin; // Initialize the trigger pin
    _echoPin = echoPin;       // Initialize the echo pin

    pinMode(_triggerPin, OUTPUT); // Set the trigger pin as output
    pinMode(_echoPin, INPUT);      // Set the echo pin as input
}

/**
 * @brief Update and get Ultrassonic value
 * 
 * @return Ultrassonic value 
 */
float UltraSensor::update()
{
    // Send a 10 microsecond pulse to trigger the sensor
    digitalWrite(_triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_triggerPin, LOW);

    // Measure the duration of the echo pulse
    long duration = pulseIn(_echoPin, HIGH);

    // Calculate the distance in centimeters (speed of sound is 343 m/s)
    float distance = (duration * 0.0343) / 2; // Divide by 2 for round trip


    if (millis() - lastUpdate < _updateInterval && distance != 0) {
        return lastdistance; // Return the last distance if update interval has not passed
    }
    else if(distance != 0){
        lastdistance = distance; // Update the last distance
        lastUpdate = millis(); // Update the last update time
        return distance;
    }
}
