//
//  JSONFlickrViewController.h
//  JSONFlickr
//
//  Created by John on 8/21/09.
//  Copyright iPhoneDeveloperTips.com 2009. All rights reserved.
//

@class ZoomedImageView;

@interface JSONFlickrViewController : UIViewController <UITableViewDelegate, UITableViewDataSource, UITextFieldDelegate>
{
  UITextField     *searchTextField;
  UITableView     *theTableView;
  NSMutableArray  *photoTitles;         // Titles of images
  NSMutableArray  *photoSmallImageData; // Image data (thumbnail)
  NSMutableArray  *photoURLsLargeImage; // URL to larger image
  
  ZoomedImageView  *fullImageViewController;
  UIActivityIndicatorView *activityIndicator;      
}

@end

