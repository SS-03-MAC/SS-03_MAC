require 'test/unit'
require 'erb'
require './../Generate.rb'

# This class is for testing that that SQL generationn works properly
class TestSQLGen < Test::Unit::TestCase
  def basic_table
    yaml = YAML.load(File.open(path))
    @types = Generation::GenerateSQL.types
    ERB.new(File.read('../table.sql.erb')).result(yaml[0])
    assert_equal(0, 1)
    assert(true)
  end
end
