/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2017 Aurora Framework, All rights reserved.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU General Public License version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3 requirements will be
** met: https://www.gnu.org/licenses/gpl-3.0.html.
****************************************************************************/

#include <AuroraFW/Aurora.h>

#include <exception>

using namespace AuroraFW;
using namespace AudioManager;

Application *app;

afwslot appMainFunction()
{
	try {
		// Initializes AudioBackend
		AuroraFW::Debug::Log("Getting access to the AudioBackend");
		AudioBackend audioBackend = AudioBackend::getInstance();
		AuroraFW::Debug::Log("AudioBackend initialized.");

		// Prints all available devices
		const AudioDevice *audioDevices = audioBackend.getAllDevices();
		CLI::Log(CLI::Notice, "Printing all available audio devices...");
		for(int i = 0; i < audioBackend.getNumDevices(); i++) {
			CLI::Log(CLI::Information, i, " - ", audioDevices[i].getName(),
			audioDevices[i].isDefaultOutputDevice() ? " [Default Output Device]" : "",
			audioDevices[i].isDefaultInputDevice() ? " [Default Input Device]" : "");
		}

		// Prints all available output devices
		const AudioDevice *audioOutputDevices = audioBackend.getOutputDevices();
		CLI::Log(CLI::Notice, "Printing all available output audio devices...");
		for(int i = 0; i < audioBackend.getNumOutputDevices(); i++) {
			CLI::Log(CLI::Information, i, " - ", audioOutputDevices[i].getName(),
			audioOutputDevices[i].isDefaultOutputDevice() ? " [Default Output Device]" : "");
		}

		// Prints all available input devices
		const AudioDevice *audioInputDevices = audioBackend.getInputDevices();
		CLI::Log(CLI::Notice, "Printing all available input audio devices...");
		for(int i = 0; i < audioBackend.getNumInputDevices(); i++) {
			CLI::Log(CLI::Information, i, " - ", audioInputDevices[i].getName(),
			audioInputDevices[i].isDefaultInputDevice() ? " [Default Input Device]" : "");
		}

		AudioSource audioSource(AudioStream("Testing"), 0, 5, 11);
		AuroraFW::Debug::Log("Size of AudioSource: ", sizeof(audioSource));

		delete[] audioDevices;
		delete[] audioInputDevices;
		delete[] audioOutputDevices;
	} catch(AudioDeviceNotFoundException& e) {
		CLI::Log(CLI::Warning, e.what());
	}
}

int main(int argc, char *argv[])
{
	app = new Application(appMainFunction, argc, argv);

	delete app;

	return EXIT_SUCCESS;
}