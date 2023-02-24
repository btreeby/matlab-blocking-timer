#include <windows.h>
#include "mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // Create an mxArray for the output argument
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);

    // Get a pointer to the output data
    double *out = mxGetPr(plhs[0]);

    // Get the current time in seconds
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    double currentTime = static_cast<double>(count.QuadPart) / static_cast<double>(frequency.QuadPart);

    *out = currentTime;
}
