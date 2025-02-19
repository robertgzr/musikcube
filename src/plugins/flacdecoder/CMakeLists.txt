set (flacdecoder_SOURCES
  stdafx.cpp
  flacdecoder_plugin.cpp
  FlacDecoderFactory.cpp
  FlacDecoder.cpp
)

ensure_library_exists(FLAC)

add_library(flacdecoder SHARED ${flacdecoder_SOURCES})

# prefer static libraries on mac to make redist easier
if (${LINK_STATICALLY} MATCHES "true")
  ensure_library_exists(libFLAC.a)
  find_library(FLACLIB NAMES libFLAC.a FLAC)
  find_library(OGGLIB NAMES libogg.a ogg)
  target_link_libraries(flacdecoder ${musikcube_LINK_LIBS} ${FLACLIB} ${OGGLIB})
else()
  target_link_libraries(flacdecoder ${musikcube_LINK_LIBS} FLAC ogg)
endif()
