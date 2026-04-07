int l, r;

void setup() 
{
    pinMode(A0, INPUT); // Left sensor
    pinMode(A1, INPUT); // Right sensor

    pinMode(5, OUTPUT); // Motor pins
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
}

// ================= MOTOR FUNCTIONS =================

void forward() 
{
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
}

void backward() 
{
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
}

void right() 
{
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
}

void left() 
{
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
}

void stop() 
{
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
}

void clockwise() 
{
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
}

void anti_clockwise() 
{
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
}

// ================= MAIN LOOP =================

void loop() 
{
    l = digitalRead(A0); // LEFT sensor
    r = digitalRead(A1); // RIGHT sensor

    if (l == 1 && r == 1) 
    {
        forward();
    } 
    else if (l == 0 && r == 1) 
    {
        left();
    } 
    else if (l == 1 && r == 0) 
    {
        right();
    } 
    else 
    {
        stop();
    }
}