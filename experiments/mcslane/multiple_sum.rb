#given an integer input, finds the sum of all multiples of three or five less than it

sum = 0
puts "Enter a number: "
limit = gets.chomp.to_i
n = 1

while n < limit
  if n % 3 == 0 || n % 5 == 0
    sum += n
  end
  n += 1
end

puts "The sum of all numbers below #{limit} that are multiples of 3 or 5 is #{sum}"