//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2017 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionTimeSeriesEvent.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief An event in a time series whose value may be interpreted as a number.

 @since 6.0
 */
@interface PTDiffusionNumberTimeSeriesEvent : PTDiffusionTimeSeriesEvent

/**
 The numeric value associated with the event.

 @since 6.0
 */
@property(nonatomic, readonly, nullable) NSNumber* number;

@end

NS_ASSUME_NONNULL_END
