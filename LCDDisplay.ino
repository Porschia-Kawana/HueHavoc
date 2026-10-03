// -------------------------
// VARIABLES
// -------------------------

String messages[] = {
    "Hue got this!",
    "Think pink!",
    "Blue-tiful!",
    "Red-y to go!",
    "Hue yeah!",
    "Stay bright!",
    "Hue-larious!",
    "Tint-sane!",
    "Grape work!",
    "Hue Rule!",
    "Hue Rock!",
    "Stay Vivid!",
    "Go RGB!",
    "Tint-tastic!",
    "Dye happy!",
    "Hue know it!"
};

// -------------------------
// LCD SETUP
// -------------------------

void setupLCD() {
    lcd.begin(16, 2);
    displayTopText("Play Hue Havoc!");
    setRGB();
}


// -------------------------
// DISPLAY TOP ROW
// -------------------------

void displayTopText(String message) {
    if (message.length() > 13) {
        message = message.substring(0, 13);
    }

    while (message.length() < 13) {
        message += " ";
    }

    lcd.setCursor(0, 0);
    lcd.print(message);
}

// -------------------------
// RANDOM MESSAGE
// -------------------------

void displayRandomMessageOfEncouragement() {
    int number =
        random(
            0,
            sizeof(messages) / sizeof(messages[0])
        );
    displayTopText(messages[number]);
}

// -------------------------
// INITIAL RGB DISPLAY
// -------------------------

void setRGB() {
    lcd.setCursor(0, 1);
    lcd.print("R000 G000 B000");
}

// -------------------------
// DISPLAY PLAYER RGB
// -------------------------

void displayRGB() {
    lcd.setCursor(0, 1);

    // RED
    lcd.print("R");
    if (playerRed < 100) {
        lcd.print("0");
    }
    if (playerRed < 10) {
        lcd.print("0");
    }
    lcd.print(playerRed);

    // GREEN
    lcd.print(" G");
    if (playerGreen < 100) {
        lcd.print("0");
    }
    if (playerGreen < 10) {
        lcd.print("0");
    }
    lcd.print(playerGreen);

    // BLUE
    lcd.print(" B");
    if (playerBlue < 100) {
        lcd.print("0");
    }
    if (playerBlue < 10) {
        lcd.print("0");
    }
    lcd.print(playerBlue);
}

// -------------------------
// DISPLAY TIMER
// -------------------------

void setTimerNumbers(String tens, String ones) {
    lcd.setCursor(13, 0);
    lcd.print(tens);

    lcd.setCursor(14, 0);
    lcd.print(ones);

    lcd.setCursor(15, 0);
    lcd.print("s");
}

// -------------------------
// DISPLAY GAME OVER
// -------------------------

void displayGameOver() {
    // Top row
    lcd.setCursor(0, 0);
    lcd.print("Game over!      ");

    // Bottom row
    lcd.setCursor(0, 1);
    lcd.print("Rounds won: ");
    lcd.print(roundsWon);

    // Clear anything left over
    int length =
        12 + String(roundsWon).length();

    while (length < 16) {
        lcd.print(" ");
        length++;
    }
}