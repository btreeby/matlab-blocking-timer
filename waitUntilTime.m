%WAITUNTILTIME Block execution until the specified time has been reached.
%   WAITUNTILTIME(TARGETTIME) blocks execution until the current time is
%   greater than or equal to TARGETTIME, where TARGETTIME is the time in
%   seconds since the epoch (January 1, 1970 00:00:00 UTC).
%
%   The function uses a high-precision multimedia timer to achieve an
%   accuracy better than 10 microseconds.
%
%   If TARGETTIME is less than the current time, the function returns an
%   error.
%
%   Example:
%       % Block execution for 1 second
%       waitUntilTime(getTime + 1);
%
%   See also GETTIME.

% Copyright (C) 2023- University College London (Bradley Treeby).