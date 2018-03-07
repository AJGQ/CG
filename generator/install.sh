
# Compilacao do executavel
make final

# Install exec
E=$(echo $PATH | cut -d: -f1 )
cp -f generator $E

# Install Manual
P=$(manpath | cut -d: -f1)
cp -f manGenerator.1 $P/man1/generator.1
gzip -f $P/man1/generator.1
