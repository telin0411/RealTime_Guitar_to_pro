using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;

using AForge.Math;
using NAudio.Wave;
using NAudio.CoreAudioApi;
using System.Diagnostics;
using System.IO;


namespace Demo_SourceStream
{
    public partial class Form1 : Form
    {
        public int fs=32;                  //KHz
        public int ms=100;              //ms
        public float[] t=new float[9600];
        public int indexsample;
        public int count = 0;
        //public CircularStream buffer1;


        public Form1()
        {
            InitializeComponent();
            timer1.Enabled = false;
            timer2.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            List<NAudio.Wave.WaveInCapabilities> sources = new List<NAudio.Wave.WaveInCapabilities>();

            for (int i = 0; i < NAudio.Wave.WaveIn.DeviceCount; i++)
            {
                sources.Add(NAudio.Wave.WaveIn.GetCapabilities(i));
            }

            listView1.Items.Clear();

            foreach (var source in sources)
            {
                ListViewItem item = new ListViewItem(source.ProductName);
                item.SubItems.Add(new ListViewItem.ListViewSubItem(item, source.Channels.ToString()));
                listView1.Items.Add(item);
            }
        }

        NAudio.Wave.WaveIn sourceStream=null ;    // waveIn is sourceStream
        //NAudio.Wave.BufferedWaveProvider bwp=null;      
       // NAudio.Wave.WaveOut waveOut = null;
        //NAudio.Wave.WaveFileWriter waveWriter = null;
       // NAudio.Wave.WaveInProvider waveIn = null;
       // NAudio.Wave.WaveBuffer wavebuffer = null;
        NAudio.Wave.DirectSoundOut waveOut = null;
       // NAudio.Wave.WaveStream stream = null;
       
        
        private void button2_Click(object sender, EventArgs e)
        {
           
            
            if (listView1.SelectedItems.Count == 0) return;



            int deviceNumber = listView1.SelectedItems[0].Index;
            
            //waveOut = new NAudio.Wave.WaveOut(); ;
            sourceStream = new NAudio.Wave.WaveIn();
            sourceStream.DeviceNumber = deviceNumber;
            sourceStream.WaveFormat = new NAudio.Wave.WaveFormat(48000, NAudio.Wave.WaveIn.GetCapabilities(deviceNumber).Channels);
            
            sourceStream.DataAvailable += new EventHandler<WaveInEventArgs>(sourceStream_DataAvailable);
            //waveWriter = new NAudio.Wave.WaveFileWriter(save.FileName, sourceStream.WaveFormat);
            
            sourceStream.BufferMilliseconds = 100;
            //wavebuffer = new NAudio.Wave.WaveBuffer();
            //bwp = new NAudio.Wave.BufferedWaveProvider(sourceStream.WaveFormat);
           // bwp.DiscardOnBufferOverflow = true;

            NAudio.Wave.WaveInProvider waveIn = new NAudio.Wave.WaveInProvider(sourceStream);
            waveOut = new NAudio.Wave.DirectSoundOut();
            waveOut.Init(waveIn);
                                    
            sourceStream.StartRecording();
            //waveOut.Init(bwp);
            waveOut.Play();
           // sourceStream.StopRecording();
           // Start(sender,e);
            timer1.Enabled=true;


            ++count;
               
            
        }

        private void Stop(object sender, EventArgs e)
        {
            
            if (waveOut != null)
            {
                waveOut.Stop();
                waveOut.Dispose();
                waveOut = null;
            }
            if (sourceStream != null)
            {
                sourceStream.StopRecording();
                sourceStream.Dispose();
                sourceStream = null;
            }
            Start(sender, e);
           
        }
        /*public enum Direction
        {
            Forward = 1,
            Backward = -1
        };*/

