require 'test/unit'
require 'erb'
require 'yaml'
require_relative '../generate_csharp.rb'

# This class is for testing that that SQL generationn works properly
class TestCSGen < Test::Unit::TestCase
  include Generation

  def test_basic_table
    in_path = './data/user.yaml'
    out_path = './data/user.cs'
    yaml = YAML.load(File.open(in_path))
    gen = GenerateCSharp.new
    gen.write_model(yaml[0], out_path)
    assert(true)
  end
end
