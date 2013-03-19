function []=iir_regression()
% IIR regression
% Reads output from executable and verify operation.
%
% Rick Lan
% See LICENSE for license.

regress_biquad();
end


function []=regress_biquad()
disp('regress_iirbiquad...');
c=load('regress_iirbiquad_coeffs.txt');
o=load('regress_iirbiquad_impulse_response.txt');
b=c(1:3)*c(7);
a=c(4:6);
ref=impz(b,a,100);
msg=sprintf('mse is %.12g', mse(ref,o));
disp(msg);
end


function [m] = mse(ref, cmp)
%MSE Compute mean squared error.
%   Y = MSE(REF, NOISY)
%   Input data structure supported: scalar, vector.
%   Input data type supported: real, complex.
%
%   Rick Lan
%   See LICENSE for the license.
%
error(nargchk(2, 2, nargin));
e = cmp - ref;
m = mean( e.*conj(e) );
end