#include <stdio.h>
#include <fcntl.h>

#define PERMS 0666 /* RW for owner, group, others */

/* cp: copy f1 to f2 */
int main(int argc, char *argv[])
{
    int f1, f2, n; char buf[BUFSIZ];
    if (argc != 3)
        perror("Usage: cp from to");
        exit(1);

    if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)
        perror("cp: can't open 1");

    if ((f2 = creat(argv[2], PERMS)) == -1)
        perror("cp: can't create file 2");

    while ((n = read(f1, buf, BUFSIZ)) > 0)
        if (write(f2, buf, n) != n)
            perror("cp: write perror on file 2");
        return 0;
}
