/**\file
 * \brief Estimator classes for random variables.
 *
 * TODO: partial template specialization for complex-valued variance estimator.
 *
 * \author Rick Lan
 * \copyright See LICENSE for license.
 */

#ifndef ESTIMATOR_H_
#define ESTIMATOR_H_


#include <cstdlib>
#include <complex>


/**Abstract base class of an estimator
 */
template<class T>
class Estimator
{
public:
	Estimator() { }
	virtual ~Estimator() { }
protected:
	virtual void reset(void) = 0;
	virtual void record(const T &x) = 0;
	virtual T estimate(void) = 0;
	virtual size_t count(void) = 0;
private:
};


/**Base class for a sample mean estimator
 * For scalar random variable and does not support vector random variable.
 */
template<class T>
class MeanEstimator : public Estimator<T>
{
public:
	MeanEstimator()
	: accumulator_(T(0))
	, count_(0)
	{ }
	
	virtual void record(const T &x)
	{
		accumulator_ = accumulator_ + x;
		count_++;
	}
	
	virtual T estimate(void)
	{
		return accumulator_ / static_cast<T>(count_);
	}
	
	virtual void reset(void)
	{
		accumulator_ = T(0);
		count_ = 0;
	}
	
	virtual size_t count(void)
	{
		return count_;
	}
	
protected:
	T accumulator_;
	size_t count_;
private:
};


/**Base class for a sample variance estimator
 */
template<class T>
class VarianceEstimator : public MeanEstimator<T>
{
public:
	VarianceEstimator()
	: mean_(T(0))
	, unbiased_(true)
	{ }
	
	VarianceEstimator(const T &mean, bool unbiased = true)
	: mean_(mean)
	, unbiased_(unbiased)
	{ }
	
	virtual void record(const T &x)
	{
		MeanEstimator<T>::accumulator_ = MeanEstimator<T>::accumulator_ + (x - mean_)*(x - mean_);
		MeanEstimator<T>::count_++;
	}
	
	virtual T estimate(void)
	{
		if (unbiased_) {
			return MeanEstimator<T>::accumulator_ / static_cast<T>(MeanEstimator<T>::count_ - 1);
		} else {
			return MeanEstimator<T>::accumulator_ / static_cast<T>(MeanEstimator<T>::count_);
		}
	}
	
protected:
	T mean_;
	bool unbiased_;
private:
};









#endif