// VARIABLES
String previousMessage = "";
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
    "Hue know it!",
};

// FUNCTIONS
void setupLCD() {
    lcd.begin(16, 2);
    displayTopText("Play Hue Havoc!");
    setRGB();
}

void displayTopText(String message) {

    if (message == previousMessage) {
        return;
    }

    previousMessage = message;

    if (message.length() > 16) {
        message = message.substring(0, 16);
    }

    while (message.length() < 13) {
        message += " ";
    }

    lcd.setCursor(0, 0);
    lcd.print(message);
}

void displayRandomMessageOfEncouragement(){
    int number = random(1, 15);
    displayTopText(messages[number]);
}

void setRGB(){
    lcd.setCursor(0, 1);
    lcd.print("R000 G000 B000");
}

void setTimerNumbers(String tens, String ones) {
    lcd.setCursor(13, 0);
    lcd.print(tens);
    lcd.setCursor(14, 0);
    lcd.print(ones);
    lcd.setCursor(15, 0);
    lcd.print("s");
}
