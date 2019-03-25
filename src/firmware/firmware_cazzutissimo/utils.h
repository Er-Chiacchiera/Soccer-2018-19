/**
 * utils.h
 **/

#pragma once

inline double clamp(double v, double m){
  if(v > m) return m;
  if(v < -m) return -m;
  return v;
}

inline double cconstrain(double x, double max, double min)
{
  if(x > max) return x - (max - min);
  if(x < min) return x + (max - min);
  return x;
}