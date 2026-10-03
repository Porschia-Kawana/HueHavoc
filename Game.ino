// -------------------------
// START GAME
// -------------------------

void startGame() {
    started = true;
    gameOver = false;

    // Reset rounds won
    roundsWon = 0;

    // -------------------------
    // READY MESSAGE
    // -------------------------

    displayTopText("Ready Set Go!");
    delay(2000);

    // -------------------------
    // 3 SECOND COUNTDOWN
    // -------------------------

    for (int i = 3; i > 0; i--) {
        displayTopText("Get ready!");
        setTimerNumbers(
            String(i / 10),
            String(i % 10)
        );
        delay(1000);
    }

    // -------------------------
    // RESET PLAYER RGB
    // -------------------------

    playerRed = 0;
    playerGreen = 0;
    playerBlue = 0;

    // -------------------------
    // GENERATE TARGET
    // -------------------------

    generateTargetRGB();

    // -------------------------
    // START GAME TIMER
    // -------------------------

    startCountdown(STARTING_TIME);
    gameStartTime = millis();
    lastPrint = 0;

    // -------------------------
    // GAME STARTED
    // -------------------------

    displayTopText("Find the RGB!");
    updatePlayerRGB();
}


// -------------------------
// SUBMIT ANSWER
// -------------------------

void submitAnswer() {

    Serial.println("ANSWER SUBMITTED");

    Serial.print("Player R: ");
    Serial.println(playerRed);

    Serial.print("Player G: ");
    Serial.println(playerGreen);

    Serial.print("Player B: ");
    Serial.println(playerBlue);

    Serial.print("Target R: ");
    Serial.println(targetRed);

    Serial.print("Target G: ");
    Serial.println(targetGreen);

    Serial.print("Target B: ");
    Serial.println(targetBlue);

    // -------------------------
    // CHECK RGB VALUES
    // -------------------------

    bool redCorrect =
        withinTolerance(
            playerRed,
            targetRed
        );

    bool greenCorrect =
        withinTolerance(
            playerGreen,
            targetGreen
        );

    bool blueCorrect =
        withinTolerance(
            playerBlue,
            targetBlue
        );

    // -------------------------
    // RESULT
    // -------------------------

    if (redCorrect &&
        greenCorrect &&
        blueCorrect) {
        winRound();
    } else {
        loseRound();
    }
}

// -------------------------
// CHECK RGB TOLERANCE
// -------------------------

bool withinTolerance(
    int playerValue,
    int targetValue
) {

    int tolerance =
        (targetValue * RGB_TOLERANCE_PERCENT) / 100;

    return
        playerValue >= targetValue - tolerance &&
        playerValue <= targetValue + tolerance;
}

// -------------------------
// WIN ROUND
// -------------------------

void winRound() {

    Serial.println("WIN!");
    roundsWon++;
    displayTopText("You got it!");

    // -------------------------
    // ADD TIME
    // -------------------------

    remainingTime += WIN_TIME_BONUS;
    countdownStartTime = millis();
    countdownRunning = true;

    // -------------------------
    // NEW TARGET
    // -------------------------

    generateTargetRGB();

    // -------------------------
    // RESET PLAYER
    // -------------------------

    playerRed = 0;
    playerGreen = 0;
    playerBlue = 0;

    updatePlayerRGB();
    delay(1000);
    displayTopText("Find the RGB!");
}

// -------------------------
// LOSE ROUND
// -------------------------

void loseRound() {
    Serial.println("LOSE!");
    displayTopText("Not quite!");

    // -------------------------
    // REMOVE TIME
    // -------------------------

    if (remainingTime > LOSE_TIME_PENALTY) {
        remainingTime -= LOSE_TIME_PENALTY;
        countdownStartTime = millis();
        countdownRunning = true;
    } else {
        remainingTime = 0;
        countdownRunning = false;
        gameOver = true;
    }

    // -------------------------
    // RESET PLAYER
    // -------------------------

    playerRed = 0;
    playerGreen = 0;
    playerBlue = 0;

    updatePlayerRGB();

    // -------------------------
    // GAME OVER
    // -------------------------

    if (gameOver) {
        delay(1000);
        displayGameOver();
        Serial.println("GAME OVER");
        Serial.print("Rounds won: ");
        Serial.println(roundsWon);
        return;
    }

    // -------------------------
    // NEW TARGET
    // -------------------------

    generateTargetRGB();
    delay(1000);
    displayTopText("Find the RGB!");
}