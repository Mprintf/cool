/*=============================================================== 
*   Copyright (C) . All rights reserved.")
*   文件名称： 
*   创 建 者：zhang
*   创建日期：
*   描    述：这个demo左右就是体现环境变量的全局特性 
================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//int main(int argc, char *argv[], char *env[])
int main()
{
    //char *getenv(const char *name);
    //通过环境变量名称获取内容
    //char *ptr = getenv("MYPATH");
    //printf("ptr:%s\n", ptr);
    int i;
    extern char **environ;
    for (i = 0; environ[i] != NULL; i++) {
        //printf("env[%d]=[%s]\n", i, env[i]);
        printf("env[%d]=[%s]\n", i, environ[i]);
    }
    return 0;
}

