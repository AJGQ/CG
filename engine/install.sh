
# copilacao do executavel
cmake CMakeLists.txt
make 

# install exec
E=$(echo $PATH | cut -d: -f1 )
cp engine $E

# install manual
: '
P=$(manpath | cut -d: -f-1)
cp manGenerator.1 $P/man1/generator.1
gzip $P/man1/generator.1
'
