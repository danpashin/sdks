//
//  HMCameraControl.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
 * @abstract Represents a generic camera control.
 */
HM_EXTERN NS_SWIFT_SENDABLE API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
    @interface HMCameraControl : NSObject

@end

NS_HEADER_AUDIT_END(nullability, sendability)
