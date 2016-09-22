require 'yaml'

path = './../../MAC/src/parsing/testing/data/example_yaml.yml'
parsed = YAML.load(File.open(path))
puts parsed