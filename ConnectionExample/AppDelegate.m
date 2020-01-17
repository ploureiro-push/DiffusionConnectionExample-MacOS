//
//  AppDelegate.m
//  ConnectionExample
//
//  Created by Pedro Loureiro on 07/01/2020.
//  Copyright © 2020 Pedro Loureiro. All rights reserved.
//

#import "AppDelegate.h"


@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;

@property PTDiffusionSession *session;
@end

@implementation AppDelegate


static NSString *const _TopicSelectorExpression = @"*Demos/Sportsbook/Football/England/Championship/Nottingham Forest vs Stoke City//";

static NSString *const _TopicSelectorExpressionForAll = @"*Demos//";


-(void) startWithURL:(NSURL*)url
{
    NSLog(@"Connecting to %@", url);
    
    [PTDiffusionSession openWithURL:url completionHandler:^(PTDiffusionSession * _Nullable session, NSError * _Nullable error) {
        if (!session)
        {
            NSLog(@"Failed to open session: %@", error);
            return;
        }
        
        NSLog(@"Connected. Session Identifier: %@", session.sessionId);
        
        self.session = session;
        
        PTDiffusionValueStream *const stream = [PTDiffusionJSON valueStreamWithDelegate:self];
        [session.topics addFallbackStream:stream];
        
        [[session.topics fetchRequest] fetchWithTopicSelectorExpression:_TopicSelectorExpressionForAll completionHandler:^(PTDiffusionFetchResult * _Nullable result, NSError * _Nullable error) {
            if (error)
            {
                NSLog(@"Error while fetching: %@", error);
            }
            else
            {
                for (PTDiffusionFetchTopicResult * topicResult in result.results)
                {
                    NSLog(@"Fetch Topic Result: %@", topicResult.path);
                }
            }
        }];
        
        
        [self performSelector:@selector(subscribe:) withObject:session afterDelay:2.0];
        
        NSNotificationCenter* nc = [NSNotificationCenter defaultCenter];
        [nc addObserverForName:PTDiffusionSessionStateDidChangeNotification object:session queue:nil usingBlock:^(NSNotification * _Nonnull note) {
            PTDiffusionSessionStateChange* change = note.userInfo[PTDiffusionSessionStateChangeUserInfoKey];
            NSLog(@"Session State Change: %@", change);
        }];
    }];
}


- (void)subscribe:(const id)object
{
    PTDiffusionSession *const session = object;
    //
    NSLog(@"Subscribing");
    [session.topics subscribeWithTopicSelectorExpression:_TopicSelectorExpression completionHandler:^(NSError * _Nullable error) {
        if (error) {
            NSLog(@"\tSubscribe request failed: %@", error);
        } else {
            NSLog(@"\tSubscribe request succeeded");
        }
    }];
}


- (void)unsubscribe:(const id)object
{
    PTDiffusionSession *const session = object;
    NSLog(@"Unsubscribing");
    //
    [session.topics unsubscribeFromTopicSelectorExpression:_TopicSelectorExpression completionHandler:^(NSError * _Nullable error) {
        if (error) {
            NSLog(@"\tUnsubscribe request failed: %@", error);
        } else {
            NSLog(@"\tUnsubscribe request succeeeded");
        }
    }];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    NSLog(@"Application finished launching");
    [self startWithURL:[NSURL URLWithString:@"ws://localhost:8080"]];
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    NSLog(@"Application will terminate");
}

-(void) applicationDidBecomeActive:(NSNotification *)notification {
    NSLog(@"Application is now active");
}


-(void) applicationDidResignActive:(NSNotification *)notification {
    NSLog(@"Application is now inactive");
}


- (void)diffusionDidCloseStream:(nonnull PTDiffusionStream *)stream {
    NSLog(@"\tStream Closed");
}

- (void)diffusionStream:(nonnull PTDiffusionStream *)stream didFailWithError:(nonnull NSError *)error {
    NSLog(@"\tStream Failed: %@", error);
}

- (void)diffusionStream:(nonnull PTDiffusionStream *)stream didSubscribeToTopicPath:(nonnull NSString *)topicPath specification:(nonnull PTDiffusionTopicSpecification *)specification {
    NSLog(@"\tSubscribed to %@ (%@)", topicPath, specification);
}

- (void)diffusionStream:(nonnull PTDiffusionStream *)stream didUnsubscribeFromTopicPath:(nonnull NSString *)topicPath specification:(nonnull PTDiffusionTopicSpecification *)specification reason:(PTDiffusionTopicUnsubscriptionReason)reason {
    NSLog(@"\tUnsubscribed from %@ (%@)", topicPath, specification);
}

- (void)diffusionStream:(nonnull PTDiffusionValueStream *)stream didUpdateTopicPath:(nonnull NSString *)topicPath specification:(nonnull PTDiffusionTopicSpecification *)specification oldJSON:(nullable PTDiffusionJSON *)oldJson newJSON:(nonnull PTDiffusionJSON *)newJson {
    NSLog(@"\tUpdated: %@ = %@", topicPath, newJson);
}

- (void)diffusionStream:(nonnull PTDiffusionStream *)stream didFetchTopicPath:(nonnull NSString *)topicPath content:(nonnull PTDiffusionContent *)content {
    NSLog(@"\tFetch result: %@ = %@", topicPath, content);
}

- (void)diffusionStream:(nonnull PTDiffusionStream *)stream didReceiveError:(nonnull NSError *)error fromSessionId:(nonnull PTDiffusionSessionId *)sessionId {
    NSLog(@"\tSession Error:%@", error);
}

@end
