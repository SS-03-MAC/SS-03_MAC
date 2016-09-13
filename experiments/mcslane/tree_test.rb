require "./binary_tree"

tree = BinarySearchTree::BinaryTree.new()
tree.insert(10)
tree.insert(15)
tree.insert(5)
puts tree

puts tree.contains(5)
puts tree.contains(2)

puts tree.delete(10)
puts tree