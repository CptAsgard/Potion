@ECHO OFF

rmdir %2Assets
mklink /D %2Assets %1Assets