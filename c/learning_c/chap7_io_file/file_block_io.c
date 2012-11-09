// malloc() free() 见 7.8.5 节
// 关于 fread() fwrite() 的详细解释，见附录 B.1.5

#include <stdio.h>
#include <stdlib.h> // malloc, free, exit 在这个头文件里

void file_block_write()
{
    FILE * pFile;
    // 字符数组的知识请见 5.5 节
    char buffer[] = "fread() and fwrite() are so fast.\nI love it!!";
    pFile = fopen ( "myfile.txt" , "w" );
    fwrite(buffer, 1, sizeof(buffer), pFile);
    fclose(pFile);
}

void file_block_read()
{
    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;

    pFile = fopen("myfile.txt", "r");
    // fopen 返回值如何是NULL 则说明打开文件不成功（比如文件不存在）
    // 这时我们让程序结束，以免后面的代码产生不好的结果
    // fopen 说明见 附录 B.1.1
    if (pFile == NULL)
    {
        printf("Error when calling fopen()\n");
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
        return;
    }
    // 再将文件读写定位器设为文件开头
    rewind (pFile);

    // 分配一个文件大小的char*类型的内存空间
    // malloc() free() 见 7.8.5 节
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL)
    {
        // 如果内存分配失败，比如文件10G，而我们内存只有4G
        // 这时我们结束程序
        printf("Memory error\n");
        exit(2);
    }

    // 耶，终于走到读文件这一步了！！
    // fread 是以块来读取文件内容，而不像 getc() 那样一个字符一个字符地读
    // 关于 fread() 的详细解释，见附录 B.1.5
    result = fread (buffer, 1, lSize, pFile);
    if (result != lSize)
    {
        // 如果一切正常 result 应该和 lSize 相等
        // 不相等说明读取文件有错，我们结束程序
        printf("Reading error\n");
        exit (3);
    }

    // 让我们来看看文件内容是什么吧
    printf("=======================================\n");
    printf("%s", buffer);
    printf("\n=======================================\n");

    // 打扫战场，释放资源
    fclose (pFile);
    free (buffer);
}

int main ()
{
    file_block_write();
    file_block_read();
    return 0;
}
