// **********************************************************************************
// OpenNode library for OpenMiniHub IoT
// **********************************************************************************
// Copyright Martins Ierags (2016), martins.ierags@gmail.com
// http://openminihub.com/
// **********************************************************************************
// License
// **********************************************************************************
// This program is free software; you can redistribute it 
// and/or modify it under the terms of the GNU General    
// Public License as published by the Free Software       
// Foundation; either version 3 of the License, or        
// (at your option) any later version.                    
//                                                        
// Licence can be viewed at                               
// http://www.gnu.org/licenses/gpl-3.0.txt
//
// Please maintain this license information along with authorship
// and copyright notices in any redistribution of this code
// **********************************************************************************
#ifndef NodeContact_h
#define NodeContact_h
#include "OpenProtocol.h"
#include "NodeType.h"

typedef enum {
  k1Minute = 60, // In seconds
  k15Minutes = 900,
  k1Hour = 3600,
  k1Day = 86400,
} ContactReportInterval_t;

#define kReportingIntervalNone (0)

typedef bool (*NodeValue)(unsigned char id); 

class NodeContact
{
public:
  NodeContact(unsigned char contactId, ContactData_t contactData, NodeValue valueFunc = NULL, unsigned long reportingInterval = kReportingIntervalNone);

  void refreshValue();

  bool sendReport(unsigned char destination=0, bool useDestinationValue=false, bool doRefresh = true);

  bool isEnqueued() { return mIsEnqueued; }; // Enqueueing. Set from interrupt mode will cause report to be sent in the next run loop

  unsigned long nextTickInterval() { return mNextReport; };
  void intervalTick(unsigned long time);
  void intervalReset() { mNextReport = mReportingInterval; };

  unsigned char id() { return mId; };
  void setId(unsigned char id) { mId = id; }
  ContactData_t data() { return mData; };
  void setType(ContactData_t data) { mData = data; }
  
private:
  unsigned char mId;
  ContactData_t mData;
  unsigned long mReportingInterval;
  unsigned long mNextReport;
  NodeValue mValueFunc;
  bool mIsEnqueued;
};

#endif // NodeContact_h
