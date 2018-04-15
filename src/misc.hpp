#ifndef MISC_HPP_
#define MISC_HPP_


#include "estimator.h"

template <class T>
class SignalStats
{
public:
  // constructure

  void record(T x)
  {
    mean_estimator_.record(x);
    variance_estimator_record(x);
    min_ = std::min(min_, x);
    max_ = std::max(max_, x);
  }

  void reset(void)
  {
    mean_estimator_.reset();
    variance_estimator_.reset();
    min_ = T(0);
    max_ = T(0);
  }

  size_t count(void) const { return mean_estimator_.count(); }
  T mean(void) const { return mean_estimator_.estimate(); }
  T variance(void) const { return variance_estimator_.estimate(); }
  T min(void) const { return min_; }
  T max(void) const { return max_; }
protected:
  MeanEstimator<T> mean_estimator_;
  VarianceEstimator<T> variance_estimator_;
  T min_;
  T max_;
private:
};

#endif //MISC_HPP_
