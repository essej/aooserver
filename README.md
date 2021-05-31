This is the standalone connection server for use with SonoBus which uses AOO.

SonoBus can be found on github at https://github.com/essej/sonobus, or its
main website at https://sonobus.net .

# BUILD

To build it on Linux:

    cd Builds/LinuxMakefile
    CONFIG=Release make

And the resulting binary will be in Builds/LinuxMakefile/build/aooserver,
which you can copy to a system binary location of your choice
(/usr/local/bin, for example).

# USAGE

`aooserver -h` will give you the usage info, which is very basic:

    aooserver -h|--help                 Prints the list of commands
    aooserver -l|--logdir logdirectory  Enables logging to file
    aooserver -p|--port <server_port>   Specify the server port (default 10998)

You can specify a different port than the default that the server uses (this
is for both TCP and UDP). You can specify if timestamped log files should be
created in a particular directory, otherwise logging will only go to the standard
output (which it always does).

# USAGE WITH DOCKER

A docker image is available to use.

How to use:

    git clone https://github.com/essej/aooserver.git
    cd aooserver/docker
    docker build . -t aooserver
    docker run -d -p 10998:10998/udp -p 10998:10998 --name aooserver aooserver

How to run with flags: `docker run -d -p PORT:PORT/udp -p PORT:PORT --name aooserver aooserver aooserver [flags]`

# SOURCE NOTES

The deps/aoo library dependency is a git subrepo (https://github.com/ingydotnet/git-subrepo), 
so all dependencies are alread included in this repository. 

JUCE is used here mostly as a hedge against future development, when
this server might have some additional audio processing capabilities. All
the JUCE source code necessary to build it is included in JuceLibraryCode,
as installed by ProJucer when using the aooserver.jucer as source. If you
want to contribute to further development, you'll need to have JUCE 5 installed
elsewhere.
