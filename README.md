# synth

#### Getting the source from repository:  
git clone https://github.com/stawrocek/synth  
cd synth  
git submodule update --init --recursive  

If you already have the source in form of a .zip file run this command instead of updating the submodule:  

git clone https://github.com/juce-framework/JUCE.git  


## building on Linux

#### Requirements for installation on Debian: 
* cmake 3.16+
* libxrandr-dev libxinerama1 libxinerama-dev libxcursor-dev libfreetype6-dev libasound2-dev

#### Building:  

mkdir build && cd build  
cmake -DCMAKE_BUILD_TYPE=Release ..  
make

now ./SynthPlugin_artefacts/ contains builded binaries

## building on Windows:  

mkdir build && cd build  
cmake ..

now open build/SynthProject.sln in VisualStudio  
set solution configuration to "Release"    
press build>build solution (ctrl+shift+b)    

now ./SynthPlugin_artefacts/ contains builded binaries
