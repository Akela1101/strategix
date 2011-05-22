##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=Strategix
ConfigurationName      :=Release
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "C:\Users\Nya\Projects\DIPLOM"
ProjectPath            := "C:\Users\Nya\Projects\DIPLOM\Strategix"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Nya
Date                   :=05/14/11
CodeLitePath           :="C:\Program Files\CodeLite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="C:\Users\Nya\Projects\DIPLOM\Strategix\Strategix.txt"
MakeDirCommand         :=makedir
CmpOptions             :=  $(Preprocessors)
C_CmpOptions           :=  $(Preprocessors)
LinkOptions            :=  
IncludePath            := $(IncludeSwitch)C:/Users/Nya/Projects/boost_1_46_1  $(IncludeSwitch). $(IncludeSwitch)src $(IncludeSwitch)../common_include 
RcIncludePath          :=
Libs                   :=
LibPath                := $(LibraryPathSwitch). 


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects=$(IntermediateDirectory)/src_CoordStructs$(ObjectSuffix) $(IntermediateDirectory)/src_Enti$(ObjectSuffix) $(IntermediateDirectory)/src_Feature$(ObjectSuffix) $(IntermediateDirectory)/src_FeatureMove$(ObjectSuffix) $(IntermediateDirectory)/src_Kernel$(ObjectSuffix) $(IntermediateDirectory)/src_KernelBase$(ObjectSuffix) $(IntermediateDirectory)/src_Log$(ObjectSuffix) $(IntermediateDirectory)/src_Map$(ObjectSuffix) $(IntermediateDirectory)/src_MapFull$(ObjectSuffix) $(IntermediateDirectory)/src_MapLocal$(ObjectSuffix) \
	$(IntermediateDirectory)/src_MapsPath$(ObjectSuffix) $(IntermediateDirectory)/src_MapsPathsFinder$(ObjectSuffix) $(IntermediateDirectory)/src_Mediator$(ObjectSuffix) $(IntermediateDirectory)/src_Player$(ObjectSuffix) $(IntermediateDirectory)/src_TechTree$(ObjectSuffix) $(IntermediateDirectory)/src_Unit$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	$(ArchiveTool) $(ArchiveOutputSwitch)$(OutputFile) $(Objects)

objects_file:
	@echo $(Objects) > $(ObjectsFileList)

./Release:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_CoordStructs$(ObjectSuffix): src/CoordStructs.cpp $(IntermediateDirectory)/src_CoordStructs$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/CoordStructs.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_CoordStructs$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_CoordStructs$(DependSuffix): src/CoordStructs.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_CoordStructs$(ObjectSuffix) -MF$(IntermediateDirectory)/src_CoordStructs$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/CoordStructs.cpp"

$(IntermediateDirectory)/src_CoordStructs$(PreprocessSuffix): src/CoordStructs.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_CoordStructs$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/CoordStructs.cpp"

$(IntermediateDirectory)/src_Enti$(ObjectSuffix): src/Enti.cpp $(IntermediateDirectory)/src_Enti$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Enti.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Enti$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Enti$(DependSuffix): src/Enti.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Enti$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Enti$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Enti.cpp"

$(IntermediateDirectory)/src_Enti$(PreprocessSuffix): src/Enti.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Enti$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Enti.cpp"

$(IntermediateDirectory)/src_Feature$(ObjectSuffix): src/Feature.cpp $(IntermediateDirectory)/src_Feature$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Feature.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Feature$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Feature$(DependSuffix): src/Feature.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Feature$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Feature$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Feature.cpp"

$(IntermediateDirectory)/src_Feature$(PreprocessSuffix): src/Feature.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Feature$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Feature.cpp"

$(IntermediateDirectory)/src_FeatureMove$(ObjectSuffix): src/FeatureMove.cpp $(IntermediateDirectory)/src_FeatureMove$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/FeatureMove.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_FeatureMove$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_FeatureMove$(DependSuffix): src/FeatureMove.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_FeatureMove$(ObjectSuffix) -MF$(IntermediateDirectory)/src_FeatureMove$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/FeatureMove.cpp"

$(IntermediateDirectory)/src_FeatureMove$(PreprocessSuffix): src/FeatureMove.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_FeatureMove$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/FeatureMove.cpp"

$(IntermediateDirectory)/src_Kernel$(ObjectSuffix): src/Kernel.cpp $(IntermediateDirectory)/src_Kernel$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Kernel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Kernel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Kernel$(DependSuffix): src/Kernel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Kernel$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Kernel$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Kernel.cpp"

$(IntermediateDirectory)/src_Kernel$(PreprocessSuffix): src/Kernel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Kernel$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Kernel.cpp"

$(IntermediateDirectory)/src_KernelBase$(ObjectSuffix): src/KernelBase.cpp $(IntermediateDirectory)/src_KernelBase$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/KernelBase.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_KernelBase$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_KernelBase$(DependSuffix): src/KernelBase.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_KernelBase$(ObjectSuffix) -MF$(IntermediateDirectory)/src_KernelBase$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/KernelBase.cpp"

$(IntermediateDirectory)/src_KernelBase$(PreprocessSuffix): src/KernelBase.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_KernelBase$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/KernelBase.cpp"

