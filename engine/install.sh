
# Compilacao do Executavel
cmake CMakeLists.txt
make

# Install Exec
E=$(echo $PATH | cut -d: -f1 )
cp engine $E

# Install Manual
: '
P=$(manpath | cut -d: -f-1)
cp manGenerator.1 $P/man1/generator.1
gzip $P/man1/generator.1
'
