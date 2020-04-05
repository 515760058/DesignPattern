#include "MathFunctions.h"
#include <stdio.h>

// 自定义的mysqrt函数
// a hack square root calculation using simple operations
double mysqrt(double x)
{
  if (x <= 0) {
    return 0;
  }

  double result;
  double delta;
  result = x;

  // do ten iterations
  int i;
  for (i = 0; i < 10; ++i) {
    if (result <= 0) {
      result = 0.1;
    }
    delta = x - (result * result);
    result = result + 0.5 * delta / result;
    fprintf(stdout, "Computing sqrt of %g to be %g\n", x, result);
  }
  return result;
}


double myexp(double x)
{
    return 10.3;
}


double mylog(double x)
{
    return 10.3;
}


