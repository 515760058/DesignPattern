// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//cmake根据配置文件，自动生成该头文件。
#include "TutorialConfig.h"
//根据USE_MYMATH的值，是否使用自己的库函数
#ifdef USE_MYMATH
#include "MathFunctions.h"
#endif

int main (int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stdout, "Usage: %s number\n", argv[0]);
    fprintf(stdout, "%s Version %d.%d\n", argv[0], Tutorial_VERSION_MAJOR, Tutorial_VERSION_MINOR);
    return 1;
  }

  double inputValue = atof(argv[1]);
#ifdef USE_MYMATH
  double outputValue = mysqrt(inputValue);//使用自己提供的libMathFunctions.a静态库里面的mysqrt函数
  fprintf(stdout,"libMathFunctions.a  ");
#else
  double outputValue = sqrt(inputValue);//使用系统自带的math.h中的sqrt函数。
  fprintf(stdout,"system              ");
#endif
  fprintf(stdout,"The square root of %g is %g\n", inputValue, outputValue);


  double result = 100.0;
// if we have both log and exp then use them
#if defined (HAVE_LOG) && defined (HAVE_EXP) //该平台含有exp和log函数
  result = exp(log(100)*0.5);
  fprintf(stdout,"system exp and log : %f\n", result);
#else // otherwise use an iterative approach 自己在mathfunction库中提供的
  result = myexp(mylog(100)*0.5);
  fprintf(stdout,"myexp and mylog : %f\n", result);
#endif

  return 0;
}

