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
./myruby test1.rb > salidas_nuestras/test1.txt
if diff salidas_nuestras/test1.txt salidas_ruby/test1.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo ""
echo ""
echo "TEST2"
echo "---------"
./myruby test2.rb > salidas_nuestras/test2.txt
if diff salidas_nuestras/test2.txt salidas_ruby/test2.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo ""
echo ""
echo "TEST3"
echo "---------"
./myruby test3.rb > salidas_nuestras/test3.txt
if diff salidas_nuestras/test3.txt salidas_ruby/test3.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo ""
echo ""
echo "TEST4"
echo "---------"
./myruby test4.rb > salidas_nuestras/test4.txt
if diff salidas_nuestras/test4.txt salidas_ruby/test4.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo ""
echo ""
echo "TEST5"
echo "---------"
./myruby test5.rb > salidas_nuestras/test5.txt
if diff salidas_nuestras/test5.txt salidas_ruby/test5.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo ""
echo ""
echo "TEST6"
echo "---------"
./myruby test6.rb > salidas_nuestras/test6.txt
if diff salidas_nuestras/test6.txt salidas_ruby/test6.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo ""
echo ""
echo "TEST7"
echo "---------"
./myruby test7.rb > salidas_nuestras/test7.txt
if diff salidas_nuestras/test7.txt salidas_ruby/test7.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo ""
echo ""
echo "TEST8"
echo "---------"
./myruby test8.rb > salidas_nuestras/test8.txt
if diff salidas_nuestras/test8.txt salidas_ruby/test8.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo ""
