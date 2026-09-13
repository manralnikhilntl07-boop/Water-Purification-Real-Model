port = "COM4";
s = serialport(port, 115200);
flush(s);

data = [];
timeData = [];
startTime = tic;

figure('Color','k');
h = plot(NaN, NaN, 'LineWidth', 2, 'Color', 'c');
ax = gca;
set(ax,'Color','k','XColor','w','YColor','w');
xlabel('Time (sec)','Color','w');
ylabel('TDS (raw value)','Color','w');
title('Live Water Quality Monitoring','Color','w');
grid off;
ax.YTick = 0:50:1000;
ax.XTick = 0:1:60;

while true
    if s.NumBytesAvailable > 0
        line = readline(s);
        val = str2double(line);
        if ~isnan(val)
            t = toc(startTime);
            timeData(end+1) = t;
            data(end+1) = val;

            set(h, 'XData', timeData, 'YData', data);
            xlim([max(0,t-60) t+1]);
            drawnow;
        end
    end
end