# copilacao do executavel
make final

# install exec
E=$(echo $PATH | cut -d: -f1 )
cp -f generator $E

# install manual
P=$(manpath | cut -d: -f1)
cp -f manGenerator.1 $P/man1/generator.1
gzip -f $P/man1/generator.1
