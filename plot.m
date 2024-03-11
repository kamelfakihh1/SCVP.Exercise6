x = [1, 10, 100, 1000, 10000, 100000];
y = [28.519, 28.05, 25.511, 18.551, 16.094, 16.261];

plot(x, y, 'r');
xlabel('X');
ylabel('Y');
title('Time quantum vs wall clock time');
xlim([1 100000])
ylim([0 30])
set(gca, 'XScale', 'log'); % set logarithmic scale for x-axis
# grid on;

