// ==========================================
// RED ENCODER
// ==========================================

const int ENCODER_RED_A = 2;
const int ENCODER_RED_B = 4;

// ==========================================
// GREEN ENCODER
// ==========================================

const int ENCODER_GREEN_A = 7;
const int ENCODER_GREEN_B = 8;

// ==========================================
// BLUE ENCODER
// ==========================================

const int ENCODER_BLUE_A = 12;
const int ENCODER_BLUE_B = 13;

// ==========================================
// ENCODER STATES
// ==========================================

int previousRedState;
int previousGreenState;
int previousBlueState;

// ==========================================
// ENCODER COUNTERS
// ==========================================

int redEncoderCount = 0;
int greenEncoderCount = 0;
int blueEncoderCount = 0;

// ==========================================
// SETUP ENCODERS
// ==========================================

void setupEncoders() {
    pinMode(ENCODER_RED_A, INPUT_PULLUP);
    pinMode(ENCODER_RED_B, INPUT_PULLUP);

    pinMode(ENCODER_GREEN_A, INPUT_PULLUP);
    pinMode(ENCODER_GREEN_B, INPUT_PULLUP);

    pinMode(ENCODER_BLUE_A, INPUT_PULLUP);
    pinMode(ENCODER_BLUE_B, INPUT_PULLUP);

    previousRedState = (digitalRead(ENCODER_RED_A) << 1) | digitalRead(ENCODER_RED_B);
    previousGreenState = (digitalRead(ENCODER_GREEN_A) << 1) | digitalRead(ENCODER_GREEN_B);
    previousBlueState = (digitalRead(ENCODER_BLUE_A) << 1) | digitalRead(ENCODER_BLUE_B);
}

// ==========================================
// READ ENCODER
// ==========================================

int readEncoder(int pinA, int pinB, int &previousState, int &count) {
    int currentState = (digitalRead(pinA) << 1) | digitalRead(pinB);
    int transition = (previousState << 2) | currentState;

    previousState = currentState;

    // ======================================
    // CLOCKWISE
    // ======================================

    if (
        transition == 0b0001 ||
        transition == 0b0111 ||
        transition == 0b1110 ||
        transition == 0b1000
    ) {
        count--;
    }

    // ======================================
    // ANTICLOCKWISE
    // ======================================

    if (
        transition == 0b0010 ||
        transition == 0b1011 ||
        transition == 0b1101 ||
        transition == 0b0100
    ) {
        count++;
    }

    // ======================================
    // COMPLETE STEP
    // ======================================

    if (count >= 4) {
        count = 0;
        return 1;
    }

    if (count <= -4) {
        count = 0;
        return -1;
    }

    return 0;
}

// ==========================================
// UPDATE ALL ENCODERS
// ==========================================

void updateEncoders() {

    bool changed = false;

    // ======================================
    // RED
    // ======================================

    int redChange =
        readEncoder(
            ENCODER_RED_A,
            ENCODER_RED_B,
            previousRedState,
            redEncoderCount
        );

    if (redChange != 0) {
        playerRed += redChange * 5;
        playerRed = constrain(playerRed, 0, 255);
        changed = true;
    }

    // ======================================
    // GREEN
    // ======================================

    int greenChange =
        readEncoder(
            ENCODER_GREEN_A,
            ENCODER_GREEN_B,
            previousGreenState,
            greenEncoderCount
        );

    if (greenChange != 0) {
        playerGreen += greenChange * 5;
        playerGreen = constrain(playerGreen, 0, 255);
        changed = true;
    }

    // ======================================
    // BLUE
    // ======================================

    int blueChange =
        readEncoder(
            ENCODER_BLUE_A,
            ENCODER_BLUE_B,
            previousBlueState,
            blueEncoderCount
        );

    if (blueChange != 0) {
        playerBlue += blueChange * 5;
        playerBlue = constrain(playerBlue, 0, 255);
        changed = true;
    }

    // ======================================
    // UPDATE LED + LCD
    // ======================================

    if (changed) {
        updatePlayerRGB();
    }
}