module Stack
  class StackNode
    attr_reader :data
    attr_accessor :data, :next

    def initialize(data)
      @data = data
    end

    def to_s
      return "(#{data} | next)"
    end
  end

  class LinkedStack
    attr_reader :top
    attr_accessor :top

    def initialize(data=nil)
      if data.nil?
        @top = nil
      else
        @top = StackNode.new(data)
      end
    end

    def empty?
      return top.nil?
    end

    def peek
      if empty?
        return nil
      else
        return top.data
      end
    end

    def pop
      if empty?
        return nil
      else
        data = top.data
        top = top.n
        return data
      end
    end

    def push(data=nil)
      if data.nil?
        return false
      elsif top.nil?
        top = StackNode.new(data)
      else
        temp = StackNode.new(data)
        temp.next = top
        top = temp
      end
    end
end 

stack = Stack::LinkedStack()

i = 0
while i < 10
  stack.push(i)
end

while !stack.empty?
  puts stack.pop