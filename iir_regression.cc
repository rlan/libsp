/**\file
 * Implementation file for IIR regression routines.
 *
 * \author Rick Lan
 * \copyright See LICENSE for license.
 */

#include "fir_regression.h"
#include "iir_regression.h"
#include "iir.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>


void regress_iirbiquad(void)
{
	std::cout << __func__ << "..." << std::endl;
	std::string prefix = "regress_iirbiquad";

	std::vector<double> coeffs(7);
	coeffs[0] = 1.0;
	coeffs[1] = 0.0821;
	coeffs[2] = 1.0;
	coeffs[3] = 1.0;
	coeffs[4] = -1.2049;
	coeffs[5] = 0.5399;
	coeffs[6] = 0.1434; // gain
	write_to<double>(prefix + "_coeffs.txt", coeffs);

	IIRBiquad<double> iir(coeffs);
	const size_t n = 100;
	std::vector<double> out(n);
	for (size_t i = 0; i < n; i++) {
		if (i==0) {
			out[i] = iir.filter(1.0);
		} else {
			out[i] = iir.filter(0.0);
		}
	}
	write_to<double>(prefix + "_impulse_response.txt", out);
}
