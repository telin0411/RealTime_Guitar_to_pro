%
% EE3660 Spring 2013 HW3
% Making sense of a spectrogram
clear; close all;

%[y,fs] = wavread('EE3660-hw3-rhapsodyEntrance.wav');
y = load('data3.txt');
fs=32000;
y = y(:);

% Define window
N = fs*0.05; % window length
Nfft = 2^(1+ceil(log2(N)));

% set up the window
win = hamming(N+1);
win = win(1:end-1);

[S,ff,tt] = spectrogram(y,win,N/2,Nfft,fs); % Calculate the spectrum
    % Please type doc spectrogram for definitions of the parameters

% Post processing
surf(tt,ff,20*log10(abs(S)),'EdgeColor','none'); % actually making the plot
axis xy; axis tight; colormap(1-gray); view(0,90);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
set(gcf, 'PaperUnits', 'inches', 'PaperPosition', [0 0 16 9]);
print(gcf, '-depsc', sprintf('Spectrogram_hamm_pro(b)_%.0f.eps',N));

% Q2
Yn = 2*length(y)/N-1;% Length of Y[k,n]
for i = 1:Yn
    x = y((i-1)*N/2+1:(i+1)*N/2); %let x be the function of y[n+m] with length of Yn
    X = fft(x.*win, Nfft); % Do DFT with x and window's fuction w[m]
    Y(:,i) = X(1:Nfft/2+1); % assign the calculated value in matrix Y
end

% Post processing
%surf(tt,ff,20*log10(abs(Y)),'EdgeColor','none'); % actually making the plot
axis xy; axis tight; colormap(1-gray); view(0,90);
xlabel('Time (s)');
ylabel('Frequency (Hz)');

set(gcf, 'PaperUnits', 'inches', 'PaperPosition', [0 0 16 9]);
print(gcf, '-depsc', sprintf('Spectrogram_hamm_pro(b)_%.0f.eps',N));

fff=ff(1:150);
% Q3
judge=zeros(1,Yn);
n=0;
times=zeros(1,1);
for i=2:Yn;
    K=20*log10(abs(S(:,i)));
    K=K(1:length(ff));
    [pks,locs]=findpeaks(K,'MINPEAKHEIGHT',10,'MINPEAKDISTANCE',50);          
    if(isempty(locs))
        Fund_freq(i)=0;
        judge(i)=0;
        if judge(i-1)==1 && judge(i)==0 && i>1
            stop = i;
            n=n+1;
                times=[times(1:n) stop];
        end    
    else
        Fund_freq(i)=fff(locs(1));
        judge(i)=1;
        if judge(i-1)==0 && judge(i)==1 && i>1
            start = i;
            n=n+1;
            times=[times(1:n) start];
        end    
    end      
end;
Fund_freq(Fund_freq==289.0625)=283.00;
%Q= 20*log10(abs(S(:,202:235)));
times=times(2:length(times));
timesnew = zeros(1,1);
%
for i=1:length(times)/2
    startd = times(2*i-1);
    stopd = times(2*i);
    diff = times(2*i) -times(2*i-1);
   if diff > 5
      timesnew = [timesnew times(2*i-1) times(2*i)]; 
   else
      for a=startd:stopd
        Fund_freq(a) = 0;
      end    
   end   
end
timesnew = timesnew(2:length(timesnew));
for i=2:length(timesnew)/2
    if timesnew(2*i-1) -timesnew(2*i-2) <= 3
        startn = timesnew(2*i-1);
        stopn = timesnew(2*i);
        for a=startn:stopn
            Fund_freq(a) = 0;
        end        
        timesnew(2*i-1)=0;
        timesnew(2*i)=0;
    end
end

mm=0;
for i=2:length(timesnew)/2
    if timesnew(2*i-3)==0 && timesnew(2*i-2)==0
       mm=mm+2;
       timesnew(2*i-3:length(timesnew)-2) = timesnew(2*i-1:length(timesnew)); 
    end   
end

timesnew=timesnew(1:length(timesnew)-mm);

%Elimintating zeros in the end
if timesnew(length(timesnew))==0 && timesnew(length(timesnew)-1)==0
    timesnew=timesnew(1:length(timesnew)-2);
end

