//
//  main.m
//  ShapesObject
//
//  Created by mitnk on 11/11/12.
//  Copyright (c) 2012 mitnk. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    kRedColor,
    kGreenColor,
    kBlueColor
} ShapeColor;

typedef struct {
    int x, y, width, height;
} ShapeRect;

NSString *colorName (ShapeColor colorName)
{
    switch (colorName) {
        case kRedColor:
            return @"red";
            break;
        case kGreenColor:
            return @"green";
            break;
        case kBlueColor:
            return @"blue";
        break; }
    return @"no clue";
} // colorName

@interface Circle : NSObject
{
    ShapeColor fillColor;
    ShapeRect bounds;
}

- (void) setFillColor: (ShapeColor) fillColor;
- (void) setBounds: (ShapeRect) bounds;
- (void) draw;

@end // Circle

@implementation Circle

- (void) setFillColor:(ShapeColor) c
{
    self->fillColor = c;
}

- (void) setBounds:(ShapeRect) b
{
    bounds = b;
}

- (void) draw
{
    NSLog(@"Drawing a circle at (%d %d %d %d) in %@",
          bounds.x, bounds.y,
          bounds.width, bounds.height,
          colorName(fillColor));
}

@end


int main(int argc, const char * argv[])
{

    ShapeRect rect = {0, 0, 10, 30};
    id shape = [Circle new];
    [shape setBounds: rect];
    [shape setFillColor: kRedColor];
    
    [shape draw];
    return 0;
}