        private void Start(object sender, EventArgs e)
        {
            // Compute the execute time
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            byte[] buffer = new byte[1600]; // similar to frequency response
            double[] samples = new double[2*fs*ms];
            double[] chan1 = new double[fs*ms];
            Complex[] chanfft = new Complex[fs * ms];
            double[] chan2 = new double[fs*ms];
            double[] tt = new double[2 * fs * ms];
            int x = 0;
            // int read = 0;
            //int c=0;
            double max = 0;
            int index;
            
            

            StreamWriter sw = new StreamWriter("data_guitar.txt", true);
            StreamWriter sw1 = new StreamWriter("data_guitar_FFT.txt", false);
            for (int i = 0; i < 2 * fs * ms; ++i)
            {
                tt[i] = t[i];

                if (x % 2 == 0)
                {
                    chan1[x / 2] = tt[x];
                    chart1.Series[0].Points.Add(chan1[x / 2]);
                    //chanfft2[x/2] = chan1[x/2];

                }
                /*if (x % 2 == 1)
                {
                    chan2[(x - 1) / 2] = tt[x];
                    chart1.Series[1].Points.Add(chan2[(x - 1) / 2]);
                }*/

                if (tt[x] > max)
                {
                    max = tt[x];
                    index = x;
                    label2.Text = max.ToString();
                    //label6.Text = index.ToString();

                }
                chanfft[x/2] = new Complex(chan1[x/2],0);
                sw.WriteLine(chan1[x/2]);
                x++;

            }
            
            //FourierTransform.FFT(chanfft, FourierTransform.Direction.Forward);
            for (int i = 0; i < fs * ms; i++)
            {
                sw1.WriteLine(chanfft[i]);
            }
            sw.Close();
            sw1.Close();

            int N = 160;
            double Nfft1 = Math.Pow(2, 1+Math.Ceiling(Math.Log(N,2)));
            StreamWriter sw2 = new StreamWriter("Nfft.txt", false);
            sw2.WriteLine(Nfft1);
            sw2.Close();
            StreamReader sr = new StreamReader("Nfft.txt");
            int Nfft2 = sr.Read();
            sr.Close();
            StreamWriter sw3 = new StreamWriter("Nfftresult.txt", false);
            sw3.WriteLine(Nfft2);
            sw3.Close();
            int Nfft = 512;

            //int Yn = 2 * fs * ms / 160 - 1;
            //Spectrogram
            /*int Yn = 39;
            double [] xx = new double[3201];
            double[] XX = new double[Nfft];
            Complex[] XXX = new Complex[512];
            //double[] chanffttospec = new double[Nfft];
            Complex[,] Y = new Complex[257,40];
            StreamWriter sw4 = new StreamWriter("Spectrogram.txt", true);
            for (int i = 1; i <= Yn; i++)
            {
                for (int a = (i - 1) * N / 2 + 1; a < (i + 1) * N / 2; a++)
                {
                    xx[a] = chan1[a];
                }
                for (int b = 0; b <= Yn; b++)
                {
                    XX[b] = xx[b] * window(N)[b];
                }
                for (int c = Yn+1; c <= Nfft-1; c++)
                {
                    XX[c] = 0;
                }
                for (int d = 0; d <= Nfft - 1; d++)
                {
                    XXX[d] = new Complex(XX[d], 0);
                }
                FourierTransform.FFT(XXX, FourierTransform.Direction.Forward);
                for (int ee = 0; ee <= 256; ee++)
                {
                    Y[ee,i] = 10*XXX[ee];
                    sw4.WriteLine(Y[ee,i]);
                }
                
            }
            StreamWriter sw5 = new StreamWriter("Manitude_Spectrogram.txt", true);
            double[] K = new double[257];
            //Transforming spectrogram to dB unit
                sw4.Close();
            //Finding fundamental frequency
            for (int i = 1; i <= Yn; i++)
            {
                //dB for S with its absolute value
                for (int a = 0; a <= Nfft / 2; a++)
                {
                    K[a] = 20*Math.Log10(Mag(Y[a, i]));
                    sw5.WriteLine(K[a]);
                }
                //Local peak function

            }
            sw5.Close();*/
                //chart2.Series[0].Points.Add(r);
                /* r is the correlation coefficient at "delay" */

                // Using hyperbolic surface to detect the source degree
                // check the source directon in front of the microphone array from left or right
                //int direction;



                // compute the angle

                stopwatch.Stop();
            Console.WriteLine("Time elapsed: {0}", stopwatch.Elapsed);
            //timer1.Enabled = false;
           // button2_Click(sender, e);
           timer2.Enabled = false;
            TimeStop(sender,e);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void sourceStream_DataAvailable(object sender, NAudio.Wave.WaveInEventArgs e)
        {

            label10.Text = e.BytesRecorded.ToString();
            label11.Text = e.Buffer.Length.ToString();          
            var buffer = e.Buffer;
            var buffer1 = new CircularBuffer<byte>(e.Buffer.Length-100,true);
            buffer1.Put(buffer);
           
           
            //buffer1.Clear();
            
            

            //MemoryStream memory = new MemoryStream(buffer);
           
            int i = 0;
            for (int index = 0; index < e.BytesRecorded; index += 2)
            {
                short sample = (short)((buffer[index + 1] << 8) | buffer[index]);
               // short sample = (short)(buffer[index]);
                //short sample=(short)(queue1.Enqueue((byte)index));
                float sample32 = sample / 32768f;
                t[i] = sample32;
                //memory.Dispose();
                
               
               // short truncated = (short)(Math.Pow(2,15)-1);
               // buffer[index]=(byte)(truncated & 0x00ff);
                //buffer[index+1]=(byte)((truncated & 0xff00)<<8);
               
                ++i;
            }

           
           
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Stop(sender,e);
          
            //timer1.Enabled = false;
        }
        private void TimeStop(object sender,EventArgs e)
        {
            
           timer1.Enabled = false;

           int deviceNumber = listView1.SelectedItems[0].Index;
           sourceStream = new NAudio.Wave.WaveIn();
           sourceStream.DeviceNumber = deviceNumber;
           sourceStream.WaveFormat = new NAudio.Wave.WaveFormat(48000, NAudio.Wave.WaveIn.GetCapabilities(deviceNumber).Channels);

           sourceStream.DataAvailable += new EventHandler<WaveInEventArgs>(sourceStream_DataAvailable);
           //waveWriter = new NAudio.Wave.WaveFileWriter(save.FileName, sourceStream.WaveFormat);

           sourceStream.BufferMilliseconds = 100;
           sourceStream.StartRecording();
           //button2_Click(sender, e);
           timer2.Enabled = true;
           
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (waveOut != null)
            {
                waveOut.Stop();
                waveOut.Dispose();
                waveOut = null;
            }
            if (sourceStream != null)
            {
                sourceStream.StopRecording();
                sourceStream.Dispose();
                sourceStream = null;
            }
            
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            chart1.Series[0].Points.Clear();
            Stop(sender,e);
        }

       

        //private void timer2_Tick(object sender, EventArgs e)
        //{
              
              //timer2.Enabled = false;
        //}

        private double Mag(Complex c)
        {
          double abs;
          abs = Math.Sqrt(c.Re*c.Re+c.Im*c.Im);
            return abs;
        }
        private double[] window(int N)
        {
            double[] win =new double[N];
            for (int n = 1; n < N; n++)
            {
                win[n] = 0.54f - 0.46f * (double)Math.Cos((2 * Math.PI * n) / (N - 1));
                
            }
            return win;
        } 
        
        /*public static void FFT(Complex[] data, FourierTransform.Direction direction)
        {
            int n = data.Length;
            int m = Tools.Log2(n);
            int tn = 1, tm;
            for (int k = 1; k <= m; k++)
            {
                Complex[] rotation = FourierTransform.;
                tm = tn;
                tn <<= 1;
                for (int i = 0; i <= tm; i++)
                {
                    Complex t = rotation[i];
                    for (int even = i; even < n; even += tn)
                    {
                        int odd = even + tm;
                        Complex ce = data[even];
                        Complex co = data[odd];
                        double tr = co.Re + t.Re - co.Im * t.Im;
                        double ti = co.Re * t.Im + co.Im * t.Re;

                        data[even].Re += tr;
                        data[even].Im += ti;
                        data[odd].Re = ce.Re - tr;
                        data[odd].Im = ce.Im - ti;
                    }
                }

            }
            if (direction == FourierTransform.Direction.Forward)
            {
                for (int i = 0; i < n; i++)
                {
                    data[i].Re /= (double)n;
                    data[i].Im /= (double)n;
                }
            }
        }*/
        
        private void DFT()
        {
            
            
            int N = 512;
            double[] X = new double[N];
            double[] Freq = new double[N];
            float Delta_F;
            Delta_F = fs*1000 / N;
           
        }
    }
}
