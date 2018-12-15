Skip to main content
Microsoft
Windows Dev Center
Windows PCs  Docs  Downloads  Samples  Support  Dashboard

DocsWindowsDesktopSynchronizationUsing SynchronizationUsing Semaphore Objects
Using Semaphore Objects
05/30/2018
2 minutes to read
The following example uses a semaphore object to limit the number of threads that can perform a particular task. First, it uses the CreateSemaphore function to create the semaphore and to specify initial and maximum counts, then it uses the CreateThread function to create the threads.

Before a thread attempts to perform the task, it uses the WaitForSingleObject function to determine whether the semaphore's current count permits it to do so. The wait function's time-out parameter is set to zero, so the function returns immediately if the semaphore is in the nonsignaled state. WaitForSingleObject decrements the semaphore's count by one.

When a thread completes the task, it uses the ReleaseSemaphore function to increment the semaphore's count, thus enabling another waiting thread to perform the task.

C++

Copy
#include <windows.h>
#include <stdio.h>

#define MAX_SEM_COUNT 10
#define THREADCOUNT 12

HANDLE ghSemaphore;

DWORD WINAPI ThreadProc( LPVOID );

int main( void )
{
    HANDLE aThread[THREADCOUNT];
    DWORD ThreadID;
    int i;

    // Create a semaphore with initial and max counts of MAX_SEM_COUNT

    ghSemaphore = CreateSemaphore( 
        NULL,           // default security attributes
        MAX_SEM_COUNT,  // initial count
        MAX_SEM_COUNT,  // maximum count
        NULL);          // unnamed semaphore

    if (ghSemaphore == NULL) 
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    // Create worker threads

    for( i=0; i < THREADCOUNT; i++ )
    {
        aThread[i] = CreateThread( 
                     NULL,       // default security attributes
                     0,          // default stack size
                     (LPTHREAD_START_ROUTINE) ThreadProc, 
                     NULL,       // no thread function arguments
                     0,          // default creation flags
                     &ThreadID); // receive thread identifier

        if( aThread[i] == NULL )
        {
            printf("CreateThread error: %d\n", GetLastError());
            return 1;
        }
    }

    // Wait for all threads to terminate

    WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

    // Close thread and semaphore handles

    for( i=0; i < THREADCOUNT; i++ )
        CloseHandle(aThread[i]);

    CloseHandle(ghSemaphore);

    return 0;
}

DWORD WINAPI ThreadProc( LPVOID lpParam )
{

    // lpParam not used in this example
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult; 
    BOOL bContinue=TRUE;

    while(bContinue)
    {
        // Try to enter the semaphore gate.

        dwWaitResult = WaitForSingleObject( 
            ghSemaphore,   // handle to semaphore
            0L);           // zero-second time-out interval

        switch (dwWaitResult) 
        { 
            // The semaphore object was signaled.
            case WAIT_OBJECT_0: 
                // TODO: Perform task
                printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                bContinue=FALSE;            

                // Simulate thread spending time on task
                Sleep(5);

                // Release the semaphore when task is finished

                if (!ReleaseSemaphore( 
                        ghSemaphore,  // handle to semaphore
                        1,            // increase count by one
                        NULL) )       // not interested in previous count
                {
                    printf("ReleaseSemaphore error: %d\n", GetLastError());
                }
                break; 

            // The semaphore was nonsignaled, so a time-out occurred.
            case WAIT_TIMEOUT: 
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break; 
        }
    }
    return TRUE;
}
 

 


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