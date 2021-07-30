This is the standalone connection server for use with SonoBus which uses AOO.

SonoBus can be found on github at https://github.com/essej/sonobus, or its
main website at https://sonobus.net .

# BUILD

To build it on Linux:

(First you will need some dev packages installed, none of them are actually
needed at runtime, but the JUCE6 cmake support requires them for building):

    libX11-dev(el)
    libXrandr-dev(el) 
    libXinerama-dev(el)
    libXcursor-dev(el)
    freetype-dev(el)
  

Then setup the cmake build with the script:

    ./setupcmake.sh

And build it with:

    ./buildcmake.sh

And the resulting binary will be in build/aooserver_artefacts/Release/aooserver,
which you can copy to a system binary location of your choice
(/usr/local/bin, for example) if you want..

## OR USE MAKE

Or, if you just hate cmake and have issues with that.... I've temporarily
added the jucer-generated build for linux back again, and you can just do
this:

    cd Builds/LinuxMakefile
    make

And the resulting executable will be in Builds/LinuxMakefile/build.


# USAGE

`aooserver -h` will give you the usage info, which is very basic:

    aooserver -h|--help                 Prints the list of commands
    aooserver -l|--logdir logdirectory  Enables logging to file
    aooserver -p|--port <server_port>   Specify the server port (default 10998)

You can specify a different port than the default that the server uses (this
is for both TCP and UDP). You can specify if timestamped log files should be
created in a particular directory, otherwise logging will only go to the standard
output (which it always does).


# SOURCE NOTES

The deps/aoo library dependency is a git subrepo (https://github.com/ingydotnet/git-subrepo), 
so all dependencies are alread included in this repository. 

JUCE is used here mostly as a hedge against future development, when
this server might have some additional audio processing capabilities. 

