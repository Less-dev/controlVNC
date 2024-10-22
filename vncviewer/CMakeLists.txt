if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  message(FATAL_ERROR "cmake must be invoked with the top level directory")
endif()

# Cambiamos el nombre del ejecutable de 'vncviewer' a 'controlvnc'
add_executable(controlvnc
  fltk/Fl_Monitor_Arrangement.cxx
  fltk/Fl_Navigation.cxx
  fltk/theme.cxx
  menukey.cxx
  BaseTouchHandler.cxx
  CConn.cxx
  DesktopWindow.cxx
  EmulateMB.cxx
  UserDialog.cxx
  ServerDialog.cxx
  Surface.cxx
  OptionsDialog.cxx
  PlatformPixelBuffer.cxx
  Viewport.cxx
  parameters.cxx
  keysym2ucs.c
  touch.cxx
  MonitorIndicesParameter.cxx
  vncviewer.cxx
  SideBar.cpp
)

# Ajustar las propiedades según el nuevo nombre del binario
if(WIN32 AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
  set_target_properties(controlvnc PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if(WIN32)
  target_include_directories(controlvnc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  configure_file(vncviewer.rc.in vncviewer.rc)
  target_sources(controlvnc PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/vncviewer.rc)
endif()

if(WIN32)
  target_sources(controlvnc PRIVATE Win32TouchHandler.cxx win32.c)
elseif(APPLE)
  target_sources(controlvnc PRIVATE cocoa.mm osx_to_qnum.c)
else()
  target_sources(controlvnc PRIVATE GestureHandler.cxx XInputTouchHandler.cxx xkb_to_qnum.c)
endif()

if(WIN32)
  target_sources(controlvnc PRIVATE Surface_Win32.cxx)
elseif(APPLE)
  target_sources(controlvnc PRIVATE Surface_OSX.cxx)
else()
  target_sources(controlvnc PRIVATE Surface_X11.cxx)
endif()

target_include_directories(controlvnc SYSTEM PUBLIC ${FLTK_INCLUDE_DIR})
target_include_directories(controlvnc SYSTEM PUBLIC ${GETTEXT_INCLUDE_DIR})
target_include_directories(controlvnc PUBLIC ${CMAKE_SOURCE_DIR}/common)
target_link_libraries(controlvnc rfb network rdr os ${FLTK_LIBRARIES} ${GETTEXT_LIBRARIES})

if(WIN32)
  target_link_libraries(controlvnc msimg32)
elseif(APPLE)
  target_link_libraries(controlvnc "-framework Cocoa")
  target_link_libraries(controlvnc "-framework Carbon")
  target_link_libraries(controlvnc "-framework IOKit")
else()
  target_link_libraries(controlvnc ${X11_Xi_LIB})

  if(X11_Xrandr_LIB)
    target_link_libraries(controlvnc ${X11_Xrandr_LIB})
  endif()
endif()

# Ajustar el destino de instalación al nuevo nombre del binario
install(TARGETS controlvnc DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})
if(UNIX)
  install(FILES vncviewer.man DESTINATION ${CMAKE_INSTALL_FULL_MANDIR}/man1 RENAME controlvnc.1)

  file(STRINGS ${CMAKE_SOURCE_DIR}/po/LINGUAS LINGUAS)
  set(po_FILES "")
  foreach(lang ${LINGUAS})
    list(APPEND po_FILES "${CMAKE_SOURCE_DIR}/po/${lang}.po")
  endforeach()

  configure_file(vncviewer.desktop.in.in vncviewer.desktop.in)
  find_program(INTLTOOL_MERGE_EXECUTABLE intltool-merge)
  if("${GETTEXT_VERSION_STRING}" VERSION_GREATER 0.18.99)
    add_custom_command(OUTPUT controlvnc.desktop
      COMMAND ${GETTEXT_MSGFMT_EXECUTABLE}
                --desktop --template vncviewer.desktop.in
                -d ${CMAKE_SOURCE_DIR}/po -o controlvnc.desktop
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/vncviewer.desktop.in
              ${po_FILES}
    )
  elseif(INTLTOOL_MERGE_EXECUTABLE)
    add_custom_command(OUTPUT controlvnc.desktop
      COMMAND sed -e 's/^Name/_Name/'
                -e 's/^GenericName/_GenericName/'
                -e 's/^Comment/_Comment/'
                vncviewer.desktop.in > controlvnc.desktop.intl
      COMMAND ${INTLTOOL_MERGE_EXECUTABLE}
                -d ${CMAKE_SOURCE_DIR}/po
                controlvnc.desktop.intl controlvnc.desktop
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/vncviewer.desktop.in
              ${po_FILES}
    )
  else()
    add_custom_command(OUTPUT controlvnc.desktop
      COMMAND cp vncviewer.desktop.in controlvnc.desktop
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/vncviewer.desktop.in
    )
  endif()
  add_custom_target(desktop ALL DEPENDS controlvnc.desktop)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/controlvnc.desktop DESTINATION ${CMAKE_INSTALL_FULL_DATADIR}/applications)

  if("${GETTEXT_VERSION_STRING}" VERSION_GREATER 0.19.6)
    add_custom_command(OUTPUT org.tigervnc.controlvnc.metainfo.xml
      COMMAND ${GETTEXT_MSGFMT_EXECUTABLE}
                --xml --template ${CMAKE_CURRENT_SOURCE_DIR}/org.tigervnc.vncviewer.metainfo.xml.in
                -d ${CMAKE_SOURCE_DIR}/po -o org.tigervnc.controlvnc.metainfo.xml
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/org.tigervnc.vncviewer.metainfo.xml.in
              ${po_FILES}
    )
  elseif(INTLTOOL_MERGE_EXECUTABLE)
    add_custom_command(OUTPUT org.tigervnc.controlvnc.metainfo.xml
      COMMAND sed -e 's@<name>@<_name>@\;s@</name>@</_name>@'
                  -e 's@<summary>@<_summary>@\;s@</summary>@</_summary>@'
                  -e 's@<caption>@<_caption>@\;s@</caption>@</_caption>@'
                  -e 's@<p>@<_p>@g\;s@</p>@</_p>@g'
                ${CMAKE_CURRENT_SOURCE_DIR}/org.tigervnc.vncviewer.metainfo.xml.in > org.tigervnc.controlvnc.metainfo.xml.intl
      COMMAND ${INTLTOOL_MERGE_EXECUTABLE}
                -x ${CMAKE_SOURCE_DIR}/po
                org.tigervnc.controlvnc.metainfo.xml.intl org.tigervnc.controlvnc.metainfo.xml
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/org.tigervnc.vncviewer.metainfo.xml.in
              ${po_FILES}
    )
  else()
    add_custom_command(OUTPUT org.tigervnc.controlvnc.metainfo.xml
      COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/org.tigervnc.vncviewer.metainfo.xml.in org.tigervnc.controlvnc.metainfo.xml
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/org.tigervnc.vncviewer.metainfo.xml.in
    )
  endif()
  add_custom_target(appstream ALL DEPENDS org.tigervnc.controlvnc.metainfo.xml)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/org.tigervnc.controlvnc.metainfo.xml DESTINATION ${CMAKE_INSTALL_FULL_DATADIR}/metainfo)

  foreach(res 16 22 24 32 48 64 128)
    install(FILES ../media/icons/tigervnc_${res}.png DESTINATION ${CMAKE_INSTALL_FULL_DATADIR}/icons/hicolor/${res}x${res}/apps RENAME controlvnc.png)
  endforeach()
  install(FILES ../media/icons/tigervnc.svg DESTINATION ${CMAKE_INSTALL_FULL_DATADIR}/icons/hicolor/scalable/apps)
endif()
