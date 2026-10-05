// ==========================================
// PLAYER LED PINS
// ==========================================

const int RED_PIN = 3;
const int GREEN_PIN = 5;
const int BLUE_PIN = 6;

// ==========================================
// TARGET LED PINS
// ==========================================

const int TARGET_BLUE_PIN = 9;
const int TARGET_GREEN_PIN = 10;
const int TARGET_RED_PIN = 11;

// ==========================================
// SETUP LEDS
// ==========================================

void setupLEDPins() {
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    pinMode(TARGET_RED_PIN, OUTPUT);
    pinMode(TARGET_GREEN_PIN, OUTPUT);
    pinMode(TARGET_BLUE_PIN, OUTPUT);

    // Player LED OFF
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 0);

    // Target LED OFF
    analogWrite(TARGET_RED_PIN, 0);
    analogWrite(TARGET_GREEN_PIN, 0);
    analogWrite(TARGET_BLUE_PIN, 0);
}

// ==========================================
// UPDATE PLAYER RGB
// ==========================================

void updatePlayerRGB() {
    analogWrite(RED_PIN, playerRed);
    analogWrite(GREEN_PIN, playerGreen);
    analogWrite(BLUE_PIN, playerBlue);
    displayRGB();
}

// ==========================================
// GENERATE TARGET RGB
// ==========================================

void generateTargetRGB() {
    int newRed;
    int newGreen;
    int newBlue;

    if (!targetGenerated) {
        // First target
        newRed = random(0, 256);
        newGreen = random(0, 256);
        newBlue = random(0, 256);
        targetGenerated = true;
    } else {
        // Subsequent targets
        do {
            newRed = random(0, 256);
            newGreen = random(0, 256);
            newBlue = random(0, 256);
        } while (
            abs(newRed - targetRed) +
            abs(newGreen - targetGreen) +
            abs(newBlue - targetBlue)
            < MIN_TARGET_DIFFERENCE * 3
        );
    }

    targetRed = newRed;
    targetGreen = newGreen;
    targetBlue = newBlue;

    // Turn target LED ON
    analogWrite(TARGET_RED_PIN, targetRed);
    analogWrite(TARGET_GREEN_PIN, targetGreen);
    analogWrite(TARGET_BLUE_PIN, targetBlue);

    Serial.println();
    Serial.println("New target:");
    Serial.print("R: ");
    Serial.println(targetRed);
    Serial.print("G: ");
    Serial.println(targetGreen);
    Serial.print("B: ");
    Serial.println(targetBlue);
}

// ==========================================
// TURN TARGET LED OFF
// ==========================================

void turnTargetLightOff() {
    analogWrite(TARGET_RED_PIN, 0);
    analogWrite(TARGET_GREEN_PIN, 0);
    analogWrite(TARGET_BLUE_PIN, 0);
}

// ==========================================
// TURN PLAYER LED OFF
// ==========================================

void turnPlayerLightOff() {
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 0);
}