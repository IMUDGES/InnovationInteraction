// vcc 5,6,13
//gnd 9,2,10
class ultrasonic
{

};
int lefton = 26; //in3
int leftback = 28;//in4
int righton = 22;//in1
int rightback = 24;//in2
int TrigPin[5] = { 7, 12, 5 };
int EchoPin[5] = { 8, 11, 4 };
int Length[10]; //每个超声波传感器的距离
//----------------------------------------------------------
void left(int t = 0)
{
  digitalWrite(lefton, 1);
  digitalWrite(leftback, 0);
  digitalWrite(righton, 0);
  digitalWrite(rightback, 1);
  delay(t);
}
void right(int t = 0)
{
  digitalWrite(lefton, 0);
  digitalWrite(leftback, 1);
  digitalWrite(righton, 1);
  digitalWrite(rightback, 0);
  delay(t);
}
void forword(int t = 0)
{
  digitalWrite(lefton, 1);
  digitalWrite(leftback, 0);
  digitalWrite(righton, 1);
  digitalWrite(rightback, 0);
  delay(t);
}
void back(int t = 0)
{
  digitalWrite(lefton, 0);
  digitalWrite(leftback, 1);
  digitalWrite(righton, 0);
  digitalWrite(rightback, 1);
  delay(t);
}
void stop(int t = 0)
{
  digitalWrite(lefton, 0);
  digitalWrite(leftback, 0);
  digitalWrite(righton, 0);
  digitalWrite(rightback, 0);
  delay(t);
}
float get_cm(int i = 0)
{
  digitalWrite(TrigPin[i], LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin[i], HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin[i], LOW);
  // 检测脉冲宽度，并计算出距离
  float distance = pulseIn(EchoPin[i], HIGH) / 58.00;
  Serial.print(i);
  Serial.print("    ");
  Serial.println(distance);
  return distance;
}
void judge()  //走出坑
{
  if (get_cm(0)<30)
  {
    stop();
    int l = get_cm(1);
    int r = get_cm(2);
    if (l<40 && r<40)
    {
      back(1000);
      judge();
    }
    else
    {
      if (l>r)
        left(500);
      else
        right(500);
        return;
    }

  }

}
int VCC[3] = { 5, 6, 13 };
int gnd[3] = { 3, 9, 10 };
//**************************************************************
void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i <= 2; i++)
  {
    digitalWrite(VCC[i], 1);
    digitalWrite(gnd[i], 0);
  }
  for (int i = 0; i <= 4; i++)
  {
    pinMode(TrigPin[i], OUTPUT);
    pinMode(EchoPin[i], INPUT);
  }
  pinMode(lefton, OUTPUT);
  pinMode(leftback, OUTPUT);
  pinMode(righton, OUTPUT);
  pinMode(rightback, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  forword();
  judge();
}