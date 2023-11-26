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
    aooserver -b|--blocklist filename   File containing IP addresses to block

You can specify a different port than the default that the server uses (this
is for both TCP and UDP). You can specify if timestamped log files should be
created in a particular directory, otherwise logging will only go to the standard
output (which it always does). The blocklist lets you specify a file containing IP addresses
that the server should block from being allowed to be used. If a line has an IP address
followed by a comma and the word public (`1.2.3.4,public` for example), then it will allow 
the IP to be used for private groups, but not present any of the public groups to that user.


# SOURCE NOTES

The deps/aoo library dependency is a git subrepo (https://github.com/ingydotnet/git-subrepo), 
so all dependencies are alread included in this repository. 

JUCE is used here mostly as a hedge against future development, when
this server might have some additional audio processing capabilities. All
the JUCE source code necessary to build it is included in JuceLibraryCode,
as installed by ProJucer when using the aooserver.jucer as source. If you
want to contribute to further development or build for other platforms, you'll need to have 
JUCE 7 installed elsewhere.
