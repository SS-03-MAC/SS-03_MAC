require "./stack"

stack = Stack::LinkedStack.new()

i = 0
while i < 10
  stack.push(i)
  i += 1
end

while !stack.empty?
  puts stack.pop
end