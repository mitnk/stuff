//
//  main.m
//  HelloOC
//
//  Created by mitnk on 11/8/12.
//  Copyright (c) 2012 mitnk. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <stdio.h>

int main(int argc, const char * argv[])
{
    // insert code here...
    NSLog(@"Hello, World!");
    NSLog(@"%d", 10);
    NSLog(@"%d", 10);
    
    char a[] = "hello world!";
    NSLog(@"%s", a);
    
    NSString *b = @"Hello Cocoa";
    NSLog(@"%@", b);
    
    BOOL aaa = 13;
    NSLog(@"aaa = %d", aaa);
    NSLog(@"aaa = YES: %d", aaa == YES);
    
    NSLog(@"size of bool: %lu", sizeof(bool));
    NSLog(@"size of BOOL: %lu", sizeof(BOOL));
    NSLog(@"size of int: %lu", sizeof(int));
    // 或者这样也行：
    int n = 1;
    bool is_good = false;
    NSLog(@"%lu", sizeof(is_good));
    NSLog(@"%lu", sizeof(n));
    
    is_good = 10;
    NSLog(@"is_good = %d", is_good);
    
    NSString = @"aa";
    
    NSLog(@"%s%@", "hello", @" world");
    return 0;
}

