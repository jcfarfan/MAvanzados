#include <stdio.h>
#include <math.h>

typedef double (*derivative)(double t, double y);
double RK45_step1(double step, double t, double y, derivative dev);
double RK45_step2(double step, double t, double y, derivative dev);
double R(double step, double t, double y, derivative dev);
double delta(double R, double epsilon);
double func_y(double t, double y);

int main(void){
  double y_RK2;
  double y_RK4;
  double w,w1,w2,r1,r2,Re,del;
  double epsilon;
  double t;
  int i;

  double T = 2.0;
  double step = 0.2;
  int n_step = (int)(T/step);

  epsilon = 0.00001;
  t=0.0;
  y_RK2=1.0;
  y_RK4=1.0;
  w = 0.5;
  for(i=0;i<n_step;i++){
    r1 = RK45_step1(step,  t, w, func_y);
    r2 = RK45_step2(step,  t, w, func_y);
    t+= step;
    w1 = w + r1;
    w2 = w + r2;
    Re = R(step, t, w, func_y);
    del = delta(Re, epsilon);
    if(Re<=epsilon){
      t += step;
      w = w1;
      step = step*del;
      printf("%f %.15e\n", t, w);
    }
    else{
      step = step*del;
    }
  }
  return 0;
}

double RK45_step1(double step, double t, double y, derivative dev){
  double k1,k2,k3,k4,k5,k6;
  double y_step;
  k1 = step * dev(t,y);
  k2 = step * dev(t+step*0.25,y+step*0.25);
  k3 = step * dev(t+step*0.375,y+(3.0/32.0)*k1+(9.0/32.0)*k2);
  k4 = step * dev(t+step*(12.0/13.0),y+(1932.0/2197.0)*k1-(7200.0/2197.0)*k2+(7296.0/2197.0)*k3);
  k5 = step * dev(t+step,y+(439.0/216.0)*k1-8*k2+(3680.0/513.0)*k3-(845.0/4104.0)*k4);
  k6 = step * dev(t+step*0.5,y-(8.0/27.0)*k1+2*k2-(3544.0/2565.0)*k3+(1859.0/4104.0)*k4-(11.0/40.0)*k5);
  y_step = y+(25.0/216.0)*k1+(1408.0/2565.0)*k3+(2197.0/4104.0)*k4-(1.0/50.0)*k5;
  return y_step;
}

double RK45_step2(double step, double t, double y, derivative dev){
  double k1,k2,k3,k4,k5,k6;
  double y_step;
  k1 = step * dev(t,y);
  k2 = step * dev(t+step*0.25,y+step*0.25);
  k3 = step * dev(t+step*0.375,y+(3.0/32.0)*k1+(9.0/32.0)*k2);
  k4 = step * dev(t+step*(12.0/13.0),y+(1932.0/2197.0)*k1-(7200.0/2197.0)*k2+(7296.0/2197.0)*k3);
  k5 = step * dev(t+step,y+(439.0/216.0)*k1-8*k2+(3680.0/513.0)*k3-(845.0/4104.0)*k4);
  k6 = step * dev(t+step*0.5,y-(8.0/27.0)*k1+2*k2-(3544.0/2565.0)*k3+(1859.0/4104.0)*k4-(11.0/40.0)*k5);
  y_step = y+(16.0/35.0)*k1+(6656.0/12825.0)*k3+(28561.0/56430.0)*k4-(9.0/50.0)*k5+(2.0/55.0)*k6;
  return y_step;
}


double R(double step, double t, double y, derivative dev){
  double R,r1,r2;
  r1 = RK45_step1(step,  t,  y, dev);
  r2 = RK45_step2(step, t,  y,  dev);
  R = (1.0/step)*abs(r1-r2);
  return R;
}

double delta(double R, double epsilon){
  double delta;
  delta = 0.84*pow(epsilon/R,0.25);
  return delta;
}

double func_y(double t, double y){
  double v;
  v = y-t*t+1;
  return v;
}
