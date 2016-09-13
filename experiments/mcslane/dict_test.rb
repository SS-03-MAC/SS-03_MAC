require "./tree_dict"

dict = TreeDict::Dictionary.new()
vowels = "aeiou"
i = 0
while i < vowels.length
  dict.add(i, vowels[i])
  i += 1
end


i = 0
while i < vowels.length
  puts dict.get(i)
  i += 1
end
puts dict
puts dict.get(5)
dict.add(2, 'z')
puts dict.get(2)