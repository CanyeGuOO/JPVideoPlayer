//
// Created by NewPan on 2018/2/20.
// Copyright (c) 2018 NewPan. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "JPResourceLoadingRequestTask.h"

NS_ASSUME_NONNULL_BEGIN

@interface NSURL (StripQuery)

/*
 * Returns absolute string of URL with the query stripped out.
 * If there is no query, returns a copy of absolute string.
 */

- (NSString *)absoluteStringByStrippingQuery;

@end

@interface NSHTTPURLResponse (JPVideoPlayer)

/**
 * Fetch the file length of response.
 *
 * @return The file length of response.
 */
- (long long)jp_fileLength;

/**
 * Check the response support streaming or not.
 *
 * @return The response support streaming or not.
 */
- (BOOL)jp_supportRange;

@end

@interface AVAssetResourceLoadingRequest (JPVideoPlayer)

/**
 * Fill content information for current request use response conent.
 *
 * @param response A response.
 */
- (void)jp_fillContentInformationWithResponse:(NSHTTPURLResponse *)response;

@end

@interface NSFileHandle (JPVideoPlayer)

- (BOOL)jp_safeWriteData:(NSData *)data;

@end

@interface NSURLSessionTask(JPVideoPlayer)

@property(nonatomic) JPResourceLoadingRequestWebTask * webTask;

@end

@interface NSObject (JPSwizzle)

+ (BOOL)jp_swizzleMethod:(SEL)origSel withMethod:(SEL)altSel error:(NSError**)error;

@end

@interface JPLog : NSObject

/**
 * Output message to console.
 *
 *  @param logLevel         The log type.
 *  @param file         The current file name.
 *  @param function     The current function name.
 *  @param line         The current line number.
 *  @param format       The log format.
 */
+ (void)logWithFlag:(JPLogLevel)logLevel
               file:(const char *)file
           function:(const char *)function
               line:(NSUInteger)line
             format:(NSString *)format, ...;

@end

#ifdef __OBJC__

#define JP_LOG_MACRO(logFlag, frmt, ...) \
                                        [JPLog logWithFlag:logFlag\
                                                      file:__FILE__ \
                                                  function:__FUNCTION__ \
                                                      line:__LINE__ \
                                                    format:(frmt), ##__VA_ARGS__]


#define JP_LOG_MAYBE(logFlag, frmt, ...) JP_LOG_MACRO(logFlag, frmt, ##__VA_ARGS__)

#if DEBUG

/**
 * Log debug log.
 */
#define JPDebugLog(frmt, ...) JP_LOG_MAYBE(JPLogLevelDebug, frmt, ##__VA_ARGS__)

/**
 * Log debug and warning log.
 */
#define JPWarningLog(frmt, ...) JP_LOG_MAYBE(JPLogLevelWarning, frmt, ##__VA_ARGS__)

/**
 * Log debug, warning and error log.
 */
#define JPErrorLog(frmt, ...) JP_LOG_MAYBE(JPLogLevelError, frmt, ##__VA_ARGS__)

#else

#define JPDebugLog(frmt, ...)
#define JPWarningLog(frmt, ...)
#define JPErrorLog(frmt, ...)
#endif

#endif

typedef NS_ENUM(NSInteger, JPApplicationState) {
    JPApplicationStateUnknown = 0,
    JPApplicationStateWillResignActive,
    JPApplicationStateDidEnterBackground,
    JPApplicationStateWillEnterForeground,
    JPApplicationStateDidBecomeActive
};

@class JPApplicationStateMonitor;

@protocol JPApplicationStateMonitorDelegate <NSObject>

@optional

/**
 * This method will be called when application state changed.
 *
 * @param monitor          The current object.
 * @param applicationState The application state.
 */
- (void)applicationStateMonitor:(JPApplicationStateMonitor *)monitor
         applicationStateDidChange:(JPApplicationState)applicationState;

/**
 * This method will be called only when application become active from `Control Center`,
 *  `Notification Center`, `pop UIAlert`, `double click Home-Button`.
 *
 * @param monitor The current object.
 */
- (void)applicationDidBecomeActiveFromResignActive:(JPApplicationStateMonitor *)monitor;

/**
 * This method will be called only when application become active from `Share to other application`,
 *  `Enter background`, `Lock screen`.
 *
 * @param monitor The current object.
 */
- (void)applicationDidBecomeActiveFromBackground:(JPApplicationStateMonitor *)monitor;

@end

@interface JPApplicationStateMonitor : NSObject

@property(nonatomic, weak) id<JPApplicationStateMonitorDelegate> delegate;

@property (nonatomic, assign, readonly) JPApplicationState applicationState;

@end

NS_ASSUME_NONNULL_END
