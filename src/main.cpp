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

		// Default output device.
		AudioDevice *defaultDevice;

		// Prints all available devices
		const AudioDevice *audioDevices = audioBackend.getAllDevices();
		CLI::Log(CLI::Notice, "Printing all available audio devices...");
		for(int i = 0; i < audioBackend.getNumDevices(); i++) {
			CLI::Log(CLI::Information, i + 1, " - ", audioDevices[i].getName(),
			audioDevices[i].isDefaultOutputDevice() ? " [Default Output Device]" : "",
			audioDevices[i].isDefaultInputDevice() ? " [Default Input Device]" : "");
		}

		// Prints all available output devices
		const AudioDevice *audioOutputDevices = audioBackend.getOutputDevices();
		CLI::Log(CLI::Notice, "Printing all available output audio devices...");
		for(int i = 0; i < audioBackend.getNumOutputDevices(); i++) {
			CLI::Log(CLI::Information, i + 1, " - ", audioOutputDevices[i].getName(),
			audioOutputDevices[i].isDefaultOutputDevice() ? " [Default Output Device]" : "");
		}

		// Prints all available input devices
		const AudioDevice *audioInputDevices = audioBackend.getInputDevices();
		CLI::Log(CLI::Notice, "Printing all available input audio devices...");
		for(int i = 0; i < audioBackend.getNumInputDevices(); i++) {
			CLI::Log(CLI::Information, i + 1, " - ", audioInputDevices[i].getName(),
			audioInputDevices[i].isDefaultInputDevice() ? " [Default Input Device]" : "");
		}

		// Prints information about the default input/output device
		defaultDevice = new AudioDevice();
		CLI::Log(CLI::Notice, "Printing info for default output device. [", defaultDevice->getName(), "]");
		CLI::Log(CLI::Notice, "Name: ", defaultDevice->getName());
		CLI::Log(CLI::Notice, "Maximum input channels: ", defaultDevice->getMaxInputChannels());
		CLI::Log(CLI::Notice, "Maximum output channels: ", defaultDevice->getMaxOutputChannels());
		CLI::Log(CLI::Notice, "Default low input latency: ", defaultDevice->getDefaultLowInputLatency());
		CLI::Log(CLI::Notice, "Default low output latency: ", defaultDevice->getDefaultLowOutputLatency());
		CLI::Log(CLI::Notice, "Default high input latency: ", defaultDevice->getDefaultHighInputLatency());
		CLI::Log(CLI::Notice, "Default high input latency: ", defaultDevice->getDefaultHighOutputLatency());
		CLI::Log(CLI::Notice, "Default sample rate: ", defaultDevice->getDefaultSampleRate());

		delete defaultDevice;

		// Gets ready to output audio
		AudioStream debugSound("example.ogg");
		CLI::Log(CLI::Notice, "Playing now a example sound file for 15 seconds...");
		debugSound.startStream();

		// Waits until the song is over
		while(debugSound.isStreamPlaying()) {}

		debugSound.stopStream();
		CLI::Log(CLI::Notice, "Stopped stream.");

		// Cleans declared pointers
		delete[] audioDevices;
		delete[] audioInputDevices;
		delete[] audioOutputDevices;

	} catch(AudioFileNotFound& e) {
		CLI::Log(CLI::Warning, e.what());
	}
}

int main(int argc, char *argv[])
{
	app = new Application(appMainFunction, argc, argv);

	delete app;

	return EXIT_SUCCESS;
}