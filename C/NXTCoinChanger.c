//Default Display Function
void initdisplay()
{
  eraseDisplay();
  nxtDisplayString(0, "Change Machine");
  nxtDisplayString(1, "Enter a $2, $5 or");
  nxtDisplayString(2, "$10 bill to");
  nxtDisplayString(3, "receive change in");
  nxtDisplayString(4, "loonies.");
}

//Identification of Note Function
int readbill()
{
  SensorType[S3] = sensorCOLORFULL;
  wait10Msec(15);
  if (SensorValue[S3] == 5) //red
    return 2;
  if (SensorValue[S3] == 3) //green
    return 5;
  if (SensorValue[S3] == 2) //blue
    return 10;
  return 0;
}

//Validity and Value of Note Function
bool calculate(int value)
{
  eraseDisplay();
  if (value == 2)
  {
      nxtDisplayString(0, "$2 will be");
      nxtDisplayString(1, "returned.");
      return true;
  }
  if (value == 5)
  {
      nxtDisplayString(0, "$5 will be");
      nxtDisplayString(1, "returned.");
      return true;
  }
  if (value == 10)
  {
      nxtDisplayString(0, "$10 will be");
      nxtDisplayString(1, "returned.");
      return true;
  }
  nxtDisplayString(0, "Unable to detect");
  nxtDisplayString(1, "valid bill.");
  return false;
}

//Reject Note Function
void reject()
{
  motor[motorA] = -75;
  wait10Msec(150);
  motor[motorA] = 0;
}

//Note Storage Function
//4.15 cm diameter of wheels
//Distance between sections of storage: Approximately 9 cm
//Initial location of container: edge offset 4.5 cm from acceptor
void storebill(int value)
{
  int i;
  nMotorEncoder[motorB] = 0;
  motor[motorB] = 50;
  if (value == 2)
    i = 1;
  else if (value == 5)
    i = 2;
  else
    i = 3;
  while (nMotorEncoder[motorB] < i*9/(PI*4.15)*360) ;
  motor[motorB] = 0;
  motor[motorA] = 75;
  wait10Msec(100);
  motor[motorA] = 0;
  motor[motorB] = -50;
  while (nMotorEncoder[motorB] > 0) ;
  motor[motorB] = 0;
}

//Coin Output Function
void coinout(int value)
{
  for (int i = 0; i < value; i++)
  {
      motor[motorC] = 100;
      wait10Msec(20);
      motor[motorC] = 0;
      wait10Msec(15);
      motor[motorC] = -100;
      wait10Msec(20);
      motor[motorC] = 0;
      wait10Msec(100);
  }
}

//User Confirmation Function
void confirm(int value)
{
  nxtDisplayString(2, "Press center");
  nxtDisplayString(3, "orange button to");
  nxtDisplayString(4, "confirm.");
  nxtDisplayString(5, "Press left or");
  nxtDisplayString(6, "right button to");
  nxtDisplayString(7, "cancel.");
  while (nNxtButtonPressed == -1) ;
  if (nNxtButtonPressed == 3)
  {
      eraseDisplay();
    nxtDisplayString(0, "Please wait...");
    storebill(value);
      coinout(value);
      eraseDisplay();
      nxtDisplayString(0, "Transaction");
      nxtDisplayString(1, "complete.");
  }
  else
  {
      eraseDisplay();
      nxtDisplayString(0, "Transaction");
      nxtDisplayString(1, "cancelled.");
      reject();
  }
}

//Note Acceptance Function
void takebill()
{
  SensorType[S1] = sensorSONAR;
  while (SensorValue[S1] > 15);
  time10[T1] = 0;
  motor[motorA] = 75;
  while (SensorValue[S1] < 15 || time10[T1] < 100)
    wait10Msec(10);
  motor[motorA] = 0;
  int value = readbill();
  if (!calculate(value))
    reject();
  else
    confirm(value);
  nxtDisplayString(2, "Elapsed time:");
  nxtDisplayString(3, "%0.2f s", time10[T1]/100.0);
  wait10Msec(300);
}

task main()
{
  while (1)
  {
      initdisplay();
      takebill();
  }
}
