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
		CLI::Log(CLI::Notice, "Printing available audio devices...");
		for(int i = 0; i < audioBackend.getNumDevices(); i++) {
			CLI::Log(CLI::Information, i, " - ", audioDevices[i].getName(),
			Pa_GetDefaultOutputDevice() == i ? " [Default Output Device]" : "",
			Pa_GetDefaultInputDevice() == i ? " [Default Input Device]" : "");
		}

		delete[] audioDevices;
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