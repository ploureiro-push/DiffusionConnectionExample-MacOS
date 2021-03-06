//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2017, 2018 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionFeature.h>

@class PTDiffusionBytes;
@class PTDiffusionRequest;
@class PTDiffusionRequestHandler;
@class PTDiffusionSendOptions;
@class PTDiffusionSessionId;
@class PTDiffusionSessionResponseStream;
@class PTDiffusionTopicTreeRegistration;

@protocol PTDiffusionMessageDelegate;

/**
 Values assigned to the `code` property of NSError objects generated by the
 PTDiffusionMessagingControlFeature.

 @since 6.0
 */
typedef NS_ENUM(NSInteger, PTDiffusionMessagingControlFeatureErrorCode) {
    /**
     The filter was rejected. The message was not sent to any clients.
     
     @see PTDiffusionUnderlyingErrorsKey
     
     @since 6.0
     */
    PTDiffusionMessagingControlFeatureErrorCode_SendToFilterRejected = 1,
};

NS_ASSUME_NONNULL_BEGIN

/**
 The value assigned to the `domain` property of NSError objects generated by the
 PTDiffusionMessagingControlFeature.

 @since 6.0
 */
extern NSString *const PTDiffusionMessagingControlFeatureErrorDomain;

/**
 @brief The Messaging Control feature provides a client session with the ability
 to use messaging functionality to communicate directly with other client
 sessions.

 The Messaging Control feature for a session can be obtained from the session's
 `messagingControl` property.

 For more detail,
 see: @ref md_messaging "Messaging with the Apple client library".

 @see PTDiffusionSession

 @since 6.0
 */
@interface PTDiffusionMessagingControlFeature : PTDiffusionFeature

/**
 Register a message handler to handle messages received from other client
 sessions for a branch of the path hierarchy.

 The handler will be invoked for paths below and including the specified path to
 which messages have been sent. This will only receive messages sent from a
 client (for example by one of the send methods in the
 PTDiffusionMessagingFeature) and not any updates to topics that are bound to
 the same paths.

 Each control session can register a single handler for a branch.
 When the handler is no longer required, it can be closed using the close
 method (see PTDiffusionTopicTreeRegistration).
 To change the handler for a particular branch the previous handler must first
 be closed.

 @param delegate Specifies the delegate for all messages sent on paths below and
 including the specified branch (unless overridden by a handler registered
 against a more specific branch).

 @param path Identifies a branch in the path hierarchy.

 @param sessionProperties a list of keys of session properties that should
 be supplied with each message. See PTDiffusionSession for a full list of
 available fixed property keys. To request no properties supply an empty list.
 To request all fixed properties include [PTDiffusionSession allFixedProperties]
 as a key. In this case any other fixed property keys would be ignored.
 To request all user properties include [PTDiffusionSession allUserProperties]
 as a key. In this case any other user properties are ignored.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will
 be `nil` and the `registration` argument will not be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException If any arguments are `nil`.

 @deprecated Since 6.2. One-way messaging has been deprecated in favor of
 request-response messaging. This method will be removed in a future release.

 @since 6.0
 */
-(void)addMessageHandlerForPath:(NSString *)path
                   withDelegate:(id<PTDiffusionMessageDelegate>)delegate
              sessionProperties:(NSArray<NSString *> *)sessionProperties
              completionHandler:(void (^)(PTDiffusionTopicTreeRegistration * _Nullable registration, NSError * _Nullable error))completionHandler
__deprecated_msg("Will be removed in a future release.");

/**
 Register a message handler to handle messages received from other client
 sessions for a branch of the path hierarchy.

 This is equivalent to calling
 addMessageHandler:forPath:sessionProperties:completionHandler: with an empty
 array for session properties.

 @param delegate Specifies the delegate for all messages sent on paths below and
 including the specified branch (unless overridden by a handler registered
 against a more specific branch).

 @param path Identifies a branch in the path hierarchy.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will
 be `nil` and the `registration` argument will not be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException If any arguments are `nil`.

 @deprecated Since 6.2. One-way messaging has been deprecated in favor of
 request-response messaging. This method will be removed in a future release.

 @since 6.0
 */
-(void)addMessageHandlerForPath:(NSString *)path
                   withDelegate:(id<PTDiffusionMessageDelegate>)delegate
              completionHandler:(void (^)(PTDiffusionTopicTreeRegistration * _Nullable registration, NSError * _Nullable error))completionHandler
__deprecated_msg("Will be removed in a future release.");

/**
 Register a request handler to handle messages received from other client
 sessions on a path.

 @param handler Specifies the handler to be registered at the server.

 @param path The request path.
 
 @param sessionProperties a list of keys of session properties that should
 be supplied with each message. See PTDiffusionSession for a full list of
 available fixed property keys. To request no properties supply an empty list.
 To request all fixed properties include [PTDiffusionSession allFixedProperties]
 as a key. In this case any other fixed property keys would be ignored.
 To request all user properties include [PTDiffusionSession allUserProperties]
 as a key. In this case any other user properties are ignored.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will
 be `nil` and the `registration` argument will not be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.
 
 @exception NSInvalidArgumentException If any argument is `nil`.

 @since 6.0
 */
-(void)addRequestHandler:(PTDiffusionRequestHandler *)handler
                 forPath:(NSString *)path
       sessionProperties:(NSArray<NSString *> *)sessionProperties
       completionHandler:(void (^)(PTDiffusionTopicTreeRegistration * _Nullable registration, NSError * _Nullable error))completionHandler;

