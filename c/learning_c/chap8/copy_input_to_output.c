int main()
{
    int n;
    const int SIZE = 1024;
    char buff[SIZE];
    while((n = read(0, buff, SIZE)) != 0)
    {
        // We use n rather than SIZE when reading buff
        write(1, buff, n);
    }
    return 0;
}
