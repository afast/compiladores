#!/bin/sh

echo
echo "Compilando el interprete"
make >/dev/null
if [ ! -d salidas_ruby ]; then mkdir salidas_ruby; fi
if [ ! -d salidas_nuestras ]; then mkdir salidas_nuestras; else rm salidas_nuestras/*; fi

echo
echo "Ejecutando pruebas"
echo ""
echo -n "tests/test1.rb ... "
./myruby tests/test1.rb > salidas_nuestras/test1.txt
if diff salidas_nuestras/test1.txt salidas_ruby/test1.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo -n "tests/test2.rb ... "
./myruby tests/test2.rb > salidas_nuestras/test2.txt
if diff salidas_nuestras/test2.txt salidas_ruby/test2.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo -n "tests/test3.rb ... "
./myruby tests/test3.rb arg1 arg2 > salidas_nuestras/test3.txt
if diff salidas_nuestras/test3.txt salidas_ruby/test3.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo -n "tests/test4.rb ... "
./myruby tests/test4.rb > salidas_nuestras/test4.txt
if diff salidas_nuestras/test4.txt salidas_ruby/test4.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo -n "tests/test5.rb ... "
./myruby tests/test5.rb > salidas_nuestras/test5.txt
if diff salidas_nuestras/test5.txt salidas_ruby/test5.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo -n "tests/test6.rb ... "
./myruby tests/test6.rb > salidas_nuestras/test6.txt
if diff salidas_nuestras/test6.txt salidas_ruby/test6.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo -n "tests/test7.rb ... "
./myruby tests/test7.rb > salidas_nuestras/test7.txt
if diff salidas_nuestras/test7.txt salidas_ruby/test7.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo -n "tests/test8.rb ... "
./myruby tests/test8.rb > salidas_nuestras/test8.txt
if diff salidas_nuestras/test8.txt salidas_ruby/test8.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
echo -n "tests/testvacio.rb ... "
./myruby tests/testvacio.rb > salidas_nuestras/testvacio.txt
if diff salidas_nuestras/testvacio.txt salidas_ruby/testvacio.txt >/dev/null ; then
  echo OK
else
  echo Hay diferencias en los archivos
fi
