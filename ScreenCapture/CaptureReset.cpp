#pragma once
#include "CaptureVariables.h"

namespace
{
	BOOL TextureResetVariablesLoop()
	{
		try
		{
			//Textures
			vCaptureInstance.iD3D11Texture2D0CpuRead.Release();
			vCaptureInstance.iD3D11Texture2D0Screen.Release();

			//Views
			vDirectXInstance.iD3D11ShaderResourceView0.Release();

			//std::cout << "Reset loop Texture variables." << std::endl;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	BOOL CaptureResetVariablesAll()
	{
		try
		{
			//Status
			vCaptureInstance.vInstanceInitialized = false;

			//Bytes
			vCaptureInstance.vScreenBytesCache.clear();

			//Textures
			vCaptureInstance.iD3D11Texture2D0CpuRead.Release();
			vCaptureInstance.iD3D11Texture2D0Screen.Release();
			vCaptureInstance.iD3D11Texture2D0RenderTargetView.Release();

			std::cout << "Reset all Capture variables." << std::endl;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	BOOL BitmapImageResetVariablesAll()
	{
		try
		{
			//Bitmap image
			vBitmapImageInstance.iWicPixelFormatGuidSource = GUID_WICPixelFormatDontCare;
			vBitmapImageInstance.iPropertyBag2.Release();
			vBitmapImageInstance.iWICImagingFactory.Release();
			vBitmapImageInstance.iWICStream.Release();
			vBitmapImageInstance.iWICBitmapEncoder.Release();
			vBitmapImageInstance.iWICBitmapFrameEncode.Release();
			vBitmapImageInstance.iWICMetadataQueryWriter.Release();
			vBitmapImageInstance.iWICFormatConverter.Release();
			vBitmapImageInstance.iWICBitmap.Release();

			std::cout << "Reset all Bitmap Image variables." << std::endl;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	BOOL MediaFoundationLoopStop()
	{
		try
		{
			if (vMediaFoundationInstance.vMediaWriteLoopAllowed)
			{
				//Status
				vMediaFoundationInstance.vMediaWriteLoopAllowed = false;

				//Wait for loop to finish
				while (!vMediaFoundationInstance.vMediaWriteLoopFinishedScreen && !vMediaFoundationInstance.vMediaWriteLoopFinishedAudio)
				{
					std::cout << "Waiting for media capture loop to stop..." << std::endl;
					Sleep(100);
				}
			}

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	BOOL MediaFoundationResetVariablesAll()
	{
		try
		{
			//Status
			vMediaFoundationInstance.vMediaCapturing = false;

			//Stop media capture loop
			MediaFoundationLoopStop();

			//Media foundation
			vMediaFoundationInstance.imfSinkWriter.Release();
			vMediaFoundationInstance.imfDXGIDeviceManager.Release();

			//Device audio
			vMediaFoundationInstance.iDevice.Release();
			vMediaFoundationInstance.iAudioDeviceCapture.Release();
			vMediaFoundationInstance.iAudioDeviceRender.Release();
			vMediaFoundationInstance.iAudioClientCapture.Release();
			vMediaFoundationInstance.iAudioClientRender.Release();
			vMediaFoundationInstance.iAudioWaveFormatExCapture.Free();
			vMediaFoundationInstance.iAudioWaveFormatExRender.Free();

			std::cout << "Reset all Media Foundation variables." << std::endl;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	BOOL WgcLoopStop()
	{
		try
		{
			if (vWgcInstance.vGraphicsStatusLoopAllowed)
			{
				//Status
				vWgcInstance.vGraphicsStatusLoopAllowed = false;

				//Wait for loop to finish
				while (!vWgcInstance.vGraphicsStatusLoopFinished)
				{
					std::cout << "Waiting for wgc status loop to stop..." << std::endl;
					Sleep(100);
				}
			}

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	BOOL WgcResetVariablesAll()
	{
		try
		{
			//Status
			vWgcInstance.vInstanceInitialized = false;

			//Stop wgc status loop
			WgcLoopStop();

			//Frame
			vWgcInstance.vFrameSizeCurrent = { 0 ,0 };
			vWgcInstance.vFramePixelFormat = winrt::Windows::Graphics::DirectX::DirectXPixelFormat::Unknown;

			//Direct3D
			if (vWgcInstance.vGraphicsD3D11Device)
			{
				vWgcInstance.vGraphicsD3D11Device.Close();
			}
			vWgcInstance.vGraphicsD3D11Device = NULL;

			//Capture
			vWgcInstance.vGraphicsCaptureItem = NULL;
			if (vWgcInstance.vGraphicsCaptureSession)
			{
				vWgcInstance.vGraphicsCaptureSession.Close();
			}
			vWgcInstance.vGraphicsCaptureSession = NULL;
			if (vWgcInstance.vGraphicsCaptureFramePool)
			{
				vWgcInstance.vGraphicsCaptureFramePool.Close();
			}
			vWgcInstance.vGraphicsCaptureFramePool = NULL;

			std::cout << "Reset all Windows Graphics Capture variables." << std::endl;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	BOOL DirectXResetVariablesAll()
	{
		try
		{
			//Status
			vDirectXInstance.vInstanceInitialized = false;

			//Devices
			vDirectXInstance.iDxgiDevice4.Release();
			vDirectXInstance.iDxgiAdapter4.Release();
			vDirectXInstance.iDxgiFactory7.Release();
			vDirectXInstance.iDxgiOutput6.Release();
			vDirectXInstance.iD3D11Device5.Release();
			vDirectXInstance.iD3D11Multithread0.Release();
			vDirectXInstance.iD3D11DeviceContext4.Release();

			//States
			vDirectXInstance.iD3D11SamplerState0.Release();

			//Views
			vDirectXInstance.iD3D11InputLayout0.Release();
			vDirectXInstance.iD3D11RenderTargetView0.Release();
			vDirectXInstance.iD3D11ShaderResourceView0.Release();

			//Shaders
			vDirectXInstance.iD3D11BufferVertex0.Release();
			vDirectXInstance.iD3D11BufferPixel0.Release();
			vDirectXInstance.iD3DBlobShaderVertex0.Release();
			vDirectXInstance.iD3DBlobShaderPixel0.Release();
			vDirectXInstance.iD3D11ShaderVertex0.Release();
			vDirectXInstance.iD3D11ShaderPixel0.Release();

			std::cout << "Reset all DirectX variables." << std::endl;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	BOOL ResetVariablesAll()
	{
		try
		{
			//Capture
			CaptureResetVariablesAll();

			//Windows Graphics Capture
			WgcResetVariablesAll();

			//DirectX
			DirectXResetVariablesAll();

			//Media foundation
			MediaFoundationResetVariablesAll();

			//Bitmap image
			BitmapImageResetVariablesAll();

			return true;
		}
		catch (...)
		{
			return false;
		}
	}
};