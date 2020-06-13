# Course: MP-6171 High Performance Embedded Systems
# Tecnologico de Costa Rica (www.tec.ac.cr)
# Developers Name: Verny Morales and Luis Carlos Alvarez
# Developers email: verny.morales@gmail.com and lcam03@gmail.com
# This script is structured in Octave (https://www.gnu.org/software/octave/)
# General purpose: Composite Trapezoidal Rule Prototyping
# Input: Lower value, upper value and sub-intervals
# Output: numerical approximation
# Reference: http://hplgit.github.io/Programming-for-Computations/pub/p4c/._p4c-bootstrap-Matlab015.html

#
# Composite Trapezoidal Rule Prototyping
# param u specifies upper value
# param l specifies lower value
# param n sub-intervals
# return numerical estimation
#
function trapezoidal(u, l, n)
  
  f = @(t) 1/(1+(t^2));
  
  #Region aproximation
  h = (u-l)/n;
  
  #Creating the approximation
  result = 0.5*f(u) + 0.5*f(l);
  for i = 1:(n-1)
    result = result + f(l + i*h);
  end
  integral = h*result;
  
  #Printing result
  fprintf("Aproximation: %.16f \n", integral)

end
