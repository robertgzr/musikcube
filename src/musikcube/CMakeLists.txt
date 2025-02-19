set (CUBE_SRCS
    ./Main.cpp
    ./stdafx.cpp
    ./app/layout/BrowseLayout.cpp
    ./app/layout/CategorySearchLayout.cpp
    ./app/layout/ConsoleLayout.cpp
    ./app/layout/DirectoryLayout.cpp
    ./app/layout/HotkeysLayout.cpp
    ./app/layout/LibraryLayout.cpp
    ./app/layout/LibraryNotConnectedLayout.cpp
    ./app/layout/LocalLibrarySettingsLayout.cpp
    ./app/layout/LyricsLayout.cpp
    ./app/layout/MainLayout.cpp
    ./app/layout/NowPlayingLayout.cpp
    ./app/layout/RemoteLibrarySettingsLayout.cpp
    ./app/layout/SettingsLayout.cpp
    ./app/layout/TrackSearchLayout.cpp
    ./app/model/DirectoryAdapter.cpp
    ./app/model/HotkeysAdapter.cpp
    ./app/overlay/BrowseOverlays.cpp
    ./app/overlay/ColorThemeOverlay.cpp
    ./app/overlay/EqualizerOverlay.cpp
    ./app/overlay/LastFmOverlay.cpp
    ./app/overlay/PlaybackOverlays.cpp
    ./app/overlay/PlayQueueOverlays.cpp
    ./app/overlay/PluginOverlay.cpp
    ./app/overlay/PreampOverlay.cpp
    ./app/overlay/ReassignHotkeyOverlay.cpp
    ./app/overlay/ServerOverlay.cpp
    ./app/overlay/SettingsOverlays.cpp
    ./app/overlay/TrackOverlays.cpp
    ./app/overlay/VisualizerOverlay.cpp
    ./app/util/ConsoleLogger.cpp
    ./app/util/GlobalHotkeys.cpp
    ./app/util/Hotkeys.cpp
    ./app/util/MagicConstants.cpp
    ./app/util/PreferenceKeys.cpp
    ./app/util/Playback.cpp
    ./app/util/Rating.cpp
    ./app/util/TrackRowRenderers.cpp
    ./app/util/UpdateCheck.cpp
    ./app/window/CategoryListView.cpp
    ./app/window/TrackListView.cpp
    ./app/window/TransportWindow.cpp
    ./cursespp/App.cpp
    ./cursespp/AppLayout.cpp
    ./cursespp/Checkbox.cpp
    ./cursespp/Colors.cpp
    ./cursespp/DialogOverlay.cpp
    ./cursespp/InputOverlay.cpp
    ./cursespp/IMouseHandler.cpp
    ./cursespp/LayoutBase.cpp
    ./cursespp/ListOverlay.cpp
    ./cursespp/ListWindow.cpp
    ./cursespp/MultiLineEntry.cpp
    ./cursespp/OverlayStack.cpp
    ./cursespp/SchemaOverlay.cpp
    ./cursespp/Screen.cpp
    ./cursespp/ScrollableWindow.cpp
    ./cursespp/ScrollAdapterBase.cpp
    ./cursespp/Scrollbar.cpp
    ./cursespp/ShortcutsWindow.cpp
    ./cursespp/SimpleScrollAdapter.cpp
    ./cursespp/SingleLineEntry.cpp
    ./cursespp/Text.cpp
    ./cursespp/TextInput.cpp
    ./cursespp/TextLabel.cpp
    ./cursespp/ToastOverlay.cpp
    ./cursespp/Window.cpp
)

set(musikcube_INSTALL_DIR ${HOMEBREW_PREFIX})
if (NOT DEFINED musikcube_INSTALL_DIR)
    set(musikcube_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
endif()

configure_file("musikcube.in" "musikcube" @ONLY)

add_executable(musikcube ${CUBE_SRCS})
add_definitions(-DNCURSES_WIDECHAR)

set_target_properties(musikcube PROPERTIES LINK_FLAGS "-Wl,-rpath,./")

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    if (${LINK_STATICALLY} MATCHES "true")
        find_library(
            NCURSESWLIB
            NAMES libncursesw.a ncursesw
            PATHS "/usr/local/opt/ncurses/lib/")

        find_library(
            PANELWLIB
            NAMES libpanelw.a panelw
            PATHS "/usr/local/opt/ncurses/lib/")

        message(STATUS "[musikcube] using libncursesw at " ${NCURSESWLIB})
        message(STATUS "[musikcube] using libpanelw at " ${PANELWLIB})

        target_link_libraries(musikcube ${musikcube_LINK_LIBS} ${NCURSESWLIB} ${PANELWLIB} musikcore)
    else()
        target_link_libraries(musikcube ${musikcube_LINK_LIBS} ncursesw panelw musikcore)
    endif()
else()
    find_package(PkgConfig)
    if (${NCURSES_DISABLE_LIB_SUFFIXES} MATCHES "true")
      # pkg_check_modules fails on some systems, including OpenBSD.
      # pkg_check_modules(NCURSES REQUIRED ncurses panel)
      ensure_library_exists(ncurses)
      ensure_library_exists(panel)
      set(NCURSES_LIBRARIES ncurses panel)
      message(STATUS "[ncurses] using library names without 'w' prefix")
    else()
      # pkg_check_modules fails on some systems, including OpenBSD.
      # pkg_check_modules(NCURSES REQUIRED ncursesw panelw)
      ensure_library_exists(ncursesw)
      ensure_library_exists(panelw)
      set(NCURSES_LIBRARIES ncursesw panelw)
      message(STATUS "[ncurses] using library names with 'w' prefix")
    endif()
    target_link_libraries(musikcube ${musikcube_LINK_LIBS} ${NCURSES_LIBRARIES} musikcore)
endif()

if (ENABLE_PCH MATCHES "true")
    message(STATUS "[musikcube] enabling precompiled headers")
    include(./pch.cmake)
endif()
