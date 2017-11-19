include(cmake/common.cmake)
project(strategix)


add_library(${PROJECT_NAME}
        src/common/ConfigurationManager.h
        src/common/CoordStructs.cpp
        src/common/CoordStructs.h
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
        src/feature/Interfaces.h
        src/Kernel.cpp
        src/Kernel.h
        src/map/MapManager.cpp
        src/map/MapManager.h
        src/map/Map.cpp
        src/map/Map.h
        src/map/Mine.cpp
        src/map/Mine.h
        src/map/MapsPath.h
        src/map/MapsPathsFinder.cpp
        src/map/MapsPathsFinder.h
        src/player/Player.cpp
        src/player/Player.h
        src/player/PlayerSlot.h
        src/common/Resource.h
        src/common/Resources.h
        src/common/Strategix_Forward.h
        src/common/StrategixCommon.h
        src/common/TechTree.cpp
        src/common/TechTree.h
        src/common/ConfigurationManager.cpp
        src/KernelSlot.h
        src/player/PlayerSlot.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PUBLIC
        src
        ../../easyloggingpp/src)

target_link_libraries(${PROJECT_NAME} nya)