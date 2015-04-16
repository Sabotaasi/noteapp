# MADE BY HEIKKI HEINONEN AND MIKKO PULLINEN
Noteapp.exe: Main.obj User.obj
	LINK ..\out\mysql-db.lib Main.obj User.obj kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /OUT:..\out\Noteapp.exe
Main.obj: Main.cpp User.h
	CL /I ..\mysql-db /c Main.cpp
User.obj: User.cpp User.h
	CL /I ..\mysql-db /c User.cpp
clean :
	rm ..\out\Noteapp.exe Main.obj User.obj
all: clean Noteapp.exe