# Compilacao do executavel
make generator

# Install exec
cp -f generator /usr/local/bin

# Install Manual
#P=$(manpath | cut -d: -f1)
#cp -f manGenerator.1 $P/man1/generator.1
#gzip -f $P/man1/generator.1
