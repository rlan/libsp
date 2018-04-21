#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestEstimator
#include <boost/test/unit_test.hpp>

#include <iomanip>
#include <iostream>

#include <cmath>

#include "runningstats.hpp"

BOOST_AUTO_TEST_SUITE( suite_estimator );

BOOST_AUTO_TEST_CASE( test_runningstats )
{
  std::vector<double> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  RunningStats estimator;
  BOOST_CHECK(estimator.count() == 0);
  BOOST_CHECK(estimator.mean() == 0.0);

  for (auto x : data)
    estimator.push(x);
  BOOST_CHECK(estimator.count() == 9);
  BOOST_CHECK(estimator.mean() == 5.0);
  BOOST_CHECK(estimator.variance() == 7.5);
  BOOST_CHECK(estimator.standard_deviation() == sqrt(7.5));
  BOOST_CHECK(estimator.skewness() == 0);
  BOOST_CHECK(estimator.kurtosis() == -1.2);
  
  estimator.clear();
  BOOST_CHECK(estimator.count() == 0);
  BOOST_CHECK(estimator.mean() == 0.0);
}

BOOST_AUTO_TEST_SUITE_END();
