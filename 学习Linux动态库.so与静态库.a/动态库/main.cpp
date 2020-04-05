// //https://www.cnblogs.com/gulvzhe/archive/2012/06/27/2565983.html

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> //注意头文件

typedef int (*PFN_MYFUNC)(int);

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("usage :%s num\n", argv[0]);
        return 1;
    }

    // dlopen 函数还会自动解析共享库中的依赖项。这样，如果您打开了一个依赖于其他共享库的对象，它就会自动加载它们。
    // 函数返回一个句柄，该句柄用于后续的 API 调用
    void *libm_handle = dlopen("libfunc.so", RTLD_LAZY);
    // 如果返回 NULL 句柄，表示无法找到对象文件，过程结束。否则的话，将会得到对象的一个句柄，可以进一步询问对象
    if (!libm_handle){
        // 如果返回 NULL 句柄,通过dlerror方法可以取得无法访问对象的原因
        printf("Open Error:%s.\n", dlerror());
        return 0;
    }

    // 使用dlsym函数，尝试解析动态库中的myfunc函数。将会得到一个指向该函数的指针，或者NULL并返回一个错误
    PFN_MYFUNC pfn_myfunc = (PFN_MYFUNC) dlsym(libm_handle, "myfunc");//显示类型转换
    char *errorInfo = dlerror();// 调用dlerror方法，返回错误信息的同时，内存中的错误信息被清空
    if (errorInfo != NULL){
        printf("Dlsym Error:%s.\n",errorInfo);
        return 0;
    }

    // 执行“myfunc”函数
    int num = atoi(argv[1]);
    int result = (*pfn_myfunc)(num);
    printf("result = %d\n",result);
    
    // 调用 dlclose来关闭对它的访问
    dlclose(libm_handle);

    return 0;
}
