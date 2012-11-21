```Objective-C
//
//  main.m
//  TestInheritance
//
//  Created by mitnk on 11/12/12.
//  Copyright (c) 2012 mitnk. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface A : NSObject
-(void) sayHello;
@end

@implementation A
-(void) sayHello
{
    NSLog(@"Hello, I'm A");
}
@end

@interface AA : A
@end

@implementation AA

-(void) sayHello
{
    [super sayHello];

    NSLog(@"Hello, I'm AA desu");
}
@end

int main(int argc, const char * argv[])
{
    id a = [AA new];
    [a sayHello];
    return 0;
}
```
