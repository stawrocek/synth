# synth


#### Installation instruction for Debian 10:  

Requirements for installation on Debian 10:   
* cmake 3.16+  
* libxrandr-dev libxinerama1 libxinerama-dev libxcursor-dev libfreetype6-dev libasound2-dev  


git clone https://github.com/stawrocek/synth  
cd synth  
git submodule update --init --recursive  
mkdir build && cd build  
cmake ..  
make  

#run standalone executable:  
./SynthPlugin_artefacts/Standalone/Synth  
