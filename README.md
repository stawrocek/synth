# synth


## Building instructions:

#### Requirements for installation on Debian 10: 
* cmake 3.16+
* libxrandr-dev libxinerama1 libxinerama-dev libxcursor-dev libfreetype6-dev libasound2-dev


#Getting the source from repository:  
git clone https://github.com/stawrocek/synth  
cd synth  
git submodule update --init --recursive  

#If you already have the source in form of a .zip file run this command instead of updating the submodule:  
git clone https://github.com/juce-framework/JUCE.git  

#building:  

mkdir build && cd build  
cmake -DCMAKE_BUILD_TYPE=Release ..  

#on Linux:  
make  

#on Windows: 
#open build/SynthProject.sln in VisualStudio  
#set solution configuration to "Release"    
#press build>build solution (ctrl+shift+b)    

#run standalone executable:  
./SynthPlugin_artefacts/Standalone/Synth  
