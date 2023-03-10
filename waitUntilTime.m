%WAITUNTILTIME Block execution until the specified time has been reached.
%   WAITUNTILTIME(TARGETTIME) blocks execution until the current time is
%   greater than or equal to TARGETTIME. If TARGETTIME is less than the
%   current time, the function returns an error.
%
%   The function uses a high-precision multimedia timer to achieve
%   real-world jitter / drift on the order of 1 ms.
%
%   Note, the time reference for this function is specific to the system on
%   which the code is running, and is not synchronized with any external
%   time standard such as UTC or GPS time.
%
%   Example:
%       % Block execution for 1 second
%       waitUntilTime(getTime + 1);
%
%   See also GETTIME.

% Copyright (C) 2023- University College London (Bradley Treeby).
