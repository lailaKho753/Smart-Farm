#define KIPAS1 13
#define KIPAS2 12
#define PUMP 11
int firstVal, secondVal, thirdVal, fourthVal;
String myString;
char rdata;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial2.available() > 0 )
  {
    rdata = Serial2.read();
    myString = myString + rdata;
    // Serial.print(rdata);
    if ( rdata == '\n')
    {
      String l = getValue(myString, ';', 0);
      String m = getValue(myString, ';', 1);
      String n = getValue(myString, ';', 2);
      String o = getValue(myString, ';', 3);
      firstVal = l.toInt();
      secondVal = m.toInt();
      thirdVal = n.toInt();
      fourthVal = o.toInt();

      myString = "";
    }
    Serial.print(firstVal);
    Serial.print(secondVal);
    Serial.print(thirdVal);
    Serial.println(";");
    if (firstVal == 11) {
      digitalWrite(KIPAS1, HIGH);
    }
    else if (firstVal == 10) {
      digitalWrite(KIPAS1, LOW);
    }
    else if (firstVal == 21) {
      digitalWrite(KIPAS2, HIGH);
    }
    else if (firstVal == 20) {
      digitalWrite(KIPAS2, LOW);
    }
    else if (firstVal == 30) {
      digitalWrite(PUMP, HIGH);
    }
    else if (firstVal == 31) {
      digitalWrite(PUMP, LOW);
    }
  }
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
