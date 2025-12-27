set VSVER=[17.0^,18.0^)
set VSTOOLSVER=142

@if     "%ProgramFiles(x86)%" == "" set UniProgramFiles=%ProgramFiles%\
@if not "%ProgramFiles(x86)%" == "" set UniProgramFiles=%ProgramFiles(x86)%\

call :GetVSCommonToolsDir

call "%VSCOMNTOOLS%VC\Auxiliary\Build\vcvarsall.bat" x64

devenv NCadSDK.sln /Build "Debug NCAD|x64"
devenv NCadSDK.sln /Build "Release NCAD|x64"
:ENDNCAD

if "%WIX%"=="" goto ENDWIX
devenv Installer\Windows\SamplesAppInstaller.sln /Build "Debug"
devenv Installer\Windows\SamplesAppInstaller.sln /Build "Release"
:ENDWIX

goto :EOF

:GetVSCommonToolsDir
@set VSCOMNTOOLS=
@set vswhere="%UniProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe"
@setlocal enabledelayedexpansion
@for /f "usebackq delims=*" %%i in (`%vswhere% -version !VSVER! -property installationPath`) do (
  @if exist "%%i\Common7\Tools\vsdevcmd.bat" (
    @endlocal
    @SET VSCOMNTOOLS=%%i\
    @exit /b 0
  )
)
@endlocal
@exit /B 1