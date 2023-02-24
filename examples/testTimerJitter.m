% Tests the jitter in the getTime and waitUntilTime functions.
%
% Assumes the getTime and waitUntilTime functions are available on the
% MATLAB path.

clearvars;

% Set the number of iterations and the wait time in seconds.
numIterations = 500;
waitTime = 0.1;

% Preallocate the result vectors.
jitter = zeros(1, numIterations);

% Repeatedly call getTime and waitUntilTime.
for ind = 1:numIterations
    startTime = getTime();
    waitUntilTime(startTime + waitTime);
    jitter(ind) = getTime() - startTime - waitTime;
end

% Plot a histogram of the results
figure;
histogram(1e3 * jitter);
title('Jitter In Timing');
xlabel('Jitter (ms)');
ylabel('Count');
