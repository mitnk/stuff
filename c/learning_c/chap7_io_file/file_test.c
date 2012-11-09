// 文件基本操作
//
// 请参考C语言书的 7.5 节
// 关于 "r" "w" "a" "r+" 等意义见附录 B.1.1
// fseek() ftell 见 B.1.6
// fgets 见附录 B.1.4
//

#include <stdio.h>

// 打印一个文件的全部内容
void print_file(char *file_name)
{
    FILE *fp = fopen(file_name, "r");
    char n;
    printf("\n\n===In %s===\n", file_name);
    while((n = getc(fp)) != EOF)
        printf("%c", n);
    fclose(fp); // 每次操作文件完成后务必关闭文件
}

// 文件的写入
void basic_write()
{
    FILE *fp = fopen("name.txt", "w");
    char n;
    for (n = 'A'; n <= 'z'; ++n)
    {
        putc(n, fp);
    }
    putc('\n', fp);
    fclose(fp); // 每次操作文件完成后务必关闭文件

    print_file("name.txt");
}

// 以a文件对文件进入追加输入
void append()
{
    // 以写的方式打开一个文件，并将它的内容清空
    // 然后写入A-Z二十六个大写字母
    FILE *fp = fopen("name.txt", "w");
    char n;
    for (n = 'A'; n <= 'Z'; ++n)
    {
        putc(n, fp);
    }
    putc('\n', fp);
    fclose(fp); // 每次操作文件完成后务必关闭文件
    print_file("name.txt");

    // 以追加方式再次打开这个文件
    // 然后写入a-z小写字母
    fp = fopen("name.txt", "a");
    for (n = 'a'; n <= 'z'; ++n)
    {
        putc(n, fp);
    }
    putc('\n', fp);
    fclose(fp); // 每次操作文件完成后务必关闭文件
    print_file("name.txt");
}


// 以r+文件对文件进入追加输入
void append2()
{
    // 以写的方式打开一个文件，并将它的内容清空
    // 然后写入A-Z二十六个大写字母
    FILE *fp = fopen("name.txt", "w");
    char n;
    for (n = 'A'; n <= 'Z'; ++n)
    {
        putc(n, fp);
    }
    putc('\n', fp);
    fclose(fp); // 每次操作文件完成后务必关闭文件
    print_file("name.txt");

    // 以r+的方式再次打开这个文件
    // 并定位到文件末尾，然后写入a-z小写字母
    // fseek & ftell 请看C语言书附录B.1.6说明
    fp = fopen("name.txt", "r+");
    printf("current position: %ld\n", ftell(fp));
    fseek(fp, 0, SEEK_END);
    printf("after fseek position: %ld\n", ftell(fp));
    for (n = 'a'; n <= 'z'; ++n)
    {
        putc(n, fp);
    }
    putc('\n', fp);
    fclose(fp); // 每次操作文件完成后务必关闭文件
    print_file("name.txt");
}

// 读取文件的前10个字符
void get_first_ten()
{
    // 以写的方式打开一个文件，并将它的内容清空
    // 然后写入A-Z二十六个大写字母
    FILE *fp = fopen("name.txt", "w");
    char n;
    for (n = 'A'; n <= 'Z'; ++n)
    {
        putc(n, fp);
    }
    putc('\n', fp);
    fclose(fp); // 每次操作文件完成后务必关闭文件

    fp = fopen("name.txt", "r");
    char s[11];
    fgets(s, 11, fp); // fgets 见附录 B.1.4
    printf("first 10 chars: %s\n", s);
    fclose(fp); // 每次操作文件完成后务必关闭文件
}


int main()
{
    //basic_write();
    //append();
    //append2();
    get_first_ten();
}
