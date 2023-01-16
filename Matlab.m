close all;
clear all;
clc; 
s = serialport('COM6',115200,'timeout',1);
muestras = 10000; 
i = 1;
figure;
title('Grafica de voltaje 2 ADC'); 
xlabel('numero de muestras');
ylabel('voltaje (V)');
grid on;
hold on; 
ylim([0 4]);
xlim([0 100]);
while i<=muestras
    if mod(i,100)==0
        xlim([i i+100]); 
    end
    str_1 = readline(s);
    str_2 = readline(s);
    ADC1 = str2double(str_1);
    ADC2 = str2double(str_2);
    voltaje_1(i) = (ADC1*3.3)/4095;
    voltaje_2(i) = (ADC2*3.3)/4095;
    plot(voltaje_1,'r');
    drawnow
    plot(voltaje_2,'b');
    drawnow
    i = i+1;
end