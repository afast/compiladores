#ejemplo if de la letra
xyz = 5
if xyz > 4
  puts 'La variable xyz es mayor que 4'
  puts 'Puedo poner más instrucciones dentro del if'
  if xyz == 5
    puts 'Se puede anidar un bloque if,else,end dentro de otro'
  else
    puts "Parte del bloque anidado"
  end
else
  puts 'La variable xyz no es mayor que 5'
  puts 'También puedo poner múltiples sentencias'
end
#ejemplo if nuestro
if 2*2 <= 2
  puts "MAL1"
elsif 8 > 5
  puts "OK"
elsif false
  puts "MAL2"
elsif 10 < 2
  puts "MAL3"
else 
  puts "MAL4"
end
#otro ejemplo nuestro
if 10**10 < 10*10
  puts "MAL1"
elsif 20 == 2
  puts "MAL2"
else 
  puts "OK"
end
#ejemplo case de la letra
xyz = 10
par = case
when xyz % 2 == 0 then true
when xyz % 2 != 0 then false
end
puts par
#ejemplo while de la letra
var = 0
while var < 10
puts var
var = var + 1
end
#ejemplo con while e if anidados complejo
if 2*5 == 10 && 2**3 == 8 
  puts "entre al if"
  a = 1
  while a < 5
    puts a
    if a % 2 == 0
      puts "es par"
    else
      puts "es impar"
    end
    a = a + 1;
  end
end