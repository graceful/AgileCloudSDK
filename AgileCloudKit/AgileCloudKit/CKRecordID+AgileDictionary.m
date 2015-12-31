//
//  CKRecordID+AgileDictionary.m
//  AgileCloudKit
//
//  Copyright (c) 2015 AgileBits. All rights reserved.
//

#import "CKRecordID+AgileDictionary.h"

@implementation CKRecordID (AgileDictionary)

- (NSDictionary *)asAgileDictionary
{
    return @{ @"recordName": self.recordName,
              @"zoneID": self.zoneID.zoneName };
}

@end
