
1. Install all necessary versions of soft. More information on official sites. 
2. Set correct pathes in project's properties to ogre, boost, etc.
3. Check current directory to be set in /Sample1. If not, change it in project properties.

#####################################
Blender model creation for OGRE
#####################################
1. use Blender 2.44 !!!!!!!!!!!!!!!!!!
2. Set center of object at the bottom - on the ground in Edit Mode.
3. apply Scale/Rotation to ObData for all objects, including armature, before animation creating !!!!!
4. use only armature animations with only "Vertex Groups" and apply it for all vertexes !!!!!
5. apply all Modifiers before export.
6. in OGRE Meshes Exporter: use "Game Engine Materials", and don't use "Apply Modifiers" !!!

*** I think it exports basing only on the mesh's information ( Edit Mode )

#####################################
Linux to Windows from scratch:
#####################################
1. install directX, OGRE, boost, compile boost
2. git clone project from linux (open sshd port before)
3. create VC solution with empty exe project for Sample1, empty lib project for Strategix. Set the last as dependence of Sample1.
3.5. Set the same boost dependencies for Strategix and for Ogre to avoid linker conflicts.
4. set in and out pathes and dependences and copy necessary dlls to run directory.
5. add ogre configs for windows: ogre.conf, plugins.conf
6. reconfigure all the symbol links T__T
7. add to .gitignore all unnecessary VC files and folders.
