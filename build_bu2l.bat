@echo off
rem path=C:\Programs\cygwin\bin;%PATH%
::path=%PATH%;C:\Programs\cegcc\bin
::set PATH=%PATH%;C:\DEVENV\CYGWIN\old\bin
::set PATH=C:\DEVENV\CYGWIN\old\bin;%windir%;%windir%\system32
@set PATH=C:\KBApps\DevEnv\Cygwin\V2_3_1\bin;%PATH%
::@set PATH=C:\KBApps\DevEnv\Cygwin\V1_7_17\bin;%PATH%
rem set TMPDIR=c:\tmp
set WORK_ROOT=%CD%
set CYGWIN=nodosfilewarning

rem C:
rem chdir C:\Programs\cygwin\bin

::echo WORK_ROOT=%WORK_ROOT%
::echo PATH=%PATH%
::bash --login -i -c "make -C $WORK_ROOT %1 %2 %3 %4"
bash -c "make -C $WORK_ROOT %1 %2 %3 %4"
