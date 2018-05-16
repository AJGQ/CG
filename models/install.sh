# chmod +x install.sh

cd ../engine
make clean
rm CMakeCache.txt 
cmake CMakeLists.txt
sudo ./install.sh

cd ../generator
make clean
sudo ./install

cd ../models
./genericModels.sh

for i in `ls *.xml`
do
    engine $i
done

