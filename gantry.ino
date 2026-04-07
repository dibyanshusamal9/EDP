#define trigger_pin 13
#define echo_pin 12

double duration;
int distance;

int count = 0, l, r;
int pin = 4;
int flag = 0;

unsigned long value = 0;
unsigned long st = 0, endt;

void setup()
{
  Serial.begin(9600);

  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(pin, INPUT);

  st = millis();   // FIXED initialization
}

// -------- MOTOR FUNCTIONS --------

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

void stop_buggy()
{
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

// -------- MAIN LOOP --------

void loop()
{
  if ((Serial.available() && Serial.read() == 'd') || flag == 1)
  {
    flag = 1;

    // -------- ULTRASONIC --------
    digitalWrite(trigger_pin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_pin, LOW);

    duration = pulseIn(echo_pin, HIGH);
    distance = duration * 0.0343 / 2;

    if (distance <= 10)
    {
      stop_buggy();
      delay(500);
    }

    // -------- GANTRY DETECTION --------
    if (digitalRead(pin) > 0)
    {
      value = pulseIn(pin, HIGH);

      Serial.print("Value = ");
      Serial.println(value);

      if (value > 1500 && value < 2000)
      {
        Serial.println("Gantry 1 crossed");
        stop_buggy();
        delay(1000);
      }

      else if (value > 2500 && value < 3000)
      {
        Serial.println("Gantry 2 crossed");
        stop_buggy();
        delay(1000);
      }

      else if (value > 500 && value < 1000)
      {
        Serial.println("Gantry 3 crossed");
        stop_buggy();
        delay(1000);
      }
    }

    // -------- LINE FOLLOWING --------
    l = digitalRead(A0);
    r = digitalRead(A1);

    if (l == 1 && r == 1)
      forward();
    else if (l == 0 && r == 1)
      left();
    else if (l == 1 && r == 0)
      right();
    else if (l == 0 && r == 0)
    {
      // -------- COUNT LOGIC --------
      endt = millis();
      if (endt - st > 1000)
      {
        count++;
        st = millis();
      }

      if (count == 1) forward();
      if (count == 2) left();
      if (count == 3) forward();
      if (count == 4) left();
      if (count == 5) forward();

      if (count > 5)
      {
        stop_buggy();
        Serial.println("Stop");
        flag = 0;
      }
    }
  }
}