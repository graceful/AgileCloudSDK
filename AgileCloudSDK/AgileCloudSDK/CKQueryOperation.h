//
//  CKQueryOperation.h
//  AgileCloudSDK
//
//  Created by Adam Wulf on 6/22/16.
//  Copyright © 2016 AgileBits. All rights reserved.
//

#import <AgileCloudSDK/AgileCloudSDK.h>

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKQueryCursor : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
@end

@class CKQuery, CKRecord, CKRecordZoneID;

/* Query operations have a dynamically defined maximum number of results.  If the results of a query
 trip this max, your completion block will invoked with a cursor.  Issue a new query with that cursor
 to fetch the next batch of results. */
CK_EXTERN const NSUInteger CKQueryOperationMaximumResults NS_AVAILABLE(10_10, 8_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKQueryOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithQuery:(CKQuery *)query;
- (instancetype)initWithCursor:(CKQueryCursor *)cursor NS_UNAVAILABLE;

@property (nonatomic, copy, nullable) CKQuery *query;
//@property (nonatomic, copy, nullable) CKQueryCursor *cursor;

/* This property indicates which record zone to query. For query operations constructed using a cursor, this
 property is ignored and instead will be evaluated in the record zone in which the cursor was originally created. */
@property (nonatomic, copy, nullable) CKRecordZoneID *zoneID;

/* Defaults to CKQueryOperationMaximumResults.
 Queries may return fewer than resultsLimit in some scenarios:
 - There are legitimately fewer than 'resultsLimit' number of records matching the query (and visible to the current user).
 - During the process of querying and fetching the results, some records were deleted, or became un-readable by the current user.
 When determining if there are more records to fetch, always check for the presence of a cursor in queryCompletionBlock. */
@property (nonatomic, assign) NSUInteger resultsLimit;

/* Declares which user-defined keys should be fetched and added to the resulting CKRecords.  If nil, declares the entire record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.  Defaults to nil. */
@property (nonatomic, copy, nullable) NSArray <NSString *> *desiredKeys;

/* This block will be called once for every record that is returned as a result of the query. The callbacks will happen in the order that the results were sorted in. */
@property (nonatomic, copy, nullable) void (^recordFetchedBlock)(CKRecord *record);

/*  This block is called when the operation completes.
 The [NSOperation completionBlock] will also be called if both are set. */
@property (nonatomic, copy, nullable) void (^queryCompletionBlock)(CKQueryCursor * __nullable cursor, NSError * __nullable operationError);

@end
NS_ASSUME_NONNULL_END