#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;

// VARIABLES
unsigned long countdownStartTime;
unsigned long countdownDuration;
bool countdownRunning = false;

// TEMPORARY VARIABLES
static bool started = false;

void setup() {
    Serial.begin(9600);
    setupLCD();
}


void loop() {
    if (!started) {
        delay(2000);
        displayTopText("Ready Set Go!");

        for (int i = 3; i > 0; i--) {
            setTimerNumbers(" ", String(i));
            delay(1000);
        }

        displayTopText("Find the RGB!");
        startCountdown(60);
        started = true;
    }

    countdown();
}