$(IntermediateDirectory)/src_Log$(ObjectSuffix): src/Log.cpp $(IntermediateDirectory)/src_Log$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Log.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Log$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Log$(DependSuffix): src/Log.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Log$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Log$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Log.cpp"

$(IntermediateDirectory)/src_Log$(PreprocessSuffix): src/Log.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Log$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Log.cpp"

$(IntermediateDirectory)/src_Map$(ObjectSuffix): src/Map.cpp $(IntermediateDirectory)/src_Map$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Map.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Map$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Map$(DependSuffix): src/Map.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Map$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Map$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Map.cpp"

$(IntermediateDirectory)/src_Map$(PreprocessSuffix): src/Map.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Map$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Map.cpp"

$(IntermediateDirectory)/src_MapFull$(ObjectSuffix): src/MapFull.cpp $(IntermediateDirectory)/src_MapFull$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/MapFull.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_MapFull$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MapFull$(DependSuffix): src/MapFull.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MapFull$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MapFull$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/MapFull.cpp"

$(IntermediateDirectory)/src_MapFull$(PreprocessSuffix): src/MapFull.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MapFull$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/MapFull.cpp"

$(IntermediateDirectory)/src_MapLocal$(ObjectSuffix): src/MapLocal.cpp $(IntermediateDirectory)/src_MapLocal$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/MapLocal.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_MapLocal$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MapLocal$(DependSuffix): src/MapLocal.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MapLocal$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MapLocal$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/MapLocal.cpp"

$(IntermediateDirectory)/src_MapLocal$(PreprocessSuffix): src/MapLocal.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MapLocal$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/MapLocal.cpp"

$(IntermediateDirectory)/src_MapsPath$(ObjectSuffix): src/MapsPath.cpp $(IntermediateDirectory)/src_MapsPath$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/MapsPath.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_MapsPath$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MapsPath$(DependSuffix): src/MapsPath.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MapsPath$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MapsPath$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/MapsPath.cpp"

$(IntermediateDirectory)/src_MapsPath$(PreprocessSuffix): src/MapsPath.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MapsPath$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/MapsPath.cpp"

$(IntermediateDirectory)/src_MapsPathsFinder$(ObjectSuffix): src/MapsPathsFinder.cpp $(IntermediateDirectory)/src_MapsPathsFinder$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/MapsPathsFinder.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_MapsPathsFinder$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MapsPathsFinder$(DependSuffix): src/MapsPathsFinder.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MapsPathsFinder$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MapsPathsFinder$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/MapsPathsFinder.cpp"

$(IntermediateDirectory)/src_MapsPathsFinder$(PreprocessSuffix): src/MapsPathsFinder.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MapsPathsFinder$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/MapsPathsFinder.cpp"

$(IntermediateDirectory)/src_Mediator$(ObjectSuffix): src/Mediator.cpp $(IntermediateDirectory)/src_Mediator$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Mediator.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Mediator$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Mediator$(DependSuffix): src/Mediator.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Mediator$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Mediator$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Mediator.cpp"

$(IntermediateDirectory)/src_Mediator$(PreprocessSuffix): src/Mediator.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Mediator$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Mediator.cpp"

$(IntermediateDirectory)/src_Player$(ObjectSuffix): src/Player.cpp $(IntermediateDirectory)/src_Player$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Player.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Player$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Player$(DependSuffix): src/Player.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Player$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Player$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Player.cpp"

$(IntermediateDirectory)/src_Player$(PreprocessSuffix): src/Player.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Player$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Player.cpp"

$(IntermediateDirectory)/src_TechTree$(ObjectSuffix): src/TechTree.cpp $(IntermediateDirectory)/src_TechTree$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/TechTree.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_TechTree$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_TechTree$(DependSuffix): src/TechTree.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_TechTree$(ObjectSuffix) -MF$(IntermediateDirectory)/src_TechTree$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/TechTree.cpp"

$(IntermediateDirectory)/src_TechTree$(PreprocessSuffix): src/TechTree.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_TechTree$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/TechTree.cpp"

$(IntermediateDirectory)/src_Unit$(ObjectSuffix): src/Unit.cpp $(IntermediateDirectory)/src_Unit$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Unit.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Unit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Unit$(DependSuffix): src/Unit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Unit$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Unit$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Unit.cpp"

$(IntermediateDirectory)/src_Unit$(PreprocessSuffix): src/Unit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Unit$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Strategix/src/Unit.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/src_CoordStructs$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_CoordStructs$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_CoordStructs$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Enti$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Enti$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Enti$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Feature$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Feature$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Feature$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_FeatureMove$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_FeatureMove$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_FeatureMove$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Kernel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Kernel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Kernel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_KernelBase$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_KernelBase$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_KernelBase$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Log$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Log$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Log$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Map$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Map$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Map$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_MapFull$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_MapFull$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_MapFull$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_MapLocal$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_MapLocal$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_MapLocal$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_MapsPath$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_MapsPath$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_MapsPath$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_MapsPathsFinder$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_MapsPathsFinder$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_MapsPathsFinder$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Mediator$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Mediator$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Mediator$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Player$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Player$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Player$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_TechTree$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_TechTree$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_TechTree$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Unit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Unit$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Unit$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)


