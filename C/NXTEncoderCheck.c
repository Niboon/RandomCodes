void speed (int time, int power, float &encSpeed, float &ultraSpeed)
{
  float origd = SensorValue[S2];
  nMotorEncoder[motorA] = 0;
  motor[motorA] = power;
  motor[motorC] = power;
  wait1Msec(time);
  motor[motorA] = 0;
  motor[motorC] = 0;
  float finald = SensorValue[S2];
  if(time != 0)
  {
    encSpeed = nMotorEncoder[motorA]/180.0 * PI * 1.5 / (time/1000.0);
    ultraSpeed = (origd - finald)/(time/1000.0);
  }
  else
  {
    encSpeed = 0;
    ultraSpeed = 0;
  }

}

task main()
{
  SensorType[S2] = sensorSONAR;
  float avgError = 0, error = 0;
  float encSpeed = 0;
  float ultraSpeed = 0;
  for (int i = 0; i < 4; i++)
  {
    while(nNxtButtonPressed == -1);
    while(nNxtButtonPressed != -1);
    speed(2000, 20 * (i + 1), encSpeed, ultraSpeed);
    error = 100 * (ultraSpeed - encSpeed)/encSpeed;
    nxtDisplayString(0, "Enc Speed: %f", encSpeed);
    nxtDisplayString(1, "Ult Speed: %f", ultraSpeed);
    nxtDisplayString(2, "Error: %f", error);
    avgError += error;
  }

    avgError /= 4;

    eraseDisplay();
    nxtDisplayString(0, "Avg Error: %f", avgError);
    wait10Msec(1000);
}
