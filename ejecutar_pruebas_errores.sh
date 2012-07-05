#!/bin/sh

echo ""
echo "hacemos make"
make
echo ""
echo "EJECUCION"
echo "---------"
echo ""
echo ""
echo "TEST1"
echo "---------"
./myruby testErr1.rb 
echo ""
echo ""
echo "TEST2"
echo "---------"
./myruby testErr2.rb
echo ""
echo ""
echo "TEST3"
echo "---------"
./myruby testErr3.rb
echo ""
echo ""
echo "TEST4"
echo "---------"
./myruby testErr4.rb
echo ""
echo ""
echo "TEST5"
echo "---------"
./myruby testErr5.rb
echo ""
echo ""
echo "TEST6"
echo "---------"
./myruby testErr6.rb
echo ""
echo ""
#echo "TEST7"
#echo "---------"
#./myruby testErr7.rb
#echo ""