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

// ==========================================
// SETUP LCD
// ==========================================

void setupLCD() {
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Play Hue Havoc!");
    lcd.setCursor(0, 1);
    lcd.print("                ");
}

// ==========================================
// DISPLAY TOP TEXT
// ==========================================

void displayTopText(String message) {
    if (message.length() > 13) {
        message = message.substring(0, 13);
    }

    lcd.setCursor(0, 0);
    lcd.print(message);

    for (int i = message.length(); i < 13; i++) {
        lcd.print(" ");
    }
}

// ==========================================
// RANDOM MESSAGE
// ==========================================

void displayRandomMessageOfEncouragement() {
    int number = random(0, sizeof(messages) / sizeof(messages[0]));
    displayTopText(messages[number]);
}

// ==========================================
// DISPLAY PLAYER RGB
// ==========================================

void displayRGB() {
    lcd.setCursor(0, 1);
    lcd.print("R");

    if (playerRed < 100) {
        lcd.print("0");
    }

    if (playerRed < 10) {
        lcd.print("0");
    }

    lcd.print(playerRed);
    lcd.print(" G");

    if (playerGreen < 100) {
        lcd.print("0");
    }

    if (playerGreen < 10) {
        lcd.print("0");
    }

    lcd.print(playerGreen);
    lcd.print(" B");

    if (playerBlue < 100) {
        lcd.print("0");
    }

    if (playerBlue < 10) {
        lcd.print("0");
    }

    lcd.print(playerBlue);
}

// ==========================================
// DISPLAY TIMER
// ==========================================

void displayTimer(unsigned long seconds) {
    int tens = (seconds / 10) % 10;
    int ones = seconds % 10;

    lcd.setCursor(13, 0);
    lcd.print(tens);

    lcd.setCursor(14, 0);
    lcd.print(ones);

    lcd.setCursor(15, 0);
    lcd.print("s");
}

// ==========================================
// PERFECT RESULT
// ==========================================

void displayPerfectResult(int score) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Perfect match!");
    lcd.setCursor(0, 1);
    lcd.print("PTS: ");
    lcd.print(score);
}

// ==========================================
// SO CLOSE RESULT
// ==========================================

void displaySoCloseResult(int score) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("So Close!");
    lcd.setCursor(0, 1);
    lcd.print("PTS: ");
    lcd.print(score);
}

// ==========================================
// MISSED RESULT
// ==========================================

void displayMissResult(int distance, int score) {
    lcd.clear();
    // Line 1
    lcd.setCursor(0, 0);
    lcd.print("Dist from target");
    // Line 2
    lcd.setCursor(0, 1);
    lcd.print(distance);
    lcd.setCursor(10, 1);
    lcd.print("PTS:");
    lcd.print(score);
}

// ==========================================
// GAME OVER
// ==========================================

void displayGameOver() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game over!");
    lcd.setCursor(0, 1);
    lcd.print("R:");
    lcd.print(roundsCompleted);
    lcd.print(" W:");
    lcd.print(perfectMatches);
    lcd.print(" PTS:");
    lcd.print(totalPoints);
}

// ==========================================
// PLAYER WON
// ==========================================

void displayPlayerWon() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Congratulations,");
    lcd.setCursor(0, 1);
    lcd.print("You Won!");
}