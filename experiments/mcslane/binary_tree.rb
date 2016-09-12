module BinarySearchTree
  class BinaryTreeNode
    attr_reader :data
    attr_accessor :left, :right, :parent

    def initialize(data)
      @data = data
    end

    def insert(v)
      case data <=> v
      when 1 then insert_left(v)
      when -1 then insert_right(v)
      when 0 then false
      end
    end

    def to_s
      return "(#{data} #{left} #{right})"
    end

    private

    def insert_left(v)
      if left
        left.insert(v)
      else
        self.left = BinaryTreeNode.new(v)
        self.left.parent = self
      end
    end

    def insert_right(v)
      if right
        right.insert(v)
      else
        self.right = BinaryTreeNode.new(v)
        self.right.parent = self
      end
    end
  end

  class BinaryTree
    attr_reader :root
    attr_accessor :root

    def initialize(data=nil)
      if data.nil?
        @root = nil
      else
        @root = BinaryTreeNode.new(data)
      end
    end

    def insert(data)
      if data.nil?
        return false
      elsif @root.nil?
        @root = BinaryTreeNode.new(data)
      else
        @root.insert(data)
      end
    end

    def to_s
      return @root.to_s
    end
  end
end

tree = BinarySearchTree::BinaryTree.new()
tree.insert(10)
tree.insert(15)
tree.insert(5)
puts tree

puts tree.root.left.parent.data