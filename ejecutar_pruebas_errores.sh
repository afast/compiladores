#!/bin/sh

echo ""
echo "hacemos make"
make >/dev/null
echo ""
echo "EJECUCION"
echo "---------"
echo ""
echo "TEST1"
echo "---------"
./myruby tests/testErr1.rb 
echo ""
echo "TEST2"
echo "---------"
./myruby tests/testErr2.rb
echo ""
echo "TEST3"
echo "---------"
./myruby tests/testErr3.rb
echo ""
echo "TEST4"
echo "---------"
./myruby tests/testErr4.rb
echo ""
echo "TEST5"
echo "---------"
./myruby tests/testErr5.rb
echo ""