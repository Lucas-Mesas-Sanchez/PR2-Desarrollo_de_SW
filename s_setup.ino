void on_setup() {

    pinMode(pinSensor, INPUT);
    pinMode(ledTemp, OUTPUT);
    pinMode(ledEmptyNuevas, OUTPUT);
    pinMode(ledFullMalas, OUTPUT);

    pinMode(btnRellenar, INPUT_PULLUP);
    pinMode(btnVaciar, INPUT_PULLUP);
    pinMode(btnEmergencia, INPUT_PULLUP);

    digitalWrite(ledTemp, LOW);
    digitalWrite(ledEmptyNuevas, LOW);
    digitalWrite(ledFullMalas, LOW);

}

