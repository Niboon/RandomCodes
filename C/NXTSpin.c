
int spinCount()
{
  nMotorEncoder[motorA] = 0;
  motor[motorA] = 50;
  motor[motorC] = -50;

  while(SensorValue[S2] <= 30);
  while(SensorValue[S2] > 30);

  motor[motorA] = 0;
  motor[motorC] = 0;

  return nMotorEncoder[motorA];
}



task main()
{
  SensorType[S2] = sensorSONAR;
  spinCount();

  int sum = 0;

  for(int i = 0; i < 4; i++)
  {
    int rev = spinCount();
    nxtDisplayString(i, "Count: %d", rev);
    sum += rev;
    wait10Msec(100);
  }

  float average = sum/4.0/360.0;

  nxtDisplayString( 6, "Average: %f per deg", average);
  wait10Msec(200);

}
