//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: BIND_ERR_MSG
//
// MessageText:
//
//  %1
//
#define BIND_ERR_MSG                     ((DWORD)0xC0000001L)

//
// MessageId: BIND_WARN_MSG
//
// MessageText:
//
//  %1
//
#define BIND_WARN_MSG                    ((DWORD)0x80000002L)

//
// MessageId: BIND_INFO_MSG
//
// MessageText:
//
//  %1
//
#define BIND_INFO_MSG                    ((DWORD)0x40000003L)

