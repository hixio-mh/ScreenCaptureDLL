#pragma once
#include "CaptureVariables.h"

namespace
{
	BOOL CaptureResetVariablesTexturesLoop()
	{
		try
		{
			//Textures
			vCaptureInstance.iDxgiResource0.Release();
			vCaptureInstance.iD3D11Texture2D0CpuRead.Release();
			vCaptureInstance.iD3D11Texture2D0Screen.Release();

			//Views
			vDirectXInstance.iD3D11ShaderResourceView0.Release();

			//Release output duplication frame
			if (vDirectXInstance.iDxgiOutputDuplication0 != NULL)
			{
				vDirectXInstance.iDxgiOutputDuplication0->ReleaseFrame();
			}

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	BOOL CaptureResetVariablesTexturesAll()
	{
		try
		{
			//Textures
			vCaptureInstance.iDxgiResource0.Release();
			vCaptureInstance.iD3D11Texture2D0CpuRead.Release();
			vCaptureInstance.iD3D11Texture2D0Screen.Release();
			vCaptureInstance.iD3D11Texture2D0Cursor.Release();
			vCaptureInstance.iD3D11Texture2D0RenderTargetView.Release();

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	BOOL CaptureResetVariablesBitmapImage()
	{
		try
		{
			//Bitmap
			vCaptureInstance.iPropertyBag2.Release();
			vCaptureInstance.iWICImagingFactory.Release();
			vCaptureInstance.iWICStream.Release();
			vCaptureInstance.iWICBitmapEncoder.Release();
			vCaptureInstance.iWICBitmapFrameEncode.Release();
			vCaptureInstance.iWICMetadataQueryWriter.Release();
			vCaptureInstance.iWICFormatConverter.Release();
			vCaptureInstance.iWICBitmap.Release();

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	BOOL CaptureResetVariablesMedia()
	{
		try
		{
			//Media foundation
			vCaptureInstance.vMediaCapturing = false;
			vCaptureInstance.vMediaWriteLoopAllowed = false;
			vCaptureInstance.imfSinkWriter.Release();
			vCaptureInstance.imfDXGIDeviceManager.Release();

			//Audio
			vCaptureInstance.iDevice.Release();
			vCaptureInstance.iAudioDeviceCapture.Release();
			vCaptureInstance.iAudioDeviceRender.Release();
			vCaptureInstance.iAudioClientCapture.Release();
			vCaptureInstance.iAudioClientRender.Release();
			vCaptureInstance.iAudioWaveFormatExCapture.Free();
			vCaptureInstance.iAudioWaveFormatExRender.Free();

			//Bytes
			vCaptureInstance.vScreenBytesCache.clear();

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
			vDirectXInstance.iDxgiOutput0.Release();
			vDirectXInstance.iDxgiOutput6.Release();
			vDirectXInstance.iDxgiOutputDuplication0.Release();
			vDirectXInstance.iD3D11Device0.Release();
			vDirectXInstance.iD3D11Device5.Release();
			vDirectXInstance.iD3D11Multithread.Release();
			vDirectXInstance.iD3D11DeviceContext0.Release();
			vDirectXInstance.iD3D11DeviceContext4.Release();

			//States
			vDirectXInstance.iD3D11SamplerState0.Release();
			vDirectXInstance.iD3D11BlendState0.Release();

			//Views
			vDirectXInstance.iD3D11InputLayout0.Release();
			vDirectXInstance.iD3D11RenderTargetView0.Release();
			vDirectXInstance.iD3D11ShaderResourceView0.Release();

			//Shaders
			vDirectXInstance.iD3D11Buffer0.Release();
			vDirectXInstance.iD3DBlob0VertexShader.Release();
			vDirectXInstance.iD3DBlob0PixelShader.Release();
			vDirectXInstance.iD3D11VertexShader0.Release();
			vDirectXInstance.iD3D11PixelShader0.Release();

			std::cout << "Reset all DirectX variables." << std::endl;
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
			vCaptureInstance.vCaptureFailCount = 0;

			//Textures
			CaptureResetVariablesTexturesAll();

			//Bitmap
			CaptureResetVariablesBitmapImage();

			//Media
			CaptureResetVariablesMedia();

			std::cout << "Reset all Capture variables." << std::endl;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
};