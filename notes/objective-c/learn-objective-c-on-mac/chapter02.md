Extensions to C
===============

1) Where is the dictionary of the head files for the Foundation framework?

`/System/Library/Frameworks/Foundation.framework/Headers`

2) How many .h files in it? With what Unix commands to check out this?

`140` Using command `ls | wc -l`

3) How many lines in all these .h files? Use what command to check it?

`18304` by `grep "" *.h | wc -l`

4) What is the same way to do `printf("%d\n", n);` when n is a int variable?

`NSLog(@"%d", n);`

5) Like `NSLog()` or `NSString`, lots of classes/functions begin with `NS`. Why? Short for What?

`NS` stands for `NextSTEP`, the former name of `Cocoa`. Stards with `NS` means these stuffs are belonging to `Cocoa` other than other frameworks. It helps prevent name collisions.

6) What is the defference between `NSString` and C-style String `char s[] = "hello strings"` ?

`NSString` can do much more things than C-style Strings

- Tell you its length
- Compare itself to another string
- Convert itself to an integer or float-point value
- etc

7) What defference between `#include` and `#import` ?

`#import` is better than `#include` because it only include one head file once.

8) What is the result of the follow code:

```c
#include <stdio.h>
int main()
{
    bool b = 10;
    printf("b = %d\n", b);
}
```

`b = 1`

9) What is the result of the follow code:

```objective-c
BOOL b = 13;
NSLog(@"b = %d", aaa);
```

`b = 13`

10) How many bytes does `int` and `bool` have? Write some code to show it.

Size of `int` is 4. Size of `bool` is 1.

```objective-c
NSLog(@"%lu", sizeof(bool));
NSLog(@"%lu", sizeof(int));
// 或者这样也行：
int n = 1;
bool is_good = false;
NSLog(@"%lu", sizeof(is_good));
NSLog(@"%lu", sizeof(n));
```

11) How to print `"hello"` and `@" world"` at together with NSLog?

`NSLog(@"%s%@", "hello", @" world");`


12) * Which class method will be called by `%@`?

`description`.

