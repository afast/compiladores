#defino metodo
def say_hello a, b
  puts a
  puts b
  puts 'hola martin'
end

#llamo al metodo 2 veces
say_hello 'jellou', 3+4+5
say_hello 'hola', 'martin'

#ARREGLOS
#creo arreglo vacio
a = []
puts a[1]
puts a[2]
#seteo valores al arreglo
a[1]= 10
a[2]= 20
#muestro los nuevos valores
puts a[1]
puts a[2]
#creo un arreglo
b = [1, 2, 3]
puts b[0]
puts b[1]
puts b[2]
#le modifico un elemento
b[1]= "modificado"
#imprimo el arreglo modificado
puts b[0]
puts b[1]
puts b[2]
#largos de arreglos
puts "length del arreglo: #{b.length}"
puts "size del arreglo: #{b.size}"
#pruebas del each
arreglo = [ 1 , 2.35 , 3 , true , "nuevo_string" ]
puts a[2]
arreglo[0]= "modificado"
arreglo.each do |tmp|
  puts "Esto es lo que tiene: #{tmp}"
end
#Bloques
puts "scope"
# modifico una variable dentro de un metodo, pero fuera del metodo mantiene su valor. 
nueva_var = "valor bloque de afuera"
def prueba
  nueva_var = "la modifique dentro"
  puts nueva_var
end
prueba
puts nueva_var
