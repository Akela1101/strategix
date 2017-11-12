project(strategix)

include_directories(../../nya/src src)


add_library(${PROJECT_NAME}
        src/ConfigurationManager.h
        src/CoordStructs.cpp
        src/CoordStructs.h
        src/Enti.cpp
        src/Enti.h
        src/EntiInfo.h
        src/EntiSlot.cpp
        src/EntiSlot.h
        src/Feature.h
        src/FeatureAttack.cpp
        src/FeatureAttack.h
        src/FeatureCollect.cpp
        src/FeatureCollect.h
        src/FeatureHealth.cpp
        src/FeatureHealth.h
        src/FeatureInfo.h
        src/FeatureMove.cpp
        src/FeatureMove.h
        src/Interfaces.h
        src/Kernel.cpp
        src/Kernel.h
        src/Map.h
        src/MapFull.cpp
        src/MapFull.h
        src/MapLocal.cpp
        src/MapLocal.h
        src/MapResource.h
        src/MapsPath.h
        src/MapsPathsFinder.cpp
        src/MapsPathsFinder.h
        src/Player.cpp
        src/Player.h
        src/PlayerSlot.h
        src/Resource.h
        src/ResourceInfo.h
        src/Resources.h
        src/Strategix_Forward.h
        src/StrategixCommon.h
        src/StrategixException.h
        src/StrategixLog.cpp
        src/StrategixLog.h
        src/StrategixSingleton.h
        src/TechTree.cpp
        src/TechTree.h
        src/TechTreesBuilder.h
        src/ConfigurationManager.cpp src/KernelSlot.h)
