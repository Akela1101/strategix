include(cmake/common.cmake)
project(strategix)


add_library(${PROJECT_NAME}
        src/ConfigurationManager.h
        src/CoordStructs.cpp
        src/CoordStructs.h
        src/entity/Enti.cpp
        src/entity/Enti.h
        src/entity/EntiInfo.h
        src/entity/EntiSlot.cpp
        src/entity/EntiSlot.h
        src/feature/Feature.h
        src/feature/FeatureAttack.cpp
        src/feature/FeatureAttack.h
        src/feature/FeatureCollect.cpp
        src/feature/FeatureCollect.h
        src/feature/FeatureHealth.cpp
        src/feature/FeatureHealth.h
        src/feature/FeatureInfo.h
        src/feature/FeatureMove.cpp
        src/feature/FeatureMove.h
        src/Interfaces.h
        src/Kernel.cpp
        src/Kernel.h
        src/map/Map.h
        src/map/MapFull.cpp
        src/map/MapFull.h
        src/map/MapLocal.cpp
        src/map/MapLocal.h
        src/map/Mine.h
        src/map/MapsPath.h
        src/map/MapsPathsFinder.cpp
        src/map/MapsPathsFinder.h
        src/player/Player.cpp
        src/player/Player.h
        src/player/PlayerSlot.h
        src/Resource.h
        src/Resources.h
        src/Strategix_Forward.h
        src/StrategixCommon.h
        src/StrategixSingleton.h
        src/TechTree.cpp
        src/TechTree.h
        src/TechTreesBuilder.h
        src/ConfigurationManager.cpp
        src/KernelSlot.h
        src/player/PlayerSlot.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PUBLIC
        src
        ../../easyloggingpp/src)

target_link_libraries(${PROJECT_NAME} nya)