#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestEstimator
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <iomanip>

#include "estimator.h"

BOOST_AUTO_TEST_SUITE( suite_estimator );

BOOST_AUTO_TEST_CASE( test_mean_estimator )
{
  std::vector<double> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  MeanEstimator<double> estimator;
  BOOST_CHECK(estimator.count() == 0);
  BOOST_CHECK(estimator.estimate() == 0.0);

  for (auto x : data)
    estimator.record(x);
  BOOST_CHECK(estimator.count() == 9);
  BOOST_CHECK(estimator.estimate() == 5.0);

  estimator.reset();
  BOOST_CHECK(estimator.count() == 0);
  BOOST_CHECK(estimator.estimate() == 0.0);
}

BOOST_AUTO_TEST_CASE( test_variance_estimator )
{
  std::vector<double> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  MeanEstimator<double> mean_estimator;
  for (auto x : data)
    mean_estimator.record(x);

  VarianceEstimator<double> estimator(mean_estimator.estimate());
  BOOST_CHECK(estimator.count() == 0);
  BOOST_CHECK(estimator.estimate() == 0.0);

  for (auto x : data)
    estimator.record(x);
  BOOST_CHECK(estimator.count() == 9);
  BOOST_CHECK(estimator.estimate() == 7.5);

  estimator.reset();
  BOOST_CHECK(estimator.count() == 0);
  BOOST_CHECK(estimator.estimate() == 0.0);
}

// TODO add biased estimator

BOOST_AUTO_TEST_SUITE_END();
