% Tests the accuracy of the getTime and waitUntilTime functions when
% repeatedly performing an action at the specified interval. In this
% example, a pause for a random length of time is used as a dummy action.
%
% Assumes the getTime and waitUntilTime functions are available on the
% MATLAB path.

clearvars;

% Set the number of iterations and the wait time in seconds.
numIterations = 500;
waitTime = 0.5;

% Preallocate the result vectors.
results = zeros(1, numIterations);

% Wait until a set time references to a fixed start time. This prevents
% drift.
startTime = getTime();
for ind = 1:numIterations
    waitUntilTime(startTime + ind * waitTime);
    results(ind) = getTime();
    pause(0.25 * rand);
end

% Convert time-stamps to time in milliseconds.
results = 1e3 * (results(2:end) - results(1:end-1));

% Plot a histogram of the results.
figure;
histogram(results, 'BinWidth', 0.1);
title('Drift In Timing');
xlabel('Time Between Operations (ms)');
ylabel('Count');
