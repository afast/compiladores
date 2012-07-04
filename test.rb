
puts 10
puts ARGV[0]
puts 11.0
puts 11.0*1.1
puts 2.4*0.5
puts 1.1+1.1
puts 2/1.5
puts 3.2-1.9
puts 1.9-3.2
puts false
puts 'algo'

puts 11

def say_hello a, b
  puts a
  puts b
  puts 'hola martin'
end

say_hello 'jellou', 3+4+5
say_hello 'hola', 'martin'

class Hola
  attr_accessor :hi
  attr_reader :some
  attr_writer :thing
  def say a , b
    puts a
    puts b
  end
  def set b
    @some = b
  end
  def thingy
    puts @thing
  end
end

al = Hola.new
al.say 'hola andreas', "final"
al.set 'seteando un attr'
al.say 'hi', 'chau'
al.hi = 'yummy'
puts al.hi
al.say '----' , 'chau'
al.thing = 333
al.thingy
al.thing = 334
al.thingy
puts al.some
puts '============================================================'
puts b
puts '====='
a=2
puts 5.0*5*5
a='hola'
puts a
b=' caro'
puts a+b
puts 'as'
c=4
c=10

while c>0
  puts c
  c= c-1
end
c=4

y=b*c

puts y

if true
  puts 4*c
elsif 1>=1
  puts b
  puts 'true'
end
if 2>1
  puts 'ifelse'
else
  puts 'efelse'
end
if (4>2) && (4<9)
  puts 'jami'
else
  puts 'jamo'
end

if 4>2 || 4<9
  puts 'elsif'
elsif 4<2
  puts 'elsif'
else
  puts 5
end

while false
  puts 10
end

=begin
puts gets
puts `hello`
puts hola.object_id
puts hello.size
puts nil
puts 'holas'*2
puts 'hi: ' + 'all'
puts hallo.respond_to?('him')
puts hallo.instance_of?('hiasd')
if 2<3
  puts 1+2
end
if (4>2) && (4<9)
  puts 'jami'
else
  puts 'jamo'
end

if 4>2 && 4<9
  puts 'jami'
elsif 4<2
  puts 'jamo'
else
  puts 'beee'
end
=end

