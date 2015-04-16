# MADE BY HEIKKI HEINONEN AND MIKKO PULLINEN
mysql-db.dll: mysqlFunctions.obj dllmain.obj stdafx.obj
	LINK /DLL lib\libmysql.lib lib\mysqlclient.lib mysqlFunctions.obj dllmain.obj stdafx.obj /OUT:..\out\mysql-db.dll
mysqlFunctions.obj: mysqlFunctions.cpp mysqlFunctions.h stdafx.h 
	CL /I include /I lib /c mysqlFunctions.cpp /link libmysql mysqlclient  
dllmain.obj: dllmain.cpp stdafx.h
	CL /c dllmain.cpp
stdafx.obj: stdafx.cpp stdafx.h
	CL /c stdafx.cpp
clean :
	rm mysqlFunctions.obj dllmain.obj stdafx.obj ..\out\mysql-db.dll
all: clean mysql-db.dll