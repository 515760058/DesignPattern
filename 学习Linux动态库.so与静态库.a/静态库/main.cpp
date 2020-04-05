// //https://www.cnblogs.com/gulvzhe/archive/2012/06/27/2565983.html

#include <stdio.h>
#include <stdlib.h>

#include "func.h"

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("usage :%s num\n", argv[0]);
        return 1;
    }
    // 执行myfunc函数
    int num = atoi(argv[1]);
    int result = myfunc(num);
    printf("result = %d\n",result);
    
    return 0;
}
