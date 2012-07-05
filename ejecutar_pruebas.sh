#!/bin/sh

echo
echo "hacemos make"
make >/dev/null
if [ ! -d salidas_ruby ]; then mkdir salidas_ruby; fi
if [ ! -d salidas_nuestras ]; then mkdir salidas_nuestras; fi
rm salidas_ruby/*
ruby -I. test1.rb > salidas_ruby/test1.txt
ruby -I. test2.rb > salidas_ruby/test2.txt
ruby -I. test3.rb > salidas_ruby/test3.txt
ruby -I. test4.rb > salidas_ruby/test4.txt
ruby -I. test5.rb > salidas_ruby/test5.txt
ruby -I. test6.rb > salidas_ruby/test6.txt
ruby -I. test7.rb > salidas_ruby/test7.txt
ruby -I. test8.rb > salidas_ruby/test8.txt
ruby -I. testvacio.rb > salidas_ruby/testvacio.txt
echo
echo "EJECUCION"
echo "---------"
echo ""
echo "TEST1"
./myruby test1.rb > salidas_nuestras/test1.txt
if diff salidas_nuestras/test1.txt salidas_ruby/test1.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo "---------"
echo ""
echo "TEST2"
./myruby test2.rb > salidas_nuestras/test2.txt
if diff salidas_nuestras/test2.txt salidas_ruby/test2.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo "---------"
echo ""
echo "TEST3"
./myruby test3.rb > salidas_nuestras/test3.txt
if diff salidas_nuestras/test3.txt salidas_ruby/test3.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo "---------"
echo ""
echo "TEST4"
./myruby test4.rb > salidas_nuestras/test4.txt
if diff salidas_nuestras/test4.txt salidas_ruby/test4.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo "---------"
echo ""
echo "TEST5"
./myruby test5.rb > salidas_nuestras/test5.txt
if diff salidas_nuestras/test5.txt salidas_ruby/test5.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo "---------"
echo ""
echo "TEST6"
./myruby test6.rb > salidas_nuestras/test6.txt
if diff salidas_nuestras/test6.txt salidas_ruby/test6.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo "---------"
echo ""
echo "TEST7"
./myruby test7.rb > salidas_nuestras/test7.txt
if diff salidas_nuestras/test7.txt salidas_ruby/test7.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo "---------"
echo ""
echo "TEST8"
./myruby test8.rb > salidas_nuestras/test8.txt
if diff salidas_nuestras/test8.txt salidas_ruby/test8.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo "---------"
echo ""
echo "TEST VACIO"
./myruby testvacio.rb > salidas_nuestras/testvacio.txt
if diff salidas_nuestras/testvacio.txt salidas_ruby/testvacio.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo "---------"
echo ""
