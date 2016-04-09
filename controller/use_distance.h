#if !defined(USE_DISTANCE) && defined(DISTANCE_TRIG) && defined(DISTANCE_ECHO)
#define USE_DISTANCE

double last_distance = 0.0;

void initDistance()
{
  pinMode(DISTANCE_ECHO, INPUT);
  pinMode(DISTANCE_TRIG, OUTPUT);
}

double getVelocity(double T) 
{
  return 331.0 + 0.6 * T;
}

double doDistance()
{
  digitalWrite(DISTANCE_TRIG, LOW); // 使发出发出超声波信号接口低电平2μs
  delayMicroseconds(2);
  digitalWrite(DISTANCE_TRIG, HIGH); // 使发出发出超声波信号接口高电平10μs，这里是至少10μs
  delayMicroseconds(10);
  digitalWrite(DISTANCE_TRIG, LOW);    // 保持发出超声波信号接口低电平
  double distance = pulseIn(DISTANCE_ECHO, HIGH);  // 读出脉冲时间
  last_distance = getVelocity(lasttemp) * distance / 1000000 * 100 / 2;   // 将脉冲时间转化为距离（单位：厘米）
  return last_distance;   //输出距离值   
}

#endif
