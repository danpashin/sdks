// Copyright © Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

#import <GameKit/GKDefines.h>

@class GKVoiceChat;
@class GKPlayer;
@class GKLocalPlayer;
@class GKThreadsafeDictionary;

@protocol GKMatchDelegate;

typedef NS_ENUM(NSInteger, GKMatchSendDataMode) {
    GKMatchSendDataReliable,         /// a.s.a.p. but requires fragmentation and reassembly for large messages, may stall if network congestion occurs
    GKMatchSendDataUnreliable        /// Preferred method. Best effort and immediate, but no guarantees of delivery or order; will not stall.
} __WATCHOS_PROHIBITED;

typedef NS_ENUM(NSInteger, GKPlayerConnectionState) {
    GKPlayerStateUnknown,       /// initial player state
    GKPlayerStateConnected,     /// connected to the match
    GKPlayerStateDisconnected   /// disconnected from the match
};

NS_ASSUME_NONNULL_BEGIN
/// GKMatch represents an active networking sessions between players. It handles network communications and can report player connection status. All matches are created by a GKMatchmaker.
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_PROHIBITED
@interface GKMatch : NSObject

@property(nonatomic, readonly) NSArray<GKPlayer *> *players NS_AVAILABLE(10_10, 8_0);    /// all the GKPlayers in the match
@property(nonatomic, nullable, weak) id<GKMatchDelegate> delegate;
@property(nonatomic, readonly) NSUInteger expectedPlayerCount;
@property(nonatomic, nullable, readonly) GKMatchProperties *properties API_AVAILABLE(ios(17.2), macos(14.2), tvos(17.2));
@property(nonatomic, nullable, readonly) NSDictionary<GKPlayer *, GKMatchProperties *> *playerProperties API_AVAILABLE(ios(17.2), macos(14.2), watchos(10.2), tvos(17.2));

/// Asynchronously send data to one or more GKPlayers. Returns YES if delivery started, NO if unable to start sending and error will be set.
- (BOOL)sendData:(NSData *)data toPlayers:(NSArray<GKPlayer *> *)players dataMode:(GKMatchSendDataMode)mode error:(NSError * __nullable * __nullable)error NS_AVAILABLE(10_10, 8_0);

/// Asynchronously broadcasts data to all players. Returns YES if delivery started, NO if unable to start sending and error will be set.
- (BOOL)sendDataToAllPlayers:(NSData *)data withDataMode:(GKMatchSendDataMode)mode error:(NSError * __nullable * __nullable)error;

/// Disconnect the match. This will show all other players in the match that the local player has disconnected. This should be called before releasing the match instance.
- (void)disconnect;

/// Join a named voice chat channel
/// Will return nil if parental controls are turned on
- (nullable GKVoiceChat *)voiceChatWithName:(NSString *)name;

/// Choose the best host from among the connected players using gathered estimates for bandwidth and packet loss. This is intended for applications that wish to implement a client-server model on top of the match. The returned player ID will be nil if the best host cannot currently be determined (e.g. players are still connecting).
- (void)chooseBestHostingPlayerWithCompletionHandler:(void(^)(GKPlayer * __nullable player))completionHandler NS_AVAILABLE(10_10, 8_0);

/// Automatching to recreate a previous peer-to-peer match that became disconnected. A new match with the same set of players will be returned by the completion handler. All players should perform this when the match has ended for automatching to succeed. Error will be nil on success.
/// Possible reasons for error:
/// 1. Communications failure
/// 2. Timeout
- (void)rematchWithCompletionHandler:(void(^__nullable)(GKMatch * __nullable match, NSError * __nullable error))completionHandler NS_AVAILABLE(10_9, 6_0);

@end

__WATCHOS_PROHIBITED
@protocol GKMatchDelegate <NSObject>
@optional

/// The match received data sent from the player.
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data fromRemotePlayer:(GKPlayer *)player NS_AVAILABLE(10_10, 8_0);
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data forRecipient:(GKPlayer *)recipient fromRemotePlayer:(GKPlayer *)player NS_AVAILABLE(10_11, 9_0);

/// The player state changed (eg. connected or disconnected)
- (void)match:(GKMatch *)match player:(GKPlayer *)player didChangeConnectionState:(GKPlayerConnectionState)state NS_AVAILABLE(10_8, 4_1);

/// The match was unable to be established with any players due to an error.
- (void)match:(GKMatch *)match didFailWithError:(nullable NSError *)error NS_AVAILABLE(10_8, 4_1);

/// This method is called when the match is interrupted; if it returns YES, a new invite will be sent to attempt reconnection. This is supported only for 1v1 games
- (BOOL)match:(GKMatch *)match shouldReinviteDisconnectedPlayer:(GKPlayer *)player NS_AVAILABLE(10_10, 8_0);

/*** These protocol methods are obsoleted. They will never be invoked and their implementation does nothing***/
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data fromPlayer:(NSString *)playerID API_DEPRECATED_WITH_REPLACEMENT("-match:didReceiveData:fromRemotePlayer:", ios(4.1,8.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos);
- (void)match:(GKMatch *)match player:(NSString *)playerID didChangeState:(GKPlayerConnectionState)state API_DEPRECATED_WITH_REPLACEMENT("-match:player:didChangeConnectionState:", ios(4.1,8.0), macos(10.8,10.8)) API_UNAVAILABLE(tvos);
- (BOOL)match:(GKMatch *)match shouldReinvitePlayer:(NSString *)playerID API_DEPRECATED_WITH_REPLACEMENT("-shouldReinviteDisconnectedPlayer:", ios(5.0,8.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos);
@end

__WATCHOS_PROHIBITED
@interface GKMatch (Obsoleted)
/*** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (void)chooseBestHostPlayerWithCompletionHandler:(void(^)(NSString * __nullable playerID))completionHandler API_DEPRECATED_WITH_REPLACEMENT("-chooseBestHostingPlayerWithCompletionHandler:", ios(6.0,8.0), macos(10.9,10.10)) __TVOS_UNAVAILABLE;

/*** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (BOOL)sendData:(NSData *)data toPlayers:(NSArray<NSString *> *)playerIDs withDataMode:(GKMatchSendDataMode)mode error:(NSError **)error API_DEPRECATED_WITH_REPLACEMENT("-sendData:toPlayers:dataMode:error:", ios(4.1,8.0), macos(10.8,10.10)) __TVOS_UNAVAILABLE;

/*** This property is obsolete.  ***/
@property(nonatomic, nullable, readonly) NSArray<NSString *> *playerIDs API_DEPRECATED_WITH_REPLACEMENT("-players:", ios(4.1,8.0), macos(10.8,10.10)) __TVOS_UNAVAILABLE;   // NSStrings of player identifiers in the match

@end
NS_ASSUME_NONNULL_END
