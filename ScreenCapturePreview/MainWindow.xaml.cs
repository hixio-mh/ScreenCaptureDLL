﻿using System;
using System.Diagnostics;
using System.Threading.Tasks;
using System.Windows;

namespace ScreenCapture
{
    public partial class MainWindow : Window
    {
        //Screen Capture Variables
        public static CaptureDetails vCaptureDetails;
        public static CaptureSettings vCaptureSettings;

        //Initialize window
        public MainWindow()
        {
            InitializeComponent();
        }

        //Initialize Screen Capture
        private async Task<bool> InitializeScreenCapture(int delayTime)
        {
            try
            {
                Debug.WriteLine("Initializing screen capture: " + DateTime.Now);

                //Set capture settings
                vCaptureSettings = new CaptureSettings
                {
                    MonitorId = 0,
                    MaxPixelDimension = 1000,
                    HDRtoSDR = true,
                    HDRPaperWhite = (float)slider_HDRPaperWhite.Value,
                    HDRMaximumNits = (float)slider_HDRMaximumNits.Value,
                    Saturation = (float)slider_Saturation.Value,
                    RedChannel = (float)slider_RedChannel.Value,
                    GreenChannel = (float)slider_GreenChannel.Value,
                    BlueChannel = (float)slider_BlueChannel.Value,
                    Brightness = (float)slider_Brightness.Value,
                    Contrast = (float)slider_Contrast.Value,
                    Gamma = (float)slider_Gamma.Value,
                };

                //Initialize screen capture
                bool captureInitialized = CaptureImport.CaptureInitialize(vCaptureSettings, out vCaptureDetails);

                //Set capture details string
                string captureDetails = "Width: " + vCaptureDetails.Width;
                captureDetails += "\nHeight: " + vCaptureDetails.Height;
                captureDetails += "\nPixelByteSize: " + vCaptureDetails.PixelByteSize;
                captureDetails += "\nWidthByteSize: " + vCaptureDetails.WidthByteSize;
                captureDetails += "\nTotalByteSize: " + vCaptureDetails.TotalByteSize;
                captureDetails += "\nHDREnabled: " + vCaptureDetails.HDREnabled;
                captureDetails += "\nHDRtoSDR: " + vCaptureSettings.HDRtoSDR;
                captureDetails += "\nSDR White Level: " + vCaptureDetails.SDRWhiteLevel;

                //Update interface details
                Debug.WriteLine(captureDetails);
                textblock_CaptureDetails.Text = captureDetails;
                return captureInitialized;
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Failed to initialize screen capture: " + ex.Message);
                return false;
            }
            finally
            {
                await Task.Delay(delayTime);
            }
        }

        //Handle window initialized event
        protected override async void OnSourceInitialized(EventArgs e)
        {
            try
            {
                //Initialize screen capture
                await InitializeScreenCapture(200);

                //Loop and capture screen
                while (true)
                {
                    IntPtr bitmapIntPtr = IntPtr.Zero;
                    try
                    {
                        //Check window state
                        if (this.WindowState == WindowState.Minimized)
                        {
                            Debug.WriteLine("Minimized skipping preview update.");
                            continue;
                        }

                        //Capture screenshot
                        try
                        {
                            bitmapIntPtr = CaptureImport.CaptureScreenshot();
                        }
                        catch { }

                        //Check screenshot
                        if (bitmapIntPtr == IntPtr.Zero)
                        {
                            Debug.WriteLine("Screenshot is corrupted, restarting capture.");
                            await InitializeScreenCapture(200);
                            continue;
                        }

                        //Update screen capture preview
                        image_DebugPreview.Source = CaptureBitmap.BitmapIntPtrToBitmapSource(bitmapIntPtr, vCaptureDetails, vCaptureSettings);
                    }
                    catch (Exception ex)
                    {
                        Debug.WriteLine("Screen capture loop failed: " + ex.Message);
                    }
                    finally
                    {
                        //Clear screen capture resources
                        if (bitmapIntPtr != IntPtr.Zero)
                        {
                            CaptureImport.CaptureFreeMemory(bitmapIntPtr);
                        }

                        //Delay next screen capture
                        await Task.Delay(250);
                    }
                }
            }
            catch { }
        }

        private void slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            try
            {
                //Update slider text
                text_HDRPaperWhite.Text = text_HDRPaperWhite.Tag + " " + slider_HDRPaperWhite.Value.ToString("0.0000");
                text_HDRMaximumNits.Text = text_HDRMaximumNits.Tag + " " + slider_HDRMaximumNits.Value.ToString("0.0000");
                text_Saturation.Text = text_Saturation.Tag + " " + slider_Saturation.Value.ToString("0.0000");
                text_RedChannel.Text = text_RedChannel.Tag + " " + slider_RedChannel.Value.ToString("0.0000");
                text_GreenChannel.Text = text_GreenChannel.Tag + " " + slider_GreenChannel.Value.ToString("0.0000");
                text_BlueChannel.Text = text_BlueChannel.Tag + " " + slider_BlueChannel.Value.ToString("0.0000");
                text_Brightness.Text = text_Brightness.Tag + " " + slider_Brightness.Value.ToString("0.0000");
                text_Contrast.Text = text_Contrast.Tag + " " + slider_Contrast.Value.ToString("0.0000");
                text_Gamma.Text = text_Gamma.Tag + " " + slider_Gamma.Value.ToString("0.0000");

                //Set capture settings
                vCaptureSettings = new CaptureSettings
                {
                    MonitorId = 0,
                    MaxPixelDimension = 1000,
                    HDRtoSDR = true,
                    HDRPaperWhite = (float)slider_HDRPaperWhite.Value,
                    HDRMaximumNits = (float)slider_HDRMaximumNits.Value,
                    Saturation = (float)slider_Saturation.Value,
                    RedChannel = (float)slider_RedChannel.Value,
                    GreenChannel = (float)slider_GreenChannel.Value,
                    BlueChannel = (float)slider_BlueChannel.Value,
                    Brightness = (float)slider_Brightness.Value,
                    Contrast = (float)slider_Contrast.Value,
                    Gamma = (float)slider_Gamma.Value,
                };

                bool settingsUpdated = CaptureImport.CaptureUpdateSettings(vCaptureSettings);
                Debug.WriteLine("Capture settings updated: " + settingsUpdated);
            }
            catch { }
        }
    }
}