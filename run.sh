#!/bin/sh
printf "Started Compiling\n\n"
if [[ $1 = "-d" || $1 = "--debug" ]]; then
g++ -o TanksExecutable *.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
else
g++ -o TanksExecutable *.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
fi

vblank_mode=0 ./TanksExecutable

printf "\nExited With Status: $?\n\n"

if [[ $1 = "-rm" ]]; then
printf "Removing Executable!\n\n"
rm -Rf TanksExecutable
printf "Done!\n\n"
fi