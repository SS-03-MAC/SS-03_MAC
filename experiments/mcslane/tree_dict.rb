require "binary_tree"

module TreeDict
  class KeyValuePair
    include Comparable
    attr_reader :key, :value
    attr_accessor :key

    def initialize(key, value)
      @key = key
      @value = value
    end

    def <=>(other)
      key <=> other.key
  end

  class Dictionary
    attr_reader :set

    def initialize
      @set = BinarySearchTree::BinaryTree.new()
    end

    def add(key, value)
      set.add(KeyValuePair.new(key, value))
    end

    def contains(key)
      return set.contains(KeyValuePair.new(key, nil))
    end

    def remove(key)
      return set.remove(KeyValuePair.new(key, nil))
    end

    def get(key)
      pair = set.contains(KeyValuePair.new(key, nil))
      if pair.nil?
        return nil
      else
        return pair.value
      end
    end
  end
end