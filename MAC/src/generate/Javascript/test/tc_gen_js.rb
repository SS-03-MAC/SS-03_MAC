require 'test/unit'
require 'erb'
require 'yaml'
require_relative '../generate_js.rb'

# This class is for testing that that SQL generationn works properly
class TestJSGen < Test::Unit::TestCase
  include Generation

  def test_basic_class
    in_path = './data/user.yaml'
    out_path = './data/user_class.js'
    yaml = YAML.load(File.open(in_path))
    gen = GenerateJavascript.new
    gen.write_class(yaml[0], out_path)

    out_path = './data/car_class.js'
    gen.write_class(yaml[1], out_path)

    out_path = './car_ownership_class.js'
    gen.write_class(yaml[2], out_path)

    assert(true)
  end
end
