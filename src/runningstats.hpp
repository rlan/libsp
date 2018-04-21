/**
 * Recoded from https://www.johndcook.com/blog/skewness_kurtosis/
 */
#ifndef RUNNINGSTATS_H_
#define RUNNINGSTATS_H_

#include <cmath>
#include <vector>
 
class RunningStats
{
public:
  RunningStats()
  {
    clear();
  }

  void clear()
  {
    n = 0;
    M1 = M2 = M3 = M4 = 0.0;
  }
  
  void push(double x)
  {
    double delta, delta_n, delta_n2, term1;
 
    long long n1 = n;
    n++;
    delta = x - M1;
    delta_n = delta / n;
    delta_n2 = delta_n * delta_n;
    term1 = delta * delta_n * n1;
    M1 += delta_n;
    M4 += term1 * delta_n2 * (n*n - 3*n + 3) + 6 * delta_n2 * M2 - 4 * delta_n * M3;
    M3 += term1 * delta_n * (n - 2) - 3 * delta_n * M2;
    M2 += term1;
  }
  
  long long count() const
  {
    return n;
  }
  
  double mean() const
  {
    return M1;
  }

  double variance() const
  {
    return M2/(n-1.0);
  }

  double standard_deviation() const
  {
    return sqrt( variance() );
  }

  double skewness() const
  {
    return sqrt(double(n)) * M3/ pow(M2, 1.5);
  }

  double kurtosis() const
  {
    return double(n)*M4 / (M2*M2) - 3.0;
  }

  friend RunningStats operator+(const RunningStats a, const RunningStats b);

  RunningStats& operator+=(const RunningStats &rhs)
  { 
    RunningStats combined = *this + rhs;
    *this = combined;
    return *this;
  }
  

private:
  long long n;
  double M1, M2, M3, M4;
};

RunningStats operator+(const RunningStats a, const RunningStats b)
{
  RunningStats combined;

  combined.n = a.n + b.n;
    
  double delta = b.M1 - a.M1;
  double delta2 = delta*delta;
  double delta3 = delta*delta2;
  double delta4 = delta2*delta2;
    
  combined.M1 = (a.n*a.M1 + b.n*b.M1) / combined.n;
    
  combined.M2 = a.M2 + b.M2 + 
                delta2 * a.n * b.n / combined.n;
    
  combined.M3 = a.M3 + b.M3 + 
                delta3 * a.n * b.n * (a.n - b.n)/(combined.n*combined.n);
  combined.M3 += 3.0*delta * (a.n*b.M2 - b.n*a.M2) / combined.n;
    
  combined.M4 = a.M4 + b.M4 + delta4*a.n*b.n * (a.n*a.n - a.n*b.n + b.n*b.n) / 
                (combined.n*combined.n*combined.n);
  combined.M4 += 6.0*delta2 * (a.n*a.n*b.M2 + b.n*b.n*a.M2)/(combined.n*combined.n) + 
                4.0*delta*(a.n*b.M3 - b.n*a.M3) / combined.n;
    
  return combined;
}


#endif // RUNNINGSTATS_H_
