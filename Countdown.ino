// VARIABLES
unsigned long lastPrint = 0;

// FUNCTIONS
void startCountdown(unsigned long seconds) {
    countdownDuration = seconds;
    countdownStartTime = millis();
}

void countdown() {
    unsigned long elapsed = millis() - countdownStartTime;
    if (elapsed < countdownDuration * 1000UL) {
        unsigned long remaining =
            countdownDuration - (elapsed / 1000UL);
        int tens = remaining / 10;
        int ones = remaining % 10;

        setTimerNumbers(String(tens), String(ones));

    if (elapsed >= 10000 && elapsed - lastPrint >= 5000) {
        displayRandomMessageOfEncouragement();
        Serial.println(elapsed);
        lastPrint = elapsed;
    }

    } else {
        lcd.setCursor(13, 0);
        lcd.print("0");
        lcd.setCursor(14, 0);
        lcd.print("0");
        displayTopText("Game over!");
    }
}