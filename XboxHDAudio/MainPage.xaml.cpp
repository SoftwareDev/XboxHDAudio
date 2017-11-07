//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <ppltasks.h>

using namespace XboxHDAudio;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Media::Devices;
using namespace Windows::Devices::Enumeration;
using namespace concurrency;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();

	auto properties = ref new Vector<String^>();
	properties->Append(L"{1DA5D803-D492-4EDD-8C23-E0C0FFEE7F0E} 0"); // FF
	properties->Append(L"xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx} 2"); // CC - intentionaly not functional

	String ^id = MediaDevice::GetDefaultAudioRenderId(AudioDeviceRole::Default);

	epid->Text = id;

	create_task(DeviceInformation::CreateFromIdAsync(MediaDevice::GetDefaultAudioRenderId(AudioDeviceRole::Default), properties)).then(
		[this](DeviceInformation^ devinfo)
	{
		auto val = safe_cast<IPropertyValue^>(devinfo->Properties->Lookup(L"{1DA5D803-D492-4EDD-8C23-E0C0FFEE7F0E} 0"));
		if (val)
		{
			ff->Text = val->GetInt32().ToString();
		}
		else
		{
			ff->Text = L"No idea";
		}

		val = safe_cast<IPropertyValue^>(devinfo->Properties->Lookup(L"{353aac96-9fac-4870-856d-163189aa34a2} 2"));
		if (val)
		{
			cc->Text = val->GetInt32().ToString();
		}
		else
		{
			cc->Text = L"No idea";
		}

	});

}
