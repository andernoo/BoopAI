# Install script for directory: /home/andrew/BoopAI/Box2D/Box2D

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D" TYPE FILE FILES "/home/andrew/BoopAI/Box2D/Box2D/Box2D.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Collision" TYPE FILE FILES
    "/home/andrew/BoopAI/Box2D/Box2D/Collision/b2BroadPhase.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Collision/b2Collision.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Collision/b2Distance.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Collision/b2DynamicTree.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Collision/b2TimeOfImpact.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Collision/Shapes" TYPE FILE FILES
    "/home/andrew/BoopAI/Box2D/Box2D/Collision/Shapes/b2CircleShape.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Collision/Shapes/b2EdgeShape.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Collision/Shapes/b2ChainShape.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Collision/Shapes/b2Shape.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Common" TYPE FILE FILES
    "/home/andrew/BoopAI/Box2D/Box2D/Common/b2BlockAllocator.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Common/b2Draw.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Common/b2GrowableStack.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Common/b2Math.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Common/b2Settings.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Common/b2StackAllocator.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Common/b2Timer.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Dynamics" TYPE FILE FILES
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/b2Body.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/b2ContactManager.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/b2Fixture.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/b2Island.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/b2TimeStep.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/b2World.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/b2WorldCallbacks.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Dynamics/Contacts" TYPE FILE FILES
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Contacts/b2CircleContact.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Contacts/b2Contact.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Contacts/b2ContactSolver.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Contacts/b2PolygonContact.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Dynamics/Joints" TYPE FILE FILES
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Joints/b2GearJoint.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Joints/b2Joint.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Joints/b2MotorJoint.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Joints/b2MouseJoint.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Joints/b2PrismaticJoint.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Joints/b2PulleyJoint.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Joints/b2RevoluteJoint.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Joints/b2RopeJoint.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Joints/b2WeldJoint.h"
    "/home/andrew/BoopAI/Box2D/Box2D/Dynamics/Joints/b2WheelJoint.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Rope" TYPE FILE FILES "/home/andrew/BoopAI/Box2D/Box2D/Rope/b2Rope.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBox2D.so.2.3.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBox2D.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/andrew/BoopAI/Box2D/Build/Box2D/libBox2D.so.2.3.2"
    "/home/andrew/BoopAI/Box2D/Build/Box2D/libBox2D.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBox2D.so.2.3.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBox2D.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/andrew/BoopAI/Box2D/Build/Box2D/libBox2D.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/Box2D/Box2D-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/Box2D/Box2D-targets.cmake"
         "/home/andrew/BoopAI/Box2D/Build/Box2D/CMakeFiles/Export/lib/Box2D/Box2D-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/Box2D/Box2D-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/Box2D/Box2D-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Box2D" TYPE FILE FILES "/home/andrew/BoopAI/Box2D/Build/Box2D/CMakeFiles/Export/lib/Box2D/Box2D-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Box2D" TYPE FILE FILES "/home/andrew/BoopAI/Box2D/Build/Box2D/CMakeFiles/Export/lib/Box2D/Box2D-targets-release.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Box2D" TYPE FILE FILES
    "/home/andrew/BoopAI/Box2D/Build/Box2D/Box2DConfig.cmake"
    "/home/andrew/BoopAI/Box2D/Box2D/UseBox2D.cmake"
    )
endif()

