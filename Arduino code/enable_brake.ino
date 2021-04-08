void chaythang()
{
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
}
void chaylui()
{
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
}
void enable()
{
  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
}
void brake_off()
{
  digitalWrite(brk1, LOW);
  digitalWrite(brk2, LOW);
}
void brake_on()
{
  digitalWrite(brk1, HIGH);
  digitalWrite(brk2, HIGH);
}
