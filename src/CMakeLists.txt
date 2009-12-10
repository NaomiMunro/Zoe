      project(zoe)

      find_package(KDE4 REQUIRED)
      include_directories(${KDE4_INCLUDES})

      set(zoe_SRCS
		  mainwindow.cpp
		  paintwidget.cpp
		  icell.cpp
		  livingarea.cpp
		  environment.cpp
		  photoautotroph.cpp
		  gene.cpp
		  )

      kde4_add_executable(zoe ${zoe_SRCS})

      target_link_libraries(zoe ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} )

      install(TARGETS zoe DESTINATION /home/kde-devel/coding/bin)
      
	  install(FILES zoeui.rc DESTINATION ${DATA_INSTALL_DIR}/zoe)