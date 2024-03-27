######################### Parameters ##########################

param($license = '')

######################### Classes ##########################

class FileConfig {
  [string] $FileName;
  [string] $ReleaseVersion;
  [string] $OS;
  [string] $Compiler;
  [string] $Architecture;
  [string] $Type;
}

######################### Config ###########################

$RELEASE_VERSION = '2024.03'

$CurrentPath = $PSScriptRoot
$CmdPath = "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat" # Configure the path to vcvarsall.bat if needed

$Files = @(
  [FileConfig]@{
    FileName       = "mdName.dll";
    ReleaseVersion = $RELEASE_VERSION;
    OS             = "WINDOWS";
    Compiler       = "DLL";
    Architecture   = "64BIT";
    Type           = "BINARY";
  },
  [FileConfig]@{
    FileName       = "mdNameEnums.h";
    ReleaseVersion = $RELEASE_VERSION;
    OS             = "ANY";
    Compiler       = "C";
    Architecture   = "ANY";
    Type           = "INTERFACE";  
  },
  [FileConfig]@{
    FileName       = "mdName.h";
    ReleaseVersion = $RELEASE_VERSION;
    OS             = "ANY";
    Compiler       = "C";
    Architecture   = "ANY";
    Type           = "INTERFACE";
  },
  [FileConfig]@{
    FileName       = "mdName.lib";
    ReleaseVersion = $RELEASE_VERSION;
    OS             = "WINDOWS";
    Compiler       = "C";
    Architecture   = "64BIT";
    Type           = "INTERFACE";
  },
  [FileConfig]@{
    FileName       = "mdNameJavaWrapper.cpp";
    ReleaseVersion = $RELEASE_VERSION;
    OS             = "ANY";
    Compiler       = "JAVA";
    Architecture   = "ANY";
    Type           = "INTERFACE";
  },
  [FileConfig]@{
    FileName       = "mdName_JavaCode.zip";
    ReleaseVersion = $RELEASE_VERSION;
    OS             = "ANY";
    Compiler       = "ANY";
    Architecture   = "ANY";
    Type           = "DATA";
  }
)

###################### Functions ######################

# This function will download all the files needed to compile the wrapper
function DownloadFiles() {
  Write-Host "MELISSA UPDATER IS DOWNLOADING FILE(s)..."
  $FileProg = 0
  foreach ($File in $Files) {
    Write-Progress -Activity "Downloading FILE(s)" -Status "$([math]::round($FileProg / $Files.Count * 100, 2))% Complete:"  -PercentComplete ($FileProg / $Files.Count * 100)

    .\MelissaUpdater\MelissaUpdater.exe file --filename $File.FileName --release_version $File.ReleaseVersion --license $LICENSE --os $File.OS --compiler $File.Compiler --architecture $File.Architecture --type $File.Type --target_directory $CurrentPath
    
    if (($?) -eq $False) {
        Write-Host "`nCannot run Melissa Updater. Please check your license string!"
        Exit
    }

    # Check for the zip folder and extract from the zip folder if it was downloaded
    if ($File.FileName -eq "mdName_JavaCode.zip") {
      if (!(Test-Path ("$CurrentPath\mdName_JavaCode.zip"))) {
        Write-Host "mdName_JavaCode.zip not found." 
        
        Write-Host "`nAborting program, see above.  Press any button to exit."
        $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
        exit
      }
      else {
        if (!(Test-Path ("$CurrentPath/com"))) {
        Expand-Archive -Path "$CurrentPath\mdName_JavaCode.zip" -DestinationPath $CurrentPath
        }
        else {
          # Remove the com folder before extracting
          Remove-Item -Path "$CurrentPath/com" -Recurse -Force

          Expand-Archive -Path "$CurrentPath\mdName_JavaCode.zip" -DestinationPath $CurrentPath
        }
      }
    }
  }
      
  Remove-Item *.hash
    
  Write-Host "Melissa Updater finished downloading file(s)!"
  $FileProg++
}

# This function will check if the files exist before trying to compile the wrapper
function CheckFiles() {
  Write-Host "`nDouble checking file(s) were downloaded...`n"
  $FileMissing = $false 
  if (!(Test-Path ("mdName.dll"))) {
    Write-Host "mdName.dll not found." 
    $FileMissing = $true
  }
  if (!(Test-Path ("mdNameEnums.h"))) {
    Write-Host "mdNameEnums.h not found." 
    $FileMissing = $true
  }
  if (!(Test-Path ("mdName.h"))) {
    Write-Host "mdName.h not found." 
    $FileMissing = $true
  }
  if (!(Test-Path ("mdName.lib"))) {
    Write-Host "mdName.lib not found." 
    $FileMissing = $true
  }
  if ($FileMissing) {
    Write-Host "`nMissing the above data file(s).  Please check that your license string and directory are correct."
    return $false
  }
  else {
    return $true
  }
}

########################## Main ############################

Write-Host "`n======================= WELCOME TO MELISSA NAME OBJECT JAVA WRAPPER =======================`n"

# Get license (either from parameters or user input)
if ([string]::IsNullOrEmpty($license)) {
  $License = Read-Host "Please enter your license string"
}

# Check for license from Environment Variables
if ([string]::IsNullOrEmpty($License)) {
  $License = $env:MD_LICENSE
}

if ([string]::IsNullOrEmpty($License)) {
  Write-Host "`nLicense String is invalid!"
  Exit
}

# Use MelissaUpdater to download file(s)
DownloadFiles -license $License

# Check if all file(s) have been downloaded. Exit script if missing
$FilesDownloaded = CheckFiles

if (!$FilesDownloaded) {
  Write-Host "`nAborting program, see above.  Press any button to exit."
  $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
  exit
}

Write-Host "All file(s) have been downloaded/updated! "

# Build the wrapper
Write-Host "`n======================================= BUILD WRAPPER =====================================`n"

# Compile DLL
cmd.exe /C """$CmdPath"" x86_x64 && Powershell -File Build.ps1" > $null

# Compile Jar
javac com\melissadata\*.java > $null

jar cvf mdName.jar com\melissadata\*.class > $null

if (Test-Path ("mdNameJavaWrapper.dll")) {
  $filePath = Join-Path -Path (Split-Path -Parent $PSCommandPath) -ChildPath "mdNameJavaWrapper.dll"

  Write-Host "`nmdNameJavaWrapper.dll has been successfully generated at:`n$filePath"
}
else {
  Write-Host "`nError: was not able to create mdNameJavaWrapper.dll"
}

if (Test-Path ("mdName.jar")) {
  $filePath = Join-Path -Path (Split-Path -Parent $PSCommandPath) -ChildPath "mdName.jar"

  Write-Host "`nmdName.jar has been successfully generated at:`n$filePath"
}
else {
  Write-Host "`nError: was not able to create mdName.jar"
}

Write-Host "`n========================= THANK YOU FOR USING MELISSA JAVA WRAPPER ========================`n"

