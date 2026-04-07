const int trigPin = 13;
const int echoPin = 12;
const int pin = 4;   // Gantry receiver

long duration;
int distanceCm;

long st = 0;
int count = 0;
int flag = 0;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(A0, INPUT);  // Left IR
  pinMode(A1, INPUT);  // Right IR
  pinMode(pin, INPUT); // Gantry signal

  Serial.begin(9600);
  st = millis();
}

void loop()
{
  if (Serial.read() == 'C' || flag == 1)
  {
    flag = 1;

    // -------- GANTRY DETECTION --------
    if (digitalRead(pin) > 0)
    {
      int value = pulseIn(pin, HIGH);

      if (value > 2500 && value < 3000)
      {
        Serial.print("Gantry 1 Crossed - Value : ");
        Serial.println(value);
        stopp();
        delay(1000);
      }
      else if (value > 500 && value < 1000)
      {
        Serial.print("Gantry 2 Crossed - Value : ");
        Serial.println(value);
        stopp();
        delay(1000);
      }
    }

    // -------- ULTRASONIC SENSOR --------
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distanceCm = (duration * 0.034) / 2;

    if (distanceCm < 15)
    {
      stopp();
      delay(2000);
      Serial.print("Stop Object Detected : ");
      Serial.println(distanceCm);
    }

    // -------- LINE FOLLOWING --------
    int r = digitalRead(A0);
    int l = digitalRead(A1);

    if (l == 1 && r == 1)
      forward();
    else if (l == 1 && r == 0)
      left();
    else if (l == 0 && r == 1)
      right();
    else
    {
      // -------- LAP COUNTING --------
      long endt = millis();
      if (endt - st > 500)
      {
        count++;
        st = millis();

        Serial.print("Office Buggy count = ");
        Serial.println(count);

        if (count == 1)
          forward();
        else if (count == 2)
          left();
        else if (count == 3)
          forward();
        else if (count == 4)
        {
          left();
          delay(200);
        }
        else if (count == 5)
        {
          stopp();
          Serial.println("Buggy parked");
          flag = 0;
        }
      }
    }
  }
}

// -------- MOTOR CONTROL FUNCTIONS --------

void stopp()
{
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void forward()
{
  digitalWrite(5, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}

void left()
{
  digitalWrite(5, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}

void right()
{
  digitalWrite(5, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}