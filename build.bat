MD x86
cd x86
cmake .. -G "Visual Studio 14 2015"
cmake --build . --config Debug
cd ..
::MD x64
::cd x64
::cmake .. -G "Visual Studio 14 2015 Win64"
::cmake --build . --config Debug
::cd ..
pause