# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

# build with "V=1" for verbose builds
ifeq ($(V), 1)
V_AT =
else
V_AT = @
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef PKG_CONFIG
  PKG_CONFIG=pkg-config
endif

ifndef STRIP
  STRIP=strip
endif

ifndef AR
  AR=ar
endif

ifndef CONFIG
  CONFIG=Debug
endif

JUCE_ARCH_LABEL := $(shell uname -m)

ifeq ($(CONFIG),Debug)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Debug
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := 
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DDEBUG=1" "-D_DEBUG=1" "-DLOGLEVEL=3" "-DUSE_CODEC_OPUS=0" "-DJUCER_LINUX_MAKE_6D53C8B4=1" "-DJUCE_APP_VERSION=1.0.0" "-DJUCE_APP_VERSION_HEX=0x10000" $(shell $(PKG_CONFIG) --cflags libcurl) -pthread -I../../JuceLibraryCode -I../../JuceLibraryCode/modules -I../../deps/aoo/lib -I../../deps/aoo/deps $(CPPFLAGS)
  JUCE_CPPFLAGS_CONSOLEAPP :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_TARGET_CONSOLEAPP := aooserver

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++17 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell $(PKG_CONFIG) --libs libcurl) -fvisibility=hidden -lrt -ldl -lpthread $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Release)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := 
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DNDEBUG=1" "-DUSE_CODEC_OPUS=0" "-DJUCER_LINUX_MAKE_6D53C8B4=1" "-DJUCE_APP_VERSION=1.0.0" "-DJUCE_APP_VERSION_HEX=0x10000" $(shell $(PKG_CONFIG) --cflags libcurl) -pthread -I../../JuceLibraryCode -I../../JuceLibraryCode/modules -I../../deps/aoo/lib -I../../deps/aoo/deps $(CPPFLAGS)
  JUCE_CPPFLAGS_CONSOLEAPP :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_TARGET_CONSOLEAPP := aooserver

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -O3 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++17 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell $(PKG_CONFIG) --libs libcurl) -fvisibility=hidden -lrt -ldl -lpthread $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS_CONSOLEAPP := \
  $(JUCE_OBJDIR)/client_305e502e.o \
  $(JUCE_OBJDIR)/codec_pcm_9c9d1978.o \
  $(JUCE_OBJDIR)/common_3542764e.o \
  $(JUCE_OBJDIR)/net_utils_b38d78d6.o \
  $(JUCE_OBJDIR)/server_81d30fa6.o \
  $(JUCE_OBJDIR)/sink_75e48a76.o \
  $(JUCE_OBJDIR)/source_ac691c7e.o \
  $(JUCE_OBJDIR)/sync_c3d7827e.o \
  $(JUCE_OBJDIR)/time_dbbc51b0.o \
  $(JUCE_OBJDIR)/md5_22b917f0.o \
  $(JUCE_OBJDIR)/OscOutboundPacketStream_6ea031b3.o \
  $(JUCE_OBJDIR)/OscPrintReceivedElements_6e7e89f4.o \
  $(JUCE_OBJDIR)/OscReceivedElements_694ce973.o \
  $(JUCE_OBJDIR)/OscTypes_bb5e81a8.o \
  $(JUCE_OBJDIR)/Main_90ebc5c2.o \
  $(JUCE_OBJDIR)/include_juce_audio_basics_8a4e984a.o \
  $(JUCE_OBJDIR)/include_juce_audio_formats_15f82001.o \
  $(JUCE_OBJDIR)/include_juce_core_f26d17db.o \
  $(JUCE_OBJDIR)/include_juce_cryptography_8cb807a8.o \
  $(JUCE_OBJDIR)/include_juce_data_structures_7471b1e3.o \
  $(JUCE_OBJDIR)/include_juce_events_fd7d695.o \

.PHONY: clean all strip

all : $(JUCE_OUTDIR)/$(JUCE_TARGET_CONSOLEAPP)