fref = [261 261 293 293 329 329 329 329 349 349 392 440];
%
for i=1:length(timesnew)/2
    %closee=0;
    fd261 = zeros(1,length(tt));
    fd257 = zeros(1,length(tt));
    fd437 = zeros(1,length(tt));
    fd283 = zeros(1,length(tt));
    fd195 = zeros(1,length(tt));
    fd295 = zeros(1,length(tt));
    fd109 = zeros(1,length(tt));
    fd218 = zeros(1,length(tt));
    fd351 = zeros(1,length(tt));
    fd171 = zeros(1,length(tt));
    fd234 = zeros(1,length(tt));
    fd328 = zeros(1,length(tt));
    start1 = timesnew(2*i-1);
    stop1 = timesnew(2*i);
    for a=start1:stop1
        fd261(a) = abs(Fund_freq(a) - 265.6249);
        fd437(a) = abs(Fund_freq(a) - 437.499);
        fd283(a) = abs(Fund_freq(a) - 282.9);
        fd195(a) = abs(Fund_freq(a) - 195.3);
        fd109(a) = abs(Fund_freq(a) - 109.3);
        fd218(a) = abs(Fund_freq(a) - 218.74);
        fd295(a) = abs(Fund_freq(a) - 295);
        fd257(a) = abs(Fund_freq(a) - 257.8124);
        fd351(a) = abs(Fund_freq(a) - 351.561);
        fd171(a) = abs(Fund_freq(a) - 171.87495);
        fd234(a) = abs(Fund_freq(a) - 234.36);
        fd328(a) = abs(Fund_freq(a) - 328.1249);
    end
    fd261(fd261==0) = 100;
    fd257(fd257==0) = 100;
    fd437(fd437==0) = 100;
    fd283(fd283==0) = 100;
    fd109(fd109==0) = 100;
    fd218(fd218==0) = 100;
    fd295(fd295==0) = 100;
    fd195(fd195==0) = 100;
    fd351(fd351==0) = 100;
    fd171(fd171==0) = 100;
    fd234(fd234==0) = 100;
    fd328(fd328==0) = 100;
    fminm = [min(fd171) min(fd261) min(fd195) min(fd295) min(fd109) min(fd218) min(fd328) min(fd437) min(fd234) min(fd351) min(fd257) min(fd283)];
    fmin = min(fminm);
    for b=1:length(fminm)
        if fminm(b) == fmin;
            fminp = b;
        end
    end
    for c=start1:stop1
        Fund_freq(c) = fref(fminp);
    end
end    
%
%KK=20*log10(abs(S(:,193:540)));

%Time duration
tempo = 70;
if(tempo==70)
   timediff=0.6;
   vdiff=timediff/tt(1);
end
%vdiff=21;
justify=zeros(1,length(tt));
for i=1:length(timesnew)/2
   justify(timesnew(2*i-1)) = 1; 
end
timesfake=[timesnew timesnew(length(timesnew)-1)+vdiff+1 timesnew(length(timesnew)-1)+2*vdiff-4];
for i=1:length(timesnew)/2
   %if timesfake(2*i+1) -timesfake(2*i-1) >= vdiff
   justify1 = justify(timesnew(2*i-1):timesnew(2*i-1)+vdiff-1);
   notelength(i) = sum(justify1); 
   %end
end
nl=length(notelength);

%Determining stop
timestop = zeros(1,length(timesnew)/2-1);
for i=1:length(timesnew)/2-1
   if timesnew(2*i+1) - timesnew(2*i) > vdiff
        timestop(i) = 10;
   end   
end
timestop = [timestop 0];
judgestop = sum(timestop) / 10;
%
figure();
plot(tt(1:Yn) , Fund_freq, 'm' ); 
   xlabel('time(s)'), ylabel('Fundamental Frequency(Hz)');  
set(gcf, 'PaperUnits', 'inches', 'PaperPosition', [0 0 16 9]);
print(gcf, '-depsc', sprintf('Freq_detect_hamm_%.0f.eps',N));

if timestop(1) > 0
    noteinfol = [notelength(1)*4 1*4];
else
    noteinfol = [notelength(1)*4];
end
if timestop(1) > 0
    noteinfof = [Fund_freq(timesnew(1)) timestop(1)];
else
    noteinfof = [Fund_freq(timesnew(1))];
end
%Preparing for the output txt file
for i=2:nl
    if timestop(i) > 0
        noteinfol = [noteinfol notelength(i)*4 1*4];     
    else
        noteinfol = [noteinfol notelength(i)*4];
    end
end
for i=2:nl
    if timestop(i) > 0
        noteinfof = [noteinfof Fund_freq(timesnew(2*i-1)) timestop(i)];     
    else
        noteinfof = [noteinfof Fund_freq(timesnew(2*i-1))];
    end
end
noteinfo = [noteinfol;noteinfof];
%
fid = fopen('noteinfo.txt','wt');
for a=1:nl+judgestop
fprintf(fid,'%d ',noteinfo(1,a));
end
fprintf(fid,'\n');
for a=1:nl+judgestop
fprintf(fid,'%d ',noteinfo(2,a));
end
fclose(fid);
%

    
