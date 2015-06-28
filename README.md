# lf2crlf
A [Miranda IM] (http://www.miranda-im.org/) plugin to convert line ending in all
MSN history events from line feed to carriage return and line feed.

Tested on Miranda IM 0.8.1 on Windows XP.

# Notice
This plugin is intended to correct the incorrect line ending character from line
feed (LF) to carriage return and line feed (CRLF), which is caused importing WLM
message history using Windows Live Messenger History Import Plugin 
(wlmHistoryImport.dll) version 0.1.2.0 and below.

# Usage
01. Copy lf2crlf.dll to Miranda IM plugin folder.
02. Backup your current profile.
03. Run Miranda IM.
04. In the main menu, select "LF to CRLF..."
05. Click "Yes" to start the conversion.
06. Wait for a few minutes until the conversion is completed. The time of the 
    conversion will depend on the number of events needed to be converted.
07. Click "OK" to close the prompt showing the number of converted messages.
08. Close Miranda IM.
09. Delete lf2crlf.dll from Miranda IM plugin folder.
10. If necessary run the Miranda Database Tool to remove the duplicated MSN 
    history messages in Miranda IM profile.
11. Done. :)

# License
Copyright (C) 2008 - 2009  Very Crazy Dog (VCD)

This plugin is released under [GPL] 
(http://www.gnu.org/licenses/gpl-3.0.en.html).
