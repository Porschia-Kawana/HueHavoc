#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;

// -------------------------
// BUTTON TYPES
// -------------------------

enum Button {
    NO_BUTTON,
    RED_PRESSED,
    GREEN_PRESSED
};

// -------------------------
// GAME SETTINGS
// -------------------------

const int STARTING_TIME = 60;          // Starting game time in seconds
const int WIN_TIME_BONUS = 5;          // Seconds added after a win
const int LOSE_TIME_PENALTY = 10;      // Seconds removed after a loss
const int RGB_TOLERANCE_PERCENT = 10;  // Allowed RGB error percentage

// -------------------------
// PLAYER RGB VALUES
// -------------------------

int playerRed = 0;
int playerGreen = 0;
int playerBlue = 0;

// -------------------------
// TARGET RGB VALUES
// -------------------------

int targetRed = 0;
int targetGreen = 0;
int targetBlue = 0;

// -------------------------
// COUNTDOWN VARIABLES
// -------------------------

unsigned long countdownStartTime;
unsigned long remainingTime;

bool countdownRunning = false;

// -------------------------
// GAME VARIABLES
// -------------------------

bool started = false;
bool gameOver = false;

unsigned long gameStartTime;
int roundsWon = 0;

// -------------------------
// SETUP
// -------------------------

void setup() {

    Serial.begin(9600);

    setupLEDPins();
    setupLCD();
    setupButtons();
    setupEncoders();

    randomSeed(analogRead(A0));
}

// -------------------------
// LOOP
// -------------------------

void loop() {

    int button = checkButtons();

    if (button == GREEN_PRESSED) {
        // Start a new game
        if (!started) {
            startGame();
        }
        // Submit current answer
        else if (!gameOver) {
            submitAnswer();
        }
    }

    if (button == RED_PRESSED) {
        // Reserved for future use
    }

    // -------------------------
    // GAME RUNNING
    // -------------------------

    if (started && !gameOver) {
        countdown();
        updateEncoders();
    }
}