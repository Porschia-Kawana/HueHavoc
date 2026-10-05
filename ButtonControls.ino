const int RED_BUTTON = A3;
const int GREEN_BUTTON = A2;

void setupButtons() {
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

int checkButtons() {

    // ==========================================
    // GREEN BUTTON
    // ==========================================

    if (digitalRead(GREEN_BUTTON) == LOW) {
        delay(50);
        while (digitalRead(GREEN_BUTTON) == LOW) {}
        return GREEN_PRESSED;
    }

    // ==========================================
    // RED BUTTON
    // ==========================================

    if (digitalRead(RED_BUTTON) == LOW) {
        delay(50);
        while (digitalRead(RED_BUTTON) == LOW) {}
        return RED_PRESSED;
    }

    return NO_BUTTON;
}