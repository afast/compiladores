#!/bin/sh

echo
echo "Compilando el interprete"
make >/dev/null
echo ""
echo "tests/testErr1.rb"
./myruby tests/testErr1.rb 
echo ""
echo "tests/testErr2.rb"
./myruby tests/testErr2.rb
echo ""
echo "tests/testErr3.rb"
./myruby tests/testErr3.rb
echo ""
echo "tests/testErr4.rb"
./myruby tests/testErr4.rb
echo ""
echo "tests/testErr5.rb"
./myruby tests/testErr5.rb

