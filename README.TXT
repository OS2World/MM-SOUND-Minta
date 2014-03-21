-- MINTA 2.52 --

 Minta is an MP3 information, tagging and listing PM-utility for OS/2.
It displays information for MP3 audio files, allows adding and removing
of ID3-tags (v1.0/1.1) can output all files with their info to a
listfile, can autorename files, etc. Easy editing of multiple files,
either one by one or all at once.

 Since v2.52, Minta is free software released under the GPL. See the
file COPYING for details.

 As an exception the French translation (francais.rc and francais.ipf)
is copyright by Guillaume Gay.

 As another exception the Hungarian translation (magyar.rc and
magyar.ipf) is copyright by Mesterh zy Attila.

 As another exception the Norwegian translation (norsk.rc and
norsk.ipf) is copyright by Jostein Ullestad and H†vard Mork.

 As another exception the Dutch translation (nederlands.rc and
nederlands.ipf) is copyright by Luc Van Bogaert.

 As another exception the Russian translation (russian.rc) is copyright
by Cyrill Vakhneyev.

 As another exception the Italian translation (italiano.rc and
italiano.ipf) is copyright by Alberto Gabrielli.


-- INSTALLATION --

 If you've unzipped the archive (which seems to be the case, since you
are reading this file ;-) and copied the files to some appropriate
directory, you're already done.

 You may run "install.cmd" to create a WPS-object for Minta.


-- BUILDING --

 Minta was originally developed under OS/2 using emx/gcc 0.9d and
dmake 4.0. I can't say if it would be hard to adjust it for other
compilers or make utilities (though I guess it will need some work to
port it to another OS due to missing seperation of program logic and
system specific issues like e.g. windowing - aka: bad code). If you
want to recompile the program, take a look at the Makefile and adjust
the settings (probably only the "I" macro that tells where you keep
your include files) and then just run dmake.

 Please also note that some files in the "src" directory may belong
to a different "branch" of minta that I once started but not finished
until now :-)

 You probably have to adjust the path to my settings classes in
settings.cpp and settings.h


-- MORE INFO --

 For more information see Minta's online help!

Have fun!
Thorsten Thielen <thth@gmx.net>
(Member of Team OS/2 Region Trier e.V.)
