##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Sample1
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "C:\Users\Nya\Projects\DIPLOM"
ProjectPath            := "C:\Users\Nya\Projects\DIPLOM\Sample1"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Nya
Date                   :=05/15/11
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="C:\Users\Nya\Projects\DIPLOM\Sample1\Sample1.txt"
MakeDirCommand         :=makedir
CmpOptions             := -g $(Preprocessors)
C_CmpOptions           := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)src $(IncludeSwitch)../common_include $(IncludeSwitch)OgreWrap/src $(IncludeSwitch)../Strategix/src $(IncludeSwitch)"$(BOOST_ROOT)" $(IncludeSwitch)"$(OGRE_HOME)/include/OGRE" $(IncludeSwitch)"$(OGRE_HOME)/include/OIS" 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)Strategix $(LibrarySwitch)boost_system-mgw45-mt-d-1_46_1 $(LibrarySwitch)boost_filesystem-mgw45-mt-d-1_46_1 $(LibrarySwitch)OIS_d $(LibrarySwitch)OgreMain_d.dll 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)"$(BOOST_ROOT)/stage/lib" $(LibraryPathSwitch)"../Strategix/Debug/" $(LibraryPathSwitch)"$(OGRE_HOME)/lib/debug" 


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects=$(IntermediateDirectory)/src_MapTexture$(ObjectSuffix) $(IntermediateDirectory)/src_MediatorFrameListener$(ObjectSuffix) $(IntermediateDirectory)/src_MyApp$(ObjectSuffix) $(IntermediateDirectory)/src_MyFrameListener$(ObjectSuffix) $(IntermediateDirectory)/src_MyMouseListener$(ObjectSuffix) $(IntermediateDirectory)/src_ObjectTitle$(ObjectSuffix) $(IntermediateDirectory)/src_OObject$(ObjectSuffix) $(IntermediateDirectory)/src_OObjectLabel$(ObjectSuffix) $(IntermediateDirectory)/src_OObjectResource$(ObjectSuffix) $(IntermediateDirectory)/src_OObjectTitled$(ObjectSuffix) \
	$(IntermediateDirectory)/src_OObjectUnit$(ObjectSuffix) $(IntermediateDirectory)/src_LabelsHolder$(ObjectSuffix) $(IntermediateDirectory)/src_Main$(ObjectSuffix) $(IntermediateDirectory)/src_TechTreesBuilderFromXml$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

objects_file:
	@echo $(Objects) > $(ObjectsFileList)

makeDirStep:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_MapTexture$(ObjectSuffix): OgreWrap/src/MapTexture.cpp $(IntermediateDirectory)/src_MapTexture$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MapTexture.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_MapTexture$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MapTexture$(DependSuffix): OgreWrap/src/MapTexture.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MapTexture$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MapTexture$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MapTexture.cpp"

$(IntermediateDirectory)/src_MapTexture$(PreprocessSuffix): OgreWrap/src/MapTexture.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MapTexture$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MapTexture.cpp"

$(IntermediateDirectory)/src_MediatorFrameListener$(ObjectSuffix): OgreWrap/src/MediatorFrameListener.cpp $(IntermediateDirectory)/src_MediatorFrameListener$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MediatorFrameListener.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_MediatorFrameListener$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MediatorFrameListener$(DependSuffix): OgreWrap/src/MediatorFrameListener.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MediatorFrameListener$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MediatorFrameListener$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MediatorFrameListener.cpp"

$(IntermediateDirectory)/src_MediatorFrameListener$(PreprocessSuffix): OgreWrap/src/MediatorFrameListener.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MediatorFrameListener$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MediatorFrameListener.cpp"

$(IntermediateDirectory)/src_MyApp$(ObjectSuffix): OgreWrap/src/MyApp.cpp $(IntermediateDirectory)/src_MyApp$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MyApp.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_MyApp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MyApp$(DependSuffix): OgreWrap/src/MyApp.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MyApp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MyApp$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MyApp.cpp"

$(IntermediateDirectory)/src_MyApp$(PreprocessSuffix): OgreWrap/src/MyApp.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MyApp$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MyApp.cpp"

$(IntermediateDirectory)/src_MyFrameListener$(ObjectSuffix): OgreWrap/src/MyFrameListener.cpp $(IntermediateDirectory)/src_MyFrameListener$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MyFrameListener.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_MyFrameListener$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MyFrameListener$(DependSuffix): OgreWrap/src/MyFrameListener.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MyFrameListener$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MyFrameListener$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MyFrameListener.cpp"

$(IntermediateDirectory)/src_MyFrameListener$(PreprocessSuffix): OgreWrap/src/MyFrameListener.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MyFrameListener$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MyFrameListener.cpp"

$(IntermediateDirectory)/src_MyMouseListener$(ObjectSuffix): OgreWrap/src/MyMouseListener.cpp $(IntermediateDirectory)/src_MyMouseListener$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MyMouseListener.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_MyMouseListener$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MyMouseListener$(DependSuffix): OgreWrap/src/MyMouseListener.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MyMouseListener$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MyMouseListener$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MyMouseListener.cpp"

$(IntermediateDirectory)/src_MyMouseListener$(PreprocessSuffix): OgreWrap/src/MyMouseListener.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MyMouseListener$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/MyMouseListener.cpp"

$(IntermediateDirectory)/src_ObjectTitle$(ObjectSuffix): OgreWrap/src/ObjectTitle.cpp $(IntermediateDirectory)/src_ObjectTitle$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/ObjectTitle.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_ObjectTitle$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ObjectTitle$(DependSuffix): OgreWrap/src/ObjectTitle.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ObjectTitle$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ObjectTitle$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/ObjectTitle.cpp"

