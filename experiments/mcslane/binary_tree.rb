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
      when 0 then data = v #replaces old version with new one (used for updating dictionary)
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
    include Enumerable
    attr_reader :root
    attr_accessor :root

    def initialize(data=nil)
      if data.nil?
        @root = nil
      else
        @root = BinaryTreeNode.new(data)
      end
    end

    def each
      node = find_min(root)
      while node
        yield node.data
        node = successor(node)
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

    def contains(data) #returns nil if item is not in set, and the item if it is
      if root.nil?
        return nil
      end
      node = root
      while !node.nil?
        if node.data == data
          return node.data
        elsif node.data < data
          node = node.right
        else
          node = node.left
        end
      end
      return nil
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

    def successor(node)
      if node.nil?
        return nil
      end
      if node.right
        p = node.right
        while p.left
          p = p.left
        end
        return p
      else
        p = node.parent
        child = node
        while p && p.right==child
          child = p
          p = p.parent
        end
        return p
      end
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
