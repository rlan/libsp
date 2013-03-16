/**\file
 * \brief Run test code.
 *
 * \author Rick Lan
 * \copyright See LICENSE for license.
 */

#include <iostream>
#include <cmath>

#include "complexmultiply.h"
#include "fir_regression.h"

void test_cxmult(void)
{
	std::cout << __func__ << "..." << std::endl;
	for (size_t i = 0; i < 8; i++) {
		std::cout << "i " << i << std::endl;
		double realp = cos(2.0*M_PI*i/8.0);
		double imagp = sin(2.0*M_PI*i/8.0);
		std::complex<double> x(realp, imagp);
		std::complex<double> y = conj(x);
		std::complex<double> z;
		z = cxmult<double, double>(realp, imagp, realp, -imagp);
		std::cout << z << std::endl;
		z = cxmult<double, double>(x, y);
		std::cout << z << std::endl;
		z = cxmult3<double, double, double>(realp, imagp, realp, -imagp);
		std::cout << z << std::endl;
		z = cxmult3<double, double, double>(x, y);
		std::cout << z << std::endl;
	}
}


int main(int argc, char **argv)
{
	test_cxmult();
	regress_fir();
	
	return 0;
}
