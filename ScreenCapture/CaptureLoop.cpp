#pragma once
#include "CaptureVariables.h"
#include "CaptureScreen.cpp"
#include "CaptureAudio.cpp"
#include "CaptureVideoStop.cpp"
#include "CaptureWrite.cpp"

namespace
{
	VOID LoopCaptureStatus()
	{
		try
		{
			//Check capture status while allowed
			while (vCaptureInstance.vCaptureStatusLoopAllowed)
			{
				try
				{
					//Check capture device change
					if (!vDirectXInstance.iDxgiFactory7->IsCurrent())
					{
						//Trigger capture event
						if (vCaptureEventDeviceChangeDetected)
						{
							std::thread threadEvent(vCaptureEventDeviceChangeDetected);
							threadEvent.detach();
						}

						//Note: triggers on resolution change, hdr switch and driver resets.
						AVDebugWriteLine("Capture device has changed, reset recommended.");
					}

					//Delay status update
					AVHighResDelay(1000);
				}
				catch (...) {}
			}
		}
		catch (...) {}

		//Reset thread variables
		vCaptureInstance.vCaptureStatusLoopFinished = true;
	}

	VOID LoopWriteScreen()
	{
		try
		{
			//Get media frame duration time
			ULONGLONG mediaTimeDuration;
			MFFrameRateToAverageTimePerFrame(vMediaSettings.VideoFrameRate, 1, &mediaTimeDuration);

			//Set thread characteristics
			DWORD taskIndex = 1;
			HANDLE mmThread = AvSetMmThreadCharacteristicsW(L"Pro Audio", &taskIndex);
			if (mmThread)
			{
				AvSetMmThreadPriority(mmThread, AVRT_PRIORITY_CRITICAL);
			}

			//Write media in loop while allowed
			while (vMediaFoundationInstance.vMediaWriteLoopAllowed)
			{
				try
				{
					//Get media frame start time
					LARGE_INTEGER qpcTimeCurrent;
					QueryPerformanceCounter(&qpcTimeCurrent);
					ULONGLONG mediaTimeStart = qpcTimeCurrent.QuadPart - vMediaFoundationInstance.vMediaTimeStartLoop;

					//Update screen texture
					if (UpdateScreenTexture())
					{
						//Write media bytes to sink
						std::thread threadWriteSample(WriteMediaTexture2D, vCaptureInstance.iD3D11Texture2D0RenderTargetView, vCaptureDetails.TotalByteSize, false, vMediaFoundationInstance.vOutVideoStreamIndex, mediaTimeStart, mediaTimeDuration);
						threadWriteSample.detach();
					}

					//Delay screen capture
					AVHighResDelay(mediaTimeDuration / vReferenceTimeToMilliseconds);
				}
				catch (...) {}
			}
		}
		catch (...) {}

		//Reset thread variables
		vMediaFoundationInstance.vMediaWriteLoopFinishedScreen = true;
	}

	VOID LoopWriteAudio()
	{
		try
		{
			//Get media frame duration time
			ULONGLONG mediaTimeDuration = vReferenceTimeFrameDuration;

			//Set thread characteristics
			DWORD taskIndex = 0;
			HANDLE mmThread = AvSetMmThreadCharacteristicsW(L"Pro Audio", &taskIndex);
			if (mmThread)
			{
				AvSetMmThreadPriority(mmThread, AVRT_PRIORITY_CRITICAL);
			}

			//Write media in loop while allowed
			while (vMediaFoundationInstance.vMediaWriteLoopAllowed)
			{
				try
				{
					//Get media frame start time
					LARGE_INTEGER qpcTimeCurrent;
					QueryPerformanceCounter(&qpcTimeCurrent);
					ULONGLONG mediaTimeStart = qpcTimeCurrent.QuadPart - vMediaFoundationInstance.vMediaTimeStartLoop;

					//Get audio bytes
					std::vector<BYTE> audioBytes = GetAudioBytes();

					//Check audio bytes
					if (!audioBytes.empty())
					{
						//Write media bytes to sink
						WriteMediaDataBytes(audioBytes, true, false, vMediaFoundationInstance.vOutAudioStreamIndex, mediaTimeStart, mediaTimeDuration);
					}
					else
					{
						//Delay audio capture
						//AVDebugWriteLine("Empty media audio, delaying capture.");
						AVHighResDelay(1);
					}
				}
				catch (...) {}
			}
		}
		catch (...) {}

		//Reset thread variables
		vMediaFoundationInstance.vMediaWriteLoopFinishedAudio = true;
	}
}