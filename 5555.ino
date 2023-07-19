#define B1A 9
#define B1B 6
#define A1A 5
#define A1B 3

//กำหนดขาของนังจอย ใช้ขาAnalog
const int joystick_x_pin = A0; 
const int joystick_y_pin = A1;

//ตัวแปรเก็บค่าของนังจอย
int x_adc_val, y_adc_val; //ค่าanalog
float x_volt, y_volt; 

//พวกมุม
int  B1Aspeed ,B1Bspeed,A1Aspeed,A1Bspeed; //มุมที่ใช้หมุน
int currentPos[4]; //เก็บมุมใหม่
int prevPos[4]={150,0,0,150}; //เก็บมุมเดิมและกำหนดเริ่มต้น
int motornum; //หมายเลขServo ที่กำหนดในฟช.




//หมุนมุมปัจจุบัน
void servodrive(int motornum,int motorPos)
{
  if (motornum == 0)
  {
    analogWrite(B1A, prevPos[0]);
    digitalWrite(B1B, LOW);
    digitalWrite(A1A, LOW);
    analogWrite(A1B, motorPos); 
    
  }
  else if (motornum == 1)
  {
    analogWrite(B1A, motorPos);
    digitalWrite(B1B, LOW);
    digitalWrite(A1A, LOW);
    analogWrite(A1B, prevPos[3]); 
  }

}


//เพิ่ม ลด
void servomotion(int  motornum,int motorPos)
{
  int i;
  currentPos[motornum] = motorPos;
  
  //เพิ่มอง
  if (prevPos[motornum] < currentPos[motornum])
  {
    for(i=prevPos[motornum] ; i < currentPos[motornum]; i++)
    {
    servodrive(motornum,i);
    delay(10);
    }
  }
  
  //ลดอง
  if (prevPos[motornum] > currentPos[motornum])
  {
    for(i=prevPos[motornum] ; i > currentPos[motornum]; i--)
    {
      servodrive(motornum,i);
      delay(10);
    }
  }
  
  prevPos[motornum] = currentPos[motornum];
}


void setup() 
{
    Serial.begin(9600); 
    pinMode(B1A, OUTPUT); 
    pinMode(B1B, OUTPUT); 
    pinMode(A1A, OUTPUT); 
    pinMode(A1B, OUTPUT);

    analogWrite(B1A, prevPos[0]);
    analogWrite(B1B, prevPos[1]);
    analogWrite(A1A, prevPos[2]);
    analogWrite(A1B, prevPos[3]);

    B1Aspeed = prevPos[0];
    B1Bspeed = prevPos[1];
    A1Aspeed = prevPos[2];
    A1Bspeed = prevPos[3];

  delay(1000);
    
}

void loop() 
{
  //ค่าของจอย
  x_adc_val = analogRead(joystick_x_pin); 
  y_adc_val = analogRead(joystick_y_pin);
  x_volt = ( ( x_adc_val * 5.0 ) / 1023 ); 
  y_volt = ( ( y_adc_val * 5.0 ) / 1023 ); 
  Serial.print("X_Vol = ");
  Serial.print(x_volt);
  Serial.print("\t");
  Serial.print("Y_Vol = ");
  Serial.println(y_volt);

     if ((x_volt<=2.60 && x_volt>=2.50) && (y_volt<=2.60 && y_volt>=2.50))
  {
    Serial.println("start");
    if(A1Bspeed < 150)
    { 
      A1Bspeed++;
    }
    else if (A1Bspeed > 150)
    { 
      A1Bspeed--;  
    }
    else
    {
      A1Bspeed=150;
    }
    
    if(B1Aspeed < 150)
    { 
      B1Aspeed++;
    }
    else if (A1Bspeed > 150)
    { 
      A1Bspeed--;  
    }
    else
    {
      B1Aspeed=150;
    }
    
    servomotion(0,A1Bspeed);
    servomotion(1,B1Aspeed);
    
  }
  
  //จอย ซ้าย ขวา
  
  //a230 ซ้าย
  if ((x_volt<=2.60 && x_volt>=2.40) && (y_volt<=0.1 && y_volt>=0.00))
  {
    if(A1Bspeed < 280)
    { 
      A1Bspeed++;
    }
    else
    {
      A1Bspeed=280;
    }
    
    servomotion(0,A1Bspeed);
   
  } 

  //a100 ขวา
  if ((x_volt<=2.60 && x_volt>=2.40) && (y_volt<=5.00 && y_volt>=4.90))
  {
     if(A1Bspeed > 130)
    { 
      A1Bspeed--;
    }
    else
    {
      A1Bspeed=130;
    }
    
    servomotion(0,A1Bspeed);
    
  }

  //b250 หน้า 
  if ((x_volt<=5.00 && x_volt>=4.90) && (y_volt<=2.60 && y_volt>=2.40))
  {
    if(B1Aspeed < 290)
    { 
      B1Aspeed++;
    }
    else
    {
      B1Aspeed=290;
    }
    
    servomotion(1,B1Aspeed);
  }

  //b130 หลัง
  if ((x_volt<=0.1 && x_volt>=0.00) && (y_volt<=2.60 && y_volt>=2.40))
  {
    if(B1Aspeed > 130)
    { 
      B1Aspeed--;
    }
    else
    {
      B1Aspeed=130;
    }
    
    servomotion(1,B1Aspeed);
    
 }
 delay(10);
}
