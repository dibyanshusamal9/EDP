#define trigger_pin 13
#define echo_pin 12

double duration;
int distance;

int l, r;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  Serial.begin(9600);
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

void stop()
{
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  delay(50);
}

void anti_clockwise()
{
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}

void clockwise()
{
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}

// -------- MAIN LOOP --------

void loop()
{
  // -------- ULTRASONIC --------
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigger_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);
  distance = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // -------- OBSTACLE DETECTION --------
  if (distance <= 10)
  {
    stop();
    delay(500);
  }
  else
  {
    // -------- LINE FOLLOWING --------
    l = digitalRead(A0);
    r = digitalRead(A1);

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
      forward();  // default case
    }
  }
}