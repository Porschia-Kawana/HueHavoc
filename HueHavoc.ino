#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;


enum Button {
    NO_BUTTON,
    RED_PRESSED,
    GREEN_PRESSED
};


// ==========================================
// GAME SETTINGS
// ==========================================

const int MAX_TIME = 90;
const int STARTING_TIME = 60;

const int WIN_TIME_BONUS = 5;
const int LOSE_TIME_PENALTY = 5;

const int MIN_TARGET_DIFFERENCE = 51;

// ==========================================
// PLAYER RGB
// ==========================================

int playerRed = 0;
int playerGreen = 0;
int playerBlue = 0;

// ==========================================
// TARGET RGB
// ==========================================

int targetRed = 0;
int targetGreen = 0;
int targetBlue = 0;

bool targetGenerated = false;

// ==========================================
// TIMER
// ==========================================

// Time allocated to the current/next round
int roundTime = STARTING_TIME;

// Actual live countdown
unsigned long remainingTime;
unsigned long countdownStartTime;
bool countdownRunning = false;

// ==========================================
// GAME STATE
// ==========================================

bool started = false;
bool gameOver = false;

// ==========================================
// SCORE
// ==========================================

int roundsCompleted = 0;
int totalPoints = 0;
int perfectMatches = 0;

// ==========================================
// SETUP
// ==========================================

void setup() {
    Serial.begin(9600);
    setupLEDPins();
    setupLCD();
    setupButtons();
    setupEncoders();
    randomSeed(analogRead(A0));
}

// ==========================================
// MAIN LOOP
// ==========================================

void loop() {
    int button = checkButtons();

    // ==========================================
    // GREEN BUTTON
    // ==========================================

    if (button == GREEN_PRESSED) {
        if (!started || gameOver) {
            // Start a new game
            startGame();
        } else {
            // Submit current answer
            submitAnswer();
        }
    }

    // ==========================================
    // RED BUTTON
    // ==========================================

    if (button == RED_PRESSED) {
        // Stop the current game immediately
        if (started && !gameOver) {
            countdownRunning = false;
            gameOver = true;
            turnPlayerLightOff();
            turnTargetLightOff();
            displayGameOver();
        }
    }

    // ==========================================
    // GAME RUNNING
    // ==========================================

    if (started && !gameOver) {
        countdown();
        updateEncoders();
    }
}