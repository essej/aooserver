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

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DDEBUG=1" "-D_DEBUG=1" "-DLOGLEVEL=3" "-DUSE_CODEC_OPUS=0" "-DAOO_HAVE_ATOMIC_INT64" "-DAOO_HAVE_ATOMIC_DOUBLE" "-DAOO_HAVE_PTHREAD_RWLOCK=1" "-DUSE_AOO_NET=1" "-DAOO_NET=1" "-DJUCER_LINUX_MAKE_6D53C8B4=1" "-DJUCE_APP_VERSION=1.0.1" "-DJUCE_APP_VERSION_HEX=0x10001" $(shell $(PKG_CONFIG) --cflags libcurl) -pthread -I../../JuceLibraryCode -I../../JuceLibraryCode/modules -I../../deps/aoo -I../../deps/aoo/include -I../../deps/aoo/deps $(CPPFLAGS)
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

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DNDEBUG=1" "-DUSE_CODEC_OPUS=0" "-DAOO_HAVE_ATOMIC_INT64" "-DAOO_HAVE_ATOMIC_DOUBLE" "-DAOO_HAVE_PTHREAD_RWLOCK=1" "-DUSE_AOO_NET=1" "-DAOO_NET=1" "-DJUCER_LINUX_MAKE_6D53C8B4=1" "-DJUCE_APP_VERSION=1.0.1" "-DJUCE_APP_VERSION_HEX=0x10001" $(shell $(PKG_CONFIG) --cflags libcurl) -pthread -I../../JuceLibraryCode -I../../JuceLibraryCode/modules -I../../deps/aoo -I../../deps/aoo/include -I../../deps/aoo/deps $(CPPFLAGS)
  JUCE_CPPFLAGS_CONSOLEAPP :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_TARGET_CONSOLEAPP := aooserver

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -O3 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++17 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell $(PKG_CONFIG) --libs libcurl) -fvisibility=hidden -lrt -ldl -lpthread $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS_CONSOLEAPP := \
  $(JUCE_OBJDIR)/net_utils_222170b9.o \
  $(JUCE_OBJDIR)/sync_a38ae8bb.o \
  $(JUCE_OBJDIR)/tcp_server_7c885c41.o \
  $(JUCE_OBJDIR)/time_bb6fb7ed.o \
  $(JUCE_OBJDIR)/udp_server_4ce92c61.o \
  $(JUCE_OBJDIR)/pcm_77442024.o \
  $(JUCE_OBJDIR)/client_d3ef9be4.o \
  $(JUCE_OBJDIR)/client_endpoint_a843d35a.o \
  $(JUCE_OBJDIR)/detail_54750d6a.o \
  $(JUCE_OBJDIR)/message_buffer_9600b111.o \
  $(JUCE_OBJDIR)/peer_fb6bdefb.o \
  $(JUCE_OBJDIR)/server_25645b5c.o \
  $(JUCE_OBJDIR)/aoo_a76ba944.o \
  $(JUCE_OBJDIR)/packet_buffer_ae20769a.o \
  $(JUCE_OBJDIR)/resampler_6731b538.o \
  $(JUCE_OBJDIR)/sink_5807bc7a.o \
  $(JUCE_OBJDIR)/source_9287dd82.o \
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

$(JUCE_OBJDIR)/net_utils_222170b9.o: ../../deps/aoo/common/net_utils.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling net_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sync_a38ae8bb.o: ../../deps/aoo/common/sync.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling sync.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/tcp_server_7c885c41.o: ../../deps/aoo/common/tcp_server.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling tcp_server.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/time_bb6fb7ed.o: ../../deps/aoo/common/time.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling time.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/udp_server_4ce92c61.o: ../../deps/aoo/common/udp_server.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling udp_server.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pcm_77442024.o: ../../deps/aoo/aoo/src/codec/pcm.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling pcm.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/client_d3ef9be4.o: ../../deps/aoo/aoo/src/net/client.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling client.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/client_endpoint_a843d35a.o: ../../deps/aoo/aoo/src/net/client_endpoint.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling client_endpoint.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/detail_54750d6a.o: ../../deps/aoo/aoo/src/net/detail.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling detail.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/message_buffer_9600b111.o: ../../deps/aoo/aoo/src/net/message_buffer.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling message_buffer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/peer_fb6bdefb.o: ../../deps/aoo/aoo/src/net/peer.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling peer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/server_25645b5c.o: ../../deps/aoo/aoo/src/net/server.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling server.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/aoo_a76ba944.o: ../../deps/aoo/aoo/src/aoo.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling aoo.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/packet_buffer_ae20769a.o: ../../deps/aoo/aoo/src/packet_buffer.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling packet_buffer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/resampler_6731b538.o: ../../deps/aoo/aoo/src/resampler.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling resampler.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sink_5807bc7a.o: ../../deps/aoo/aoo/src/sink.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling sink.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_CONSOLEAPP) $(JUCE_CFLAGS_CONSOLEAPP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/source_9287dd82.o: ../../deps/aoo/aoo/src/source.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling source.cpp"
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

clean:
	@echo Cleaning aooserver
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping aooserver
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

-include $(OBJECTS_CONSOLEAPP:%.o=%.d)
