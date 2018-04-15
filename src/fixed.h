/**\file
 * \brief Fixed-point class
 *
 * \author Rick Lan
 * \copyright See LICENSE for license.
 */

#ifndef FIXED_H_
#define FIXED_H_

#include <cstddef>

#include <algorithm>

#include "estimator.h"


/**Fixed-point class
 * TODO fix estimator const
 */
template<
  size_t WL = 32, 
  size_t IL = (WL-1), 
  bool SIGNED = true, 
  bool OWARN = false, 
  bool UWARN = false, 
  bool WWARN = false, 
  bool STATS = false
  >
class Fixed
{
  public:
    Fixed()
    { }
    Fixed(double x)
    : q_(quantize(x))
    {
      if (STATS) updateStats(x);
    }
    Fixed(const Fixed &rhs)
    : q_(rhs) // no need to quantize because already quantized
    {
      if (STATS) updateStats(rhs);
    }

    // copy assignment
    Fixed& operator=(Fixed rhs)
    {
      q_ = quantize(rhs);
      if (STATS) updateStats(rhs);
      return *this;
    }

    // copy assignment
    Fixed& operator=(const Fixed& rhs)
    {
      if (&rhs != this) {
        q_ = quantize(rhs);
        if (STATS) updateStats(rhs);
      }
      return *this;
    }

    //lhs double() //TODO proxy object?

    // implicit type conversion to double
    operator double() const { return q_; }

    size_t overflow(void) const { return overflow_count_; }
    size_t underflow(void) const { return underflow_count_; }
    size_t wraparound(void) const { return wrap_around_count_; }
    double min(void) const { return min_; }
    double max(void) const { return max_; }
    double mean(void) const { return mean_estimate_.estimate(); }
    double variance(void) const { return variance_estimate_.estimate(); }

  protected:
    double quantize(double x)
    {
      if (STATS) updateStats(x);
      if (SIGNED)
        return quantizeSigned(x);
      else
        return quantizeUnsigned(x);;
    }

    void updateStats(double x)
    {
      min_ = std::min(min_, x);
      max_ = std::max(max_, x);
      mean_estimate_.record(x);
      variance_estimate_.record(x);
    }

    double q_; // quantized

    // statistics of quantization
    size_t overflow_count_;
    size_t underflow_count_;
    size_t wrap_around_count_;

    // statistics of input
    double min_;
    double max_;
    MeanEstimator<double> mean_estimate_;
    VarianceEstimator<double> variance_estimate_;

  private:
};

#endif //FIXED_H_
