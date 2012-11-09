标准输出
------

    :::bash
    echo -e "first\nsecond\nthird"

结果为：

    first
    second
    third

以上命令的结果输出直接输出到了Terminal  
这就是所谓的“标准输出”

将结果输出到文件
--------------

我们也可以使用文件重定向 `>` 将结果输出到一个文件里

    :::bash
    echo -e "first\nsecond\nthird" > n.txt

这时Terminal没有任何输出结果  
不过在当前文件夹将会产生一个叫 n.txt 的文件  
它的内容就是上面三行文字  

    :::bash
    cat n.txt

结果：

    first
    second
    third

任何标准linux/unix命令都可以用文件重定向将结果输入到文件里

    :::bash
    ls > result.txt


Linux管道
--------

通过管道我们可以**让一个命令的输出当作后一个命令的输入**  
比如 `wc -l` 命令是计算输入的行数：

    :::bash
    wc -l

这时命令会等待你的输入  
按以下方式输入（这就叫标准输入）：

    abc(回车)
    eee(回车)
    Ctrl-D

然后会看到输出结果 `2`

通过管道我们可以将其它命令的输出当作输入：

    :::bash
    echo -e "first\nsecond\nthird" | wc -l

输出结果为 `3`

我们可以在一条命令中用多个管道：

    :::bash
    ls | grep "ic" | wc -l

上面命令是数一下当前目录下名称含有 `ic` 的文件/文件夹个数

将文件里的内容（而不是文件本身）当作输入
----------------------------------

我们还可以利用重定向 `<` 将一个文件的内容当作一个命令的输入：

    :::bash
    wc -l < n.txt

输入结果为 `3` (这里的 n.txt 为上面成生的那个)

其实通过管道我们也可以达到相同目的：

    :::bash
    cat n.txt | wc -l
