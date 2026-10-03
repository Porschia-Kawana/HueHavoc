// -------------------------
// BUTTON PINS
// -------------------------

const int RED_BUTTON = A3;
const int GREEN_BUTTON = A2;

// -------------------------
// BUTTON SETUP
// -------------------------

void setupButtons() {
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

// -------------------------
// CHECK BUTTONS
// -------------------------

int checkButtons() {
    if (digitalRead(RED_BUTTON) == LOW) {
        return RED_PRESSED;
    }

    if (digitalRead(GREEN_BUTTON) == LOW) {
        return GREEN_PRESSED;
    }

    return NO_BUTTON;
}