//
//  AppDelegate.h
//  ConnectionExample
//
//  Created by Pedro Loureiro on 07/01/2020.
//  Copyright © 2020 Pedro Loureiro. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@import Diffusion;

@interface AppDelegate : NSObject <NSApplicationDelegate, PTDiffusionJSONValueStreamDelegate, PTDiffusionFetchStreamDelegate, PTDiffusionSessionResponseStreamDelegate>


@end

