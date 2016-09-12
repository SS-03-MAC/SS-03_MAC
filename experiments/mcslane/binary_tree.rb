module BinarySearchTree
  class BinaryTreeNode
    attr_reader :data
    attr_accessor :left, :right, :parent, :data

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

    def contains(data)
      if root.nil?
        return false
      end
      node = root
      while !node.nil?
        if node.data == data
          return true
        elsif node.data < data
          node = node.right
        else
          node = node.left
        end
      end
      return false
    end

    def delete(data, node=self.root)
      if node.nil? #data is not in subtree
        return false
      end
      if data < node.data
        return delete(data, node.left)
      elsif data > node.data
        return delete(data, node.right)
      else #found our data to delete
        if node.left && node.right #both children present
          successor = find_min(node.right)
          node.data = successor.data
          delete(successor.data, successor)
        elsif node.left #only a left child
          replace(node, node.left)
        elsif node.right #only a right child
          replace(node, node.right)
        else #no children
          replace(node, nil)
        end
        return true
      end
    end

    private

    def find_min(node)
      while node.left
        node = node.left
      end
      return node
    end

    def replace(node, new_value=nil)
      if node.parent
        if node == node.parent.left
          node.parent.left = new_value
        else
          node.parent.right = new_value
        end
      end
      if new_value
        new_value.parent = nil
      end
    end
  end
end

tree = BinarySearchTree::BinaryTree.new()
tree.insert(10)
tree.insert(15)
tree.insert(5)
puts tree

puts tree.contains(5)
puts tree.contains(2)

puts tree.delete(10)
puts tree