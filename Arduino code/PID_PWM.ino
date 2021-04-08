void readsensor_calculate_pid_pwm()
{ 
  readSensors();
  calculateError();
  pidCalculations();
  changeMotorSpeed();
}
void pidCalculations() 
{
  pTerm = kp * error;
  integral += error;
  iTerm = ki * integral;
  derivative = error - previousError;
  dTerm = kd * derivative;
  output = pTerm + iTerm + dTerm;
  previousError = error;
}
void changeMotorSpeed() 
{
  //Change motor speed of both motors accordingly
  motor1newSpeed = motor1Speed + output;
  motor2newSpeed = motor2Speed - output;
  if(motor1newSpeed<0)  motor1newSpeed=0;
  if(motor2newSpeed<0)  motor2newSpeed=0;
  //Constrain the new speed of motors to be between the range 0-255
  constrain(motor1newSpeed, 0, maximumspeed);
  constrain(motor2newSpeed, 0, maximumspeed);
  //Set new speed, and run motors in forward direction
  analogWrite(motor1pwmPin, motor1newSpeed);
  analogWrite(motor2pwmPin, motor2newSpeed);
}
