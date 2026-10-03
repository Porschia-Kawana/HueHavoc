// -------------------------
// VARIABLES
// -------------------------

unsigned long lastPrint = 0;

// -------------------------
// START COUNTDOWN
// -------------------------

void startCountdown(unsigned long seconds) {
    remainingTime = seconds;
    countdownStartTime = millis();
    countdownRunning = true;
}

// -------------------------
// COUNTDOWN
// -------------------------

void countdown() {
    if (!countdownRunning) {
        return;
    }

    unsigned long elapsed =
        (millis() - countdownStartTime) / 1000UL;

    if (elapsed > 0) {
        // TIMER HAS REACHED ZERO
        if (elapsed >= remainingTime) {
            remainingTime = 0;
            countdownRunning = false;

            // Automatically submit
            submitAnswer();
            return;
        }

        // REMOVE ELAPSED TIME
        remainingTime -= elapsed;
        countdownStartTime = millis();
    }

    // -------------------------
    // DISPLAY TIMER
    // -------------------------

    int tens = (remainingTime / 10) % 10;
    int ones = remainingTime % 10;

    setTimerNumbers(
        String(tens),
        String(ones)
    );

    // -------------------------
    // ENCOURAGEMENT
    // -------------------------

    unsigned long totalElapsed =
        millis() - gameStartTime;

    if (totalElapsed >= 10000 &&
        totalElapsed - lastPrint >= 5000) {
        displayRandomMessageOfEncouragement();
        Serial.println(totalElapsed);
        lastPrint = totalElapsed;
    }
}