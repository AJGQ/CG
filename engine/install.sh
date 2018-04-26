cd $(dirname $0)
# Compilacao do Executavel
cmake CMakeLists.txt
make

# Install Exec
cp engine /usr/local/bin

# Install Manual
: '
P=$(manpath | cut -d: -f-1)
cp manGenerator.1 $P/man1/generator.1
gzip $P/man1/generator.1
'
