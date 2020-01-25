function(AddQtMultiMediaSupport addonName)

    # execute_process(COMMAND node -p "require('@nodegui/qode').qtHome"
    #     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    #     OUTPUT_VARIABLE QT_HOME_DIR
    # )
    
    if(DEFINED ENV{QT_INSTALL_DIR})
        # Allows to use custom Qt installation via QT_INSTALL_DIR env variable
        message(STATUS "Using Custom QT installation for ${addonName} QT_INSTALL_DIR:$ENV{QT_INSTALL_DIR}")
        set(QT_HOME_DIR "$ENV{QT_INSTALL_DIR}")
    endif()
   
    string(REPLACE "\n" "" QT_HOME_DIR "${QT_HOME_DIR}")
    string(REPLACE "\"" "" QT_HOME_DIR "${QT_HOME_DIR}")
    
    if (APPLE) 
        target_include_directories(${addonName} PRIVATE
            "${QT_HOME_DIR}/include"
            "${QT_HOME_DIR}/lib/QtMultimediaWidgets.framework/Versions/5/Headers"
            "${QT_HOME_DIR}/lib/QtMultimedia.framework/Versions/5/Headers"
        )
        target_link_libraries(${addonName} PRIVATE
            "${QT_HOME_DIR}/lib/QtMultimediaWidgets.framework/Versions/5/QtMultimediaWidgets"
            "${QT_HOME_DIR}/lib/QtMultimedia.framework/Versions/5/QtMultimedia"
        )
    endif()

    if (WIN32)       
        target_include_directories(${addonName} PRIVATE
            "${QT_HOME_DIR}\\include"
            "${QT_HOME_DIR}\\include\\QtMultimediaWidgets"
            "${QT_HOME_DIR}\\include\\QtMultimedia"
        )
        target_link_libraries(${addonName} PRIVATE
            "${QT_HOME_DIR}\\lib\\Qt5MultimediaWidgets.lib"
            "${QT_HOME_DIR}\\lib\\Qt5Multimedia.lib"
        )
    endif()

    if(UNIX AND NOT APPLE)
        set(LINUX TRUE)
    endif()

    if(LINUX)
        target_include_directories(${addonName} PRIVATE
            "${QT_HOME_DIR}/include"
            "${QT_HOME_DIR}/include/QtMultimedia"
            "${QT_HOME_DIR}/include/QtMultimediaWidgets"
        )
        target_link_libraries(${addonName} PRIVATE
            "${QT_HOME_DIR}/lib/QtMultimedia.so"
            "${QT_HOME_DIR}/lib/QtMultimediaWidgets.so"
        )
    endif()    

  
endfunction(AddQtMultiMediaSupport addonName)
