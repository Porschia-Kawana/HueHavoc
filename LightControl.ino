// -------------------------
// PLAYER RGB LED
// -------------------------

const int RED_PIN = 3;
const int GREEN_PIN = 5;
const int BLUE_PIN = 6;

// -------------------------
// TARGET RGB LED
// -------------------------

const int TARGET_RED_PIN = 9;
const int TARGET_GREEN_PIN = 10;
const int TARGET_BLUE_PIN = 11;

// -------------------------
// SETUP LED PINS
// -------------------------

void setupLEDPins() {

    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    pinMode(TARGET_RED_PIN, OUTPUT);
    pinMode(TARGET_GREEN_PIN, OUTPUT);
    pinMode(TARGET_BLUE_PIN, OUTPUT);


    // Turn player LED off
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 0);


    // Turn target LED off
    analogWrite(TARGET_RED_PIN, 0);
    analogWrite(TARGET_GREEN_PIN, 0);
    analogWrite(TARGET_BLUE_PIN, 0);
}

// -------------------------
// UPDATE PLAYER RGB LED
// -------------------------

void updatePlayerRGB() {
    analogWrite(
        RED_PIN,
        playerRed
    );

    analogWrite(
        GREEN_PIN,
        playerGreen
    );

    analogWrite(
        BLUE_PIN,
        playerBlue
    );

    displayRGB();
}

// -------------------------
// GENERATE TARGET RGB
// -------------------------

void generateTargetRGB() {
    targetRed = random(0, 256);
    targetGreen = random(0, 256);
    targetBlue = random(0, 256);

    // Target LED
    analogWrite(
        TARGET_RED_PIN,
        targetRed
    );

    analogWrite(
        TARGET_GREEN_PIN,
        targetGreen
    );

    analogWrite(
        TARGET_BLUE_PIN,
        targetBlue
    );

    // Serial output
    Serial.print("Target R: ");
    Serial.println(targetRed);

    Serial.print("Target G: ");
    Serial.println(targetGreen);

    Serial.print("Target B: ");
    Serial.println(targetBlue);
}
