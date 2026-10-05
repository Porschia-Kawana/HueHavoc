#include <math.h>


// ==========================================
// START GAME
// ==========================================

void startGame() {

    started = true;
    gameOver = false;

    roundsCompleted = 0;
    totalPoints = 0;
    perfectMatches = 0;

    // Reset allocated time
    roundTime = STARTING_TIME;

    targetGenerated = false;

    playerRed = 0;
    playerGreen = 0;
    playerBlue = 0;

    // Turn all LEDs off
    turnPlayerLightOff();
    turnTargetLightOff();

    lcd.clear();

    // ==========================================
    // STARTING COUNTDOWN
    // ==========================================

    for (int i = 3; i > 0; i--) {
        lcd.setCursor(0, 0);
        lcd.print("Get ready!      ");

        lcd.setCursor(0, 1);
        lcd.print("Starting in ");
        lcd.print(i);
        lcd.print("   ");

        delay(1000);
    }

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Go!");

    delay(500);

    // ==========================================
    // FIRST ROUND
    // ==========================================

    playerRed = 0;
    playerGreen = 0;
    playerBlue = 0;

    // Generate first target
    generateTargetRGB();

    // Start countdown using allocated time
    startCountdown(roundTime);

    displayTopText("Find the RGB!");

    displayTimer(remainingTime);

    updatePlayerRGB();

    Serial.println();
    Serial.println("===== NEW GAME =====");

    Serial.print("Starting round time: ");
    Serial.println(roundTime);
}

// ==========================================
// SUBMIT ANSWER
// ==========================================

void submitAnswer() {
    if (gameOver) {
        return;
    }

    // Stop countdown
    countdownRunning = false;

    // Count completed round
    roundsCompleted++;

    // ==========================================
    // CALCULATE RGB DISTANCE
    // ==========================================

    long redDifference = playerRed - targetRed;
    long greenDifference = playerGreen - targetGreen;
    long blueDifference = playerBlue - targetBlue;
    float distance =
        sqrt(
            (redDifference * redDifference) +
            (greenDifference * greenDifference) +
            (blueDifference * blueDifference)
        );

    int roundedDistance = round(distance);

    // ==========================================
    // CALCULATE SCORE
    // ==========================================

    int roundScore = 0;

    if (distance < 50) {
        // Perfect match
        roundScore = 10;
    } else if (distance < 75) {
        // So close
        roundScore = 9;
    } else if (distance < 100) {
        roundScore = 8;
    } else if (distance < 125) {
        roundScore = 7;
    } else if (distance < 150) {
        roundScore = 6;
    } else if (distance < 175) {
        roundScore = 5;
    } else if (distance < 200) {
        roundScore = 3;
    } else if (distance < 225) {
        roundScore = 1;
    } else {
        roundScore = 0;
    }

    // ==========================================
    // COUNT PERFECT MATCHES
    // ==========================================

    if (roundScore == 10) {
        perfectMatches++;
    }

    // ==========================================
    // ADD SCORE
    // ==========================================

    totalPoints += roundScore;

    // ==========================================
    // SERIAL OUTPUT
    // ==========================================

    Serial.println();
    Serial.println("===== ANSWER =====");

    Serial.print("Player RGB: ");
    Serial.print(playerRed);
    Serial.print(", ");
    Serial.print(playerGreen);
    Serial.print(", ");
    Serial.println(playerBlue);

    Serial.print("Target RGB: ");
    Serial.print(targetRed);
    Serial.print(", ");
    Serial.print(targetGreen);
    Serial.print(", ");
    Serial.println(targetBlue);

    Serial.print("Distance: ");
    Serial.println(roundedDistance);

    Serial.print("Round score: ");
    Serial.println(roundScore);

    Serial.print("Perfect matches: ");
    Serial.println(perfectMatches);

    Serial.print("Total points: ");
    Serial.println(totalPoints);

    // ==========================================
    // WIN CONDITION
    // ==========================================

    if (roundsCompleted > 99 || totalPoints > 999) {

        gameOver = true;
        countdownRunning = false;

        turnPlayerLightOff();
        turnTargetLightOff();

        displayPlayerWon();

        Serial.println();
        Serial.println("===== PLAYER WON =====");

        return;
    }

    if (roundScore == 10) {
        // ==========================================
        // PERFECT MATCH
        // ==========================================
        Serial.println("PERFECT MATCH!");
        displayPerfectResult(roundScore);

        // Add 5 seconds to next round
        roundTime += WIN_TIME_BONUS;

        // Maximum of 90 seconds
        if (roundTime > MAX_TIME) {
            roundTime = MAX_TIME;
        }

        Serial.print("Next round time: ");
        Serial.println(roundTime);

        // Perfect match displayed for 3 seconds
        delay(3000);
    } else if (roundScore == 9) {
        // ==========================================
        // SO CLOSE
        // ==========================================

        Serial.println("SO CLOSE!");
        displaySoCloseResult(roundScore);

        // Add 5 seconds to next round
        roundTime += WIN_TIME_BONUS;

        // Maximum of 90 seconds
        if (roundTime > MAX_TIME) {
            roundTime = MAX_TIME;
        }

        Serial.print("Next round time: ");
        Serial.println(roundTime);

        // So Close displayed for 3 seconds
        delay(3000);
    } else {
        // ==========================================
        // MISS
        // ==========================================

        Serial.println("NOT A PERFECT MATCH");
        displayMissResult(roundedDistance, roundScore);

        // ======================================
        // REDUCE NEXT ROUND TIME
        // ======================================

        if (roundTime <= LOSE_TIME_PENALTY) {
            roundTime = 0;
            countdownRunning = false;
            gameOver = true;

            Serial.println();
            Serial.println("===== GAME OVER =====");

            Serial.print("Rounds: ");
            Serial.println(roundsCompleted);

            Serial.print("Perfect matches: ");
            Serial.println(perfectMatches);

            Serial.print("Points: ");
            Serial.println(totalPoints);

            // Keep distance screen visible
            // for 5 seconds
            delay(5000);

            turnPlayerLightOff();
            turnTargetLightOff();

            displayGameOver();
            return;
        }

        roundTime -= LOSE_TIME_PENALTY;

        Serial.print("Next round time: ");
        Serial.println(roundTime);

        // Distance screen displayed for 5 seconds
        delay(5000);
    }

    // ==========================================
    // TURN ALL LEDS OFF
    // ==========================================

    playerRed = 0;
    playerGreen = 0;
    playerBlue = 0;

    turnPlayerLightOff();
    turnTargetLightOff();

    // ==========================================
    // 2 SECOND BREAK
    // ==========================================

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Next round!");

    for (int i = 2; i > 0; i--) {
        lcd.setCursor(0, 1);
        lcd.print("Starting in ");
        lcd.print(i);
        lcd.print("   ");

        delay(1000);
    }

    // ==========================================
    // START NEXT ROUND
    // ==========================================

    // Reset player RGB
    playerRed = 0;
    playerGreen = 0;
    playerBlue = 0;

    turnPlayerLightOff();

    // Generate new target
    generateTargetRGB();

    // Target LED is now ON
    // Player LED remains OFF
    displayTopText("Find the RGB!");

    // Start next round using roundTime
    startCountdown(roundTime);

    // Show player RGB as 000, 000, 000
    displayRGB();

    Serial.println();
    Serial.print("Next round started with ");
    Serial.print(roundTime);
    Serial.println(" seconds.");
}