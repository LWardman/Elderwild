This project makes use of custom log categories, for example "AudioLog", "GridLog" and "CalendarLog".

These log categories should be used in their respective situations.
i.e. all UE_LOG's in the Calendar directory should use CalendarLog as it's log category.

To make use of this, follow these steps...
1. Run a session in the PIE
2. Open the Output Log
3. There is a section called "Filters". Toggle off "Show All", then toggle "CalendarLog"
4. Now you should only be able to see logs from the category "CalendarLog"
5. If you can't filter the logs by a certain category, it is very likely that no outputted logs exist from it yet

To create a new log category, create a new file in the Logging/ directory with the desired name. 
e.g. XLog.h & XLog.cpp

Populate the header file with this

'''
#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(XLog, Log, All);
'''

Then the source file with this

'''
#include "Logging/XLog.h"

DEFINE_LOG_CATEGORY(XLog);
'''

Then in the X/ directory, whenever you would use a UE_LOG, use this signature...
UE_LOG(XLog, Verbosity, TEXT("Information"));