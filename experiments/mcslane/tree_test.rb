require "./binary_tree"

rng = Random.new()
tree = BinarySearchTree::BinaryTree.new()

i = 0
while i < 10
  tree.insert(rng.rand(256))
  i += 1
end

tree.each do |i|
  puts i
end