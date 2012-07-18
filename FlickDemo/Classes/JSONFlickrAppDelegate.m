//
//  JSONFlickrAppDelegate.m
//  JSONFlickr
//
//  Created by John on 8/21/09.
//  Copyright iPhoneDeveloperTips.com 2009. All rights reserved.
//

#import "JSONFlickrAppDelegate.h"
#import "JSONFlickrViewController.h"

@implementation JSONFlickrAppDelegate

/*-------------------------------------------------------------
*
*------------------------------------------------------------*/
- (void)applicationDidFinishLaunching:(UIApplication *)application
{        
	window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];

  viewController = [[JSONFlickrViewController alloc] init];
  
  [window addSubview:viewController.view];
  [window makeKeyAndVisible];
}

/*-------------------------------------------------------------
*
*------------------------------------------------------------*/
- (void)dealloc 
{
  [window release];
  [viewController release];
  [super dealloc];
}

@end
