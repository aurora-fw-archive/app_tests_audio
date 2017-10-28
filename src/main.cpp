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
		AuroraFW::Debug::Log("Assigning a custom device named \"OpenAL Soft\" to AudioBackend");
		AudioBackend audioBackend = AudioBackend::getInstance();
		audioBackend.setDevice("High Definition Audio Controller Digital Stereo (HDMI)");

		char* outputDevices = audioBackend.getOutputDevices();
		CLI::Log(CLI::Information, "Available output devices:");
		while(outputDevices && *outputDevices !=NULL) {
			CLI::Log(CLI::Information, "- ", outputDevices);

			outputDevices += strlen(outputDevices) + 1;
		}

		char* inputDevices = audioBackend.getInputDevices();
		CLI::Log(CLI::Information, "Available input devices:");
		while(inputDevices && *inputDevices !=NULL) {
			CLI::Log(CLI::Information, "- ", inputDevices);

			inputDevices += strlen(inputDevices) + 1;
		}
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