#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * get_value(const char *buffer, const char *s)
{
    char *result = (char *)malloc(10000);
    char *index = strstr(buffer, s);
    if (!index)
    {
        printf("Error in found value.\n");
        exit(1);
    }
    index += strlen(s);
    int i = 0;
    while(*index != '&' && *index != '\n')
    {
        result[i++] = *index++;
    }
    return result;
}

char *read_config()
{
    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;

    pFile = fopen("config.txt", "r");
    if (pFile == NULL)
    {
        printf("Error when opening file\n");
        exit(1);
    }

    // 取得文件大小，即这个文件一共有多少个字节
    // 移动读写定位到文件末尾
    fseek (pFile , 0 , SEEK_END);
    // 看一下这时位置的数字，它就是文件的大小！
    lSize = ftell (pFile);
    if (lSize == 0) // 如果文件为空，咱们也结束程序
    {
        printf("the file is Empty.\n");
        fclose (pFile);
        exit(1);
    }
    rewind (pFile);

    buffer = (char*) malloc (sizeof(char)*lSize);
    result = fread (buffer, 1, lSize, pFile);
    if (result != lSize)
    {
        printf("Reading error\n");
        exit (3);
    }


    fclose (pFile);
    free (buffer);
    return buffer;
}


int main()
{
    char *FVlevel;
    char *FVterrainString = malloc(1000);
    char *FVinsMax;
    char *FVinsMin;
    char *FVboardX;
    char *FVboardY;

    char *buffer = read_config();

    FVterrainString = get_value(buffer, "FVterrainString=");
    FVinsMax = get_value(buffer, "FVinsMax=");
    FVinsMin = get_value(buffer, "FVinsMin=");
    FVboardX = get_value(buffer, "FVboardX=");
    FVboardY = get_value(buffer, "FVboardY=");
    FVlevel = get_value(buffer, "FVlevel=");

    printf("FVlevel=%s\n", FVlevel);
    printf("FVterrainString=%s\n", FVterrainString);
    printf("FVinsMax=%s\n", FVinsMax);
    printf("FVinsMin=%s\n", FVinsMin);
    printf("FVboardX=%s\n", FVboardX);
    printf("FVboardY=%s\n", FVboardY);
}