$(IntermediateDirectory)/src_ObjectTitle$(PreprocessSuffix): OgreWrap/src/ObjectTitle.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ObjectTitle$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/ObjectTitle.cpp"

$(IntermediateDirectory)/src_OObject$(ObjectSuffix): OgreWrap/src/OObject.cpp $(IntermediateDirectory)/src_OObject$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObject.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_OObject$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_OObject$(DependSuffix): OgreWrap/src/OObject.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_OObject$(ObjectSuffix) -MF$(IntermediateDirectory)/src_OObject$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObject.cpp"

$(IntermediateDirectory)/src_OObject$(PreprocessSuffix): OgreWrap/src/OObject.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_OObject$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObject.cpp"

$(IntermediateDirectory)/src_OObjectLabel$(ObjectSuffix): OgreWrap/src/OObjectLabel.cpp $(IntermediateDirectory)/src_OObjectLabel$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObjectLabel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_OObjectLabel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_OObjectLabel$(DependSuffix): OgreWrap/src/OObjectLabel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_OObjectLabel$(ObjectSuffix) -MF$(IntermediateDirectory)/src_OObjectLabel$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObjectLabel.cpp"

$(IntermediateDirectory)/src_OObjectLabel$(PreprocessSuffix): OgreWrap/src/OObjectLabel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_OObjectLabel$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObjectLabel.cpp"

$(IntermediateDirectory)/src_OObjectResource$(ObjectSuffix): OgreWrap/src/OObjectResource.cpp $(IntermediateDirectory)/src_OObjectResource$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObjectResource.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_OObjectResource$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_OObjectResource$(DependSuffix): OgreWrap/src/OObjectResource.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_OObjectResource$(ObjectSuffix) -MF$(IntermediateDirectory)/src_OObjectResource$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObjectResource.cpp"

$(IntermediateDirectory)/src_OObjectResource$(PreprocessSuffix): OgreWrap/src/OObjectResource.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_OObjectResource$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObjectResource.cpp"

$(IntermediateDirectory)/src_OObjectTitled$(ObjectSuffix): OgreWrap/src/OObjectTitled.cpp $(IntermediateDirectory)/src_OObjectTitled$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObjectTitled.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_OObjectTitled$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_OObjectTitled$(DependSuffix): OgreWrap/src/OObjectTitled.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_OObjectTitled$(ObjectSuffix) -MF$(IntermediateDirectory)/src_OObjectTitled$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObjectTitled.cpp"

$(IntermediateDirectory)/src_OObjectTitled$(PreprocessSuffix): OgreWrap/src/OObjectTitled.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_OObjectTitled$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObjectTitled.cpp"

$(IntermediateDirectory)/src_OObjectUnit$(ObjectSuffix): OgreWrap/src/OObjectUnit.cpp $(IntermediateDirectory)/src_OObjectUnit$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObjectUnit.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_OObjectUnit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_OObjectUnit$(DependSuffix): OgreWrap/src/OObjectUnit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_OObjectUnit$(ObjectSuffix) -MF$(IntermediateDirectory)/src_OObjectUnit$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObjectUnit.cpp"

$(IntermediateDirectory)/src_OObjectUnit$(PreprocessSuffix): OgreWrap/src/OObjectUnit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_OObjectUnit$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Sample1/OgreWrap/src/OObjectUnit.cpp"

$(IntermediateDirectory)/src_LabelsHolder$(ObjectSuffix): src/LabelsHolder.cpp $(IntermediateDirectory)/src_LabelsHolder$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Sample1/src/LabelsHolder.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_LabelsHolder$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_LabelsHolder$(DependSuffix): src/LabelsHolder.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_LabelsHolder$(ObjectSuffix) -MF$(IntermediateDirectory)/src_LabelsHolder$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Sample1/src/LabelsHolder.cpp"

$(IntermediateDirectory)/src_LabelsHolder$(PreprocessSuffix): src/LabelsHolder.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_LabelsHolder$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Sample1/src/LabelsHolder.cpp"

$(IntermediateDirectory)/src_Main$(ObjectSuffix): src/Main.cpp $(IntermediateDirectory)/src_Main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Sample1/src/Main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Main$(DependSuffix): src/Main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Main$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Main$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Sample1/src/Main.cpp"

$(IntermediateDirectory)/src_Main$(PreprocessSuffix): src/Main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Main$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Sample1/src/Main.cpp"

$(IntermediateDirectory)/src_TechTreesBuilderFromXml$(ObjectSuffix): src/TechTreesBuilderFromXml.cpp $(IntermediateDirectory)/src_TechTreesBuilderFromXml$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/Users/Nya/Projects/DIPLOM/Sample1/src/TechTreesBuilderFromXml.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_TechTreesBuilderFromXml$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_TechTreesBuilderFromXml$(DependSuffix): src/TechTreesBuilderFromXml.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_TechTreesBuilderFromXml$(ObjectSuffix) -MF$(IntermediateDirectory)/src_TechTreesBuilderFromXml$(DependSuffix) -MM "C:/Users/Nya/Projects/DIPLOM/Sample1/src/TechTreesBuilderFromXml.cpp"

$(IntermediateDirectory)/src_TechTreesBuilderFromXml$(PreprocessSuffix): src/TechTreesBuilderFromXml.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_TechTreesBuilderFromXml$(PreprocessSuffix) "C:/Users/Nya/Projects/DIPLOM/Sample1/src/TechTreesBuilderFromXml.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/*.*
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe


