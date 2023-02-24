#include "mex.h"
#include <windows.h>

void CALLBACK TimerProc(UINT uID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2) {
    SetEvent(reinterpret_cast<HANDLE>(dwUser));
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Check the number of input arguments
    if (nrhs != 1) {
        mexErrMsgIdAndTxt("waitUntilTime:nrhs", "One input argument required.");
    }
    // Check the number of output arguments
    if (nlhs != 0) {
        mexErrMsgIdAndTxt("waitUntilTime:nlhs", "No output arguments allowed.");
    }
    // Check that the input argument is a scalar
    if (!mxIsDouble(prhs[0]) || mxGetNumberOfElements(prhs[0]) != 1) {
        mexErrMsgIdAndTxt("waitUntilTime:invalidInput", "Input argument must be a scalar.");
    }

    // Get the target time in seconds
    double targetTime = mxGetScalar(prhs[0]);

    // Get the current time in seconds
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    double currentTime = static_cast<double>(count.QuadPart) / static_cast<double>(frequency.QuadPart);

    // Calculate the time difference between the target time and the current time
    double timeDiff = targetTime - currentTime;

    // If the time difference is negative, the target time has already passed
    if (timeDiff < 0) {
        mexErrMsgIdAndTxt("waitUntilTime:invalidInput", "Target time has already passed.");
    }

    // Create an event object for the multimedia timer
    HANDLE event = CreateEvent(NULL, TRUE, FALSE, NULL);

    // Set up the multimedia timer
    TIMECAPS tc;
    timeGetDevCaps(&tc, sizeof(tc));
    UINT resolution = min(max(tc.wPeriodMin, 1), tc.wPeriodMax);
    timeBeginPeriod(resolution);
    UINT timerId = timeSetEvent(static_cast<UINT>(timeDiff * 1000), resolution, TimerProc, reinterpret_cast<DWORD_PTR>(event), TIME_ONESHOT);

    // Wait for the event to be signaled by the multimedia timer
    WaitForSingleObject(event, INFINITE);

    // Clean up the multimedia timer and event objects
    timeKillEvent(timerId);
    timeEndPeriod(resolution);
    CloseHandle(event);
}
