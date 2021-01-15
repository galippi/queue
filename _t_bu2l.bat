::@set PATH=C:\KBApps\DevEnv\Cygwin\V1_7_9_advanced\bin;%windir%;%windir%\system32
@set PATH=C:\KBApps\DevEnv\Cygwin\V2_3_1\bin;%PATH%
@set path=%CD%\lib;%PATH%
::@cd obj
obj\test1.exe %*
::@cd ..
