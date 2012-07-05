class Perro  
  # método inicializar clase
  def initialize(raza, nombre)
    # atributos
    @raza = raza
    @nombre = nombre
  end
  
  # método ladrar
  def ladrar
    puts 'Guau! Guau!'
  end
  
  # método saludar
  def saludar
    puts @raza
    puts @nombre
  end
 
end

d = Perro.new("Ovejero")
