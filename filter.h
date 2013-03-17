/**\file
 * \brief Abstract Base Class of a Filter
 *
 * Defines basic operation of a filter:
 * - Store coefficients.
 * - Compute an output.
 * - Update memory in the filter.
 */

#ifndef FILTER_H_
#define FILTER_H_

#include <vector>


template<class T>
class Filter
{
public:
	Filter(const std::vector<T> &Coeffs)
	: Coeffs_(Coeffs)
	{ }

	virtual ~Filter()
	{ }

protected:
	const std::vector<T> Coeffs_;

	/** Update memory in the filter. */
	virtual void
	shift(const T &In)
	{ }

	/** Compute an output. */
	virtual T
	compute(void)
	{ return T(0); }

	/** Filter operation. */
	virtual T
	filter(const T &In)
	{
		shift(In);
		return compute();
	}

private:
	Filter(); // disabled
};



#endif /* FILTER_H_ */