$(JUCE_OUTDIR)/$(JUCE_TARGET_CONSOLEAPP) : $(OBJECTS_CONSOLEAPP) $(JUCE_OBJDIR)/execinfo.cmd $(RESOURCES)
	@command -v $(PKG_CONFIG) >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@$(PKG_CONFIG) --print-errors libcurl
	@echo Linking "aooserver - ConsoleApp"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_CONSOLEAPP) $(OBJECTS_CONSOLEAPP) $(JUCE_LDFLAGS) $(shell cat $(JUCE_OBJDIR)/execinfo.cmd) $(RESOURCES) $(TARGET_ARCH)

$(JUCE_OBJDIR)/client_305e502e.o: ../../deps/aoo/lib/src/client.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling client.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/codec_pcm_9c9d1978.o: ../../deps/aoo/lib/src/codec_pcm.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling codec_pcm.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/common_3542764e.o: ../../deps/aoo/lib/src/common.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling common.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/net_utils_b38d78d6.o: ../../deps/aoo/lib/src/net_utils.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling net_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/server_81d30fa6.o: ../../deps/aoo/lib/src/server.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling server.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sink_75e48a76.o: ../../deps/aoo/lib/src/sink.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling sink.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/source_ac691c7e.o: ../../deps/aoo/lib/src/source.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling source.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sync_c3d7827e.o: ../../deps/aoo/lib/src/sync.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling sync.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/time_dbbc51b0.o: ../../deps/aoo/lib/src/time.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling time.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/md5_22b917f0.o: ../../deps/aoo/deps/md5/md5.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling md5.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/OscOutboundPacketStream_6ea031b3.o: ../../deps/aoo/deps/oscpack/osc/OscOutboundPacketStream.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling OscOutboundPacketStream.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/OscPrintReceivedElements_6e7e89f4.o: ../../deps/aoo/deps/oscpack/osc/OscPrintReceivedElements.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling OscPrintReceivedElements.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/OscReceivedElements_694ce973.o: ../../deps/aoo/deps/oscpack/osc/OscReceivedElements.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling OscReceivedElements.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/OscTypes_bb5e81a8.o: ../../deps/aoo/deps/oscpack/osc/OscTypes.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling OscTypes.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling Main.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_basics_8a4e984a.o: ../../JuceLibraryCode/include_juce_audio_basics.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_formats_15f82001.o: ../../JuceLibraryCode/include_juce_audio_formats.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_formats.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_core_f26d17db.o: ../../JuceLibraryCode/include_juce_core.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_cryptography_8cb807a8.o: ../../JuceLibraryCode/include_juce_cryptography.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_cryptography.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_data_structures_7471b1e3.o: ../../JuceLibraryCode/include_juce_data_structures.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_data_structures.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_events_fd7d695.o: ../../JuceLibraryCode/include_juce_events.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_events.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/execinfo.cmd:
	-$(V_AT)mkdir -p $(@D)
	-@if [ -z "$(V_AT)" ]; then echo "Checking if we need to link libexecinfo"; fi
	$(V_AT)printf "int main() { return 0; }" | $(CXX) -x c++ -o $(@D)/execinfo.x -lexecinfo - >/dev/null 2>&1 && printf -- "-lexecinfo" > "$@" || touch "$@"

$(JUCE_OBJDIR)/cxxfs.cmd:
	-$(V_AT)mkdir -p $(@D)
	-@if [ -z "$(V_AT)" ]; then echo "Checking if we need to link stdc++fs"; fi
	$(V_AT)printf "int main() { return 0; }" | $(CXX) -x c++ -o $(@D)/cxxfs.x -lstdc++fs - >/dev/null 2>&1 && printf -- "-lstdc++fs" > "$@" || touch "$@"

clean:
	@echo Cleaning aooserver
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping aooserver
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

-include $(OBJECTS_CONSOLEAPP:%.o=%.d)