/**
 Register a request handler to handle messages received from other client
 sessions on a path.

 This is equivalent to calling
 addRequestHandler:forPath:requestClass:responseClass:sessionProperties:completionHandler:
 with an empty array for session properties.

 @param handler Specifies the handler to be registered at the server.

 @param path The request path.
 
 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will
 be `nil` and the `registration` argument will not be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.
 
 @exception NSInvalidArgumentException If any argument is `nil`.

 @since 6.0
 */
-(void)addRequestHandler:(PTDiffusionRequestHandler *)handler
                 forPath:(NSString *)path
       completionHandler:(void (^)(PTDiffusionTopicTreeRegistration * _Nullable registration, NSError * _Nullable error))completionHandler;

/**
 Send a message to a session using a specific path.
 
 @param sessionId Identifies the session to which the message will be sent.
 
 @param path The message path that the message is to be associated with.
 
 @param message The message to send.
 
 @param options Message options, including headers and priority.
 
 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException If any arguments are `nil`.

 @deprecated Since 6.2. One-way messaging has been deprecated in favor of
 request-response messaging. This method will be removed in a future release.

 @since 6.0
 */
-(void)sendToSessionId:(PTDiffusionSessionId *)sessionId
                  path:(NSString *)path
               message:(PTDiffusionBytes *)message
               options:(PTDiffusionSendOptions *)options
     completionHandler:(void (^)(NSError * _Nullable error))completionHandler
__deprecated_msg("Will be removed in a future release.");

/**
 Send a message to a session using a specific path.
 
 This is equivalent to calling
 sendToSessionId:path:message:options:completionHandler: with default options.

 @param sessionId Identifies the session to which the message will be sent.
 
 @param path The message path that the message is to be associated with.
 
 @param message The message to send.
 
 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException If any arguments are `nil`.

 @deprecated Since 6.2. One-way messaging has been deprecated in favor of
 request-response messaging. This method will be removed in a future release.

 @since 6.0
 */
-(void)sendToSessionId:(PTDiffusionSessionId *)sessionId
                  path:(NSString *)path
               message:(PTDiffusionBytes *)message
     completionHandler:(void (^)(NSError * _Nullable error))completionHandler
__deprecated_msg("Will be removed in a future release.");

/**
 Send a message to all sessions that satisfy a given session filter using a
 specific path.
 
 See PTDiffusionSession for a full description of filter expressions.
 
 @param filter The session filter expression.
 
 @param path The message path that the message is to be associated with.
 
 @param message The message to send.
 
 @param options Message options, including headers and priority.
 
 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil` and the `count` argument indicates the number of clients
 that satisfied the filter and to which the message was sent. On failure the
 `error` argument passed to the block will not be `nil` and the `count` argument
 will be zero. The completion handler will be called asynchronously on the main
 dispatch queue.
 
 @note The completion handler block will be invoked with a `nil` for the `error`
 argument and zero for the `count` argument if no client sessions matched the
 filter.

 @exception NSInvalidArgumentException If any arguments are `nil`.

 @deprecated Since 6.2. One-way messaging has been deprecated in favor of
 request-response messaging. This method will be removed in a future release.

 @since 6.0
 */
-(void)sendToFilter:(NSString *)filter
               path:(NSString *)path
            message:(PTDiffusionBytes *)message
            options:(PTDiffusionSendOptions *)options
  completionHandler:(void (^)(NSUInteger count, NSError * _Nullable error))completionHandler
__deprecated_msg("Will be removed in a future release.");

/**
 Send a message to all sessions that satisfy a given session filter using a
 specific path.

 This is equivalent to calling
 sendToFilter:path:message:options:completionHandler: with default options.

 @param filter The session filter expression.
 
 @param path The message path that the message is to be associated with.
 
 @param message The message to send.
 
 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil` and the `count` argument indicates the number of clients
 that satisfied the filter and to which the message was sent. On failure the
 `error` argument passed to the block will not be `nil` and the `count` argument
 will be zero. The completion handler will be called asynchronously on the main
 dispatch queue.
 
 @note The completion handler block will be invoked with a `nil` for the `error`
 argument and zero for the `count` argument if no client sessions matched the
 filter.

 @exception NSInvalidArgumentException If any arguments are `nil`.

 @deprecated Since 6.2. One-way messaging has been deprecated in favor of
 request-response messaging. This method will be removed in a future release.

 @since 6.0
 */
-(void)sendToFilter:(NSString *)filter
               path:(NSString *)path
            message:(PTDiffusionBytes *)message
  completionHandler:(void (^)(NSUInteger count, NSError * _Nullable error))completionHandler
__deprecated_msg("Will be removed in a future release.");

/**
 Send a request to all sessions that satisfy a given session filter.

 @param request The request to send.

 @param filter The session filter expression.

 @param path The path to send the request to.

 @param responseStream The stream that will handle the incoming responses.
 The delegate associated with this stream will be sent messages asynchronously
 on the main dispatch queue.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue. Success indicates that the server has dispatched all
 the requests.

 @note The completion handler block will be invoked with a `nil` for the `error`
 argument and zero for the `count` argument if no client sessions matched the
 filter.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @since 6.1
 */
-(void)   sendRequest:(PTDiffusionRequest *)request
             toFilter:(NSString *)filter
                 path:(NSString *)path
       responseStream:(PTDiffusionSessionResponseStream *)responseStream
    completionHandler:(void (^)(NSUInteger count, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
