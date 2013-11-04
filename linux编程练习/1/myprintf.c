/*
 * =====================================================================================
 *
 *       Filename:  myprintf.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/16/2013 06:22:38 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (zyl), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void myprintf(char *format, ...)
{
    va_list args;
    int i = 0, j = 0;
    //type va_arg(va_list arg_ptr, type);
    va_start(args, format);
    char ans[1000];
    char *str, buffer[20];
    int temp;
    double tempf;
    memset(ans, 0, sizeof(ans));
    while('\0' != format[i])
    {
        if('%' == format[i])
        {
            switch(format[i + 1])
            {
                case 's':
                    str = va_arg(args, char*);
                    memcpy(ans + j, str, strlen(str));
                    j += strlen(str);
                    i += 2;
                    break;
                case 'd':
                    temp = va_arg(args, int);
					itoa(temp, buffer, 10);
                    //sprintf(buffer, "%d", temp);
                    memcpy(ans + j, buffer, strlen(buffer));
                    j += strlen(buffer);
                    i += 2;
                    break;
                case 'f':
					tempf = va_arg(args, double);
					gcvt(tempf, 5, buffer);
				    //sprintf(buffer, "%f", tempf);
					memcpy(ans + j, buffer, strlen(buffer));
					j += strlen(buffer);
					i += 2;
                    break;
                default:
                    ans[j] = format[i + 1];
                    j += 1;
                    i += 2;
                    break;
            }
        }
        else
        {
            ans[j++] = format[i++];
        }
    }
    va_end(args);
    ans[j] = '\0';
    write(STDOUT_FILENO, ans, strlen(ans));
}

int main(int argc, char *argv[])
{
    myprintf("myprintf %d %s %f\n", 12, "hello", 15.5);

    return 0;
}
