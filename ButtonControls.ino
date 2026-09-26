static bool pressed = 0;

bool startPressed() {
    if(!pressed){
        delay(2000);
        pressed = 1;
        return true;
    } 
    return false;
}