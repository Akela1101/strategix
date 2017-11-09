##   Blender model creation

* Set center of object at the bottom - on the ground in Edit Mode.
* Apply Scale/Rotation to ObData for all objects, including armature, before animation creating.
* Use only armature animations with only "Vertex Groups" and apply it for all vertexes.
* Apply all Modifiers manually before export.
* In OGRE Meshes Exporter: use "Game Engine Materials", and don't use "Apply Modifiers".

*** It seems that export is based only on the mesh's information ( Blender - Edit Mode ) ***

### Adding new Feature \[ deprecated ]

1. add properties to xml file in \<features>
2. add new class in FeatureInfo.h
3. class FeatureInfo***; in Strategix_Forward.h
4. add code to your TechTreesBuilder->Build method
5. add new class Feature*** (with all virtual methods!)
6. \#include "Feature***" in Enti.h and Strategix.h
7. add code to Enti::AddFeature(..)
8. add new callback interface to Interfaces.h and EntiSlot.h (if you need one)
9. specify this callback in EntiSlot descendant
