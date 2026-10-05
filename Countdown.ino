void startCountdown(unsigned long seconds) {
    remainingTime = seconds;
    countdownStartTime = millis();
    countdownRunning = true;
    displayTimer(remainingTime);
}

void countdown() {
    if (!countdownRunning) {
        return;
    }

    unsigned long currentTime = millis();
    unsigned long elapsedSeconds =
        (currentTime - countdownStartTime) / 1000UL;

    if (elapsedSeconds > 0) {
        // Timer has reached zero
        if (elapsedSeconds >= remainingTime) {
            remainingTime = 0;
            countdownRunning = false;
            displayTimer(0);

            // Automatically submit the answer.
            // Reaching zero does NOT directly cause
            // game over.
            submitAnswer();
            return;
        }

        remainingTime -= elapsedSeconds;
        countdownStartTime = currentTime;
        displayTimer(remainingTime);
    }
}