Skip to main content
Microsoft
Windows Dev Center
Windows PCs  Docs  Downloads  Samples  Support  Dashboard

DocsWindowsDesktopSynchronizationUsing SynchronizationUsing Named Objects
In this article
First Process
Second Process
Related topics
Using Named Objects
05/30/2018
2 minutes to read
The following example illustrates the use of object names by creating and opening a named mutex.

First Process
The first process uses the CreateMutex function to create the mutex object. Note that this function succeeds even if there is an existing object with the same name.

C++

Copy
#include <windows.h>
#include <stdio.h>
#include <conio.h>

// This process creates the mutex object.

int main(void)
{
    HANDLE hMutex; 

    hMutex = CreateMutex( 
        NULL,                        // default security descriptor
        FALSE,                       // mutex not owned
        TEXT("NameOfMutexObject"));  // object name

    if (hMutex == NULL) 
        printf("CreateMutex error: %d\n", GetLastError() ); 
    else 
        if ( GetLastError() == ERROR_ALREADY_EXISTS ) 
            printf("CreateMutex opened an existing mutex\n"); 
        else printf("CreateMutex created a new mutex.\n");

    // Keep this process around until the second process is run
    _getch();

    CloseHandle(hMutex);

    return 0;
}
Second Process
The second process uses the OpenMutex function to open a handle to the existing mutex. This function fails if a mutex object with the specified name does not exist. The access parameter requests full access to the mutex object, which is necessary for the handle to be used in any of the wait functions.

C++

Copy
#include <windows.h>
#include <stdio.h>

// This process opens a handle to a mutex created by another process.

int main(void)
{
    HANDLE hMutex; 

    hMutex = OpenMutex( 
        MUTEX_ALL_ACCESS,            // request full access
        FALSE,                       // handle not inheritable
        TEXT("NameOfMutexObject"));  // object name

    if (hMutex == NULL) 
        printf("OpenMutex error: %d\n", GetLastError() );
    else printf("OpenMutex successfully opened the mutex.\n");

    CloseHandle(hMutex);

    return 0;
}
Related topics
Object Names

Using Mutex Objects

 

 


Filter by title
Synchronization
What's New in Synchronization
About Synchronization
Using Synchronization
Waiting for Multiple Objects
Using Named Objects
Using Event Objects
Using Mutex Objects
Using Semaphore Objects
Using Waitable Timer Objects
Using Waitable Timers with an Asynchronous Procedure Call
Using Critical Section Objects
Using Condition Variables
Using One-Time Initialization
Using Singly Linked Lists
Using Timer Queues
Synchronization Reference

Is this page helpful?
English (United States)
Previous Version Docs Blog Contribute Privacy & Cookies Terms of Use Site Feedback Trademarks