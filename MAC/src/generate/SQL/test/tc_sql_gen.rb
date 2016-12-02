require 'test/unit'
require 'erb'
require 'yaml'
require_relative '../generate_sql.rb'

# This class is for testing that that SQL generationn works properly
class TestSQLGen < Test::Unit::TestCase
  include Generation

  def test_basic_table
    in_path = './data/user.yaml'
    out_path = './data/user_table.sql'
    yaml = YAML.load(File.open(in_path))
    gen = GenerateSQL.new
    gen.write_table(yaml[0], out_path)

    out_path = './data/car_table.sql'
    yaml = YAML.load(File.open(in_path))
    gen = GenerateSQL.new
    gen.write_table(yaml[1], out_path)

    out_path = './data/car_ownership_table.sql'
    yaml = YAML.load(File.open(in_path))
    gen = GenerateSQL.new
    gen.write_table(yaml[2], out_path)
    
    assert(true)
  end
end
