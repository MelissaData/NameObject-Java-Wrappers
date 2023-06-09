# Set Java Includes and Name Object Library Path
$JavaIncludeDirectory1 = "C:\Program Files\Java\jdk-20\include"
$JavaIncludeDirectory2 = "C:\Program Files\Java\jdk-20\include\win32"
$NameLibraryPath = $PSScriptRoot

# Run cl command
& 'cl' -I"$NameLibraryPath" -I"$JavaIncludeDirectory1" -I"$JavaIncludeDirectory2" -Fe'mdNameJavaWrapper.dll' 'mdNameJavaWrapper.cpp' -link -DLL -LIBPATH:"$NameLibraryPath" -DEFAULTLIB:'mdName.lib'

# Remove files
Remove-Item 'mdNameJavaWrapper.exp' -ErrorAction SilentlyContinue
Remove-Item 'mdNameJavaWrapper.obj' -ErrorAction SilentlyContinue
Remove-Item 'mdNameJavaWrapper.lib' -ErrorAction SilentlyContinue

