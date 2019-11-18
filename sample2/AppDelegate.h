//
//  AppDelegate.h
//  sample2
//
//  Copyright (c) 2013 bismark LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

#include "bsmd.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property BSMD_FUNC *api;
@property BSMD_HANDLE handle;

@end
