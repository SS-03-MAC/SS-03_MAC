require "test/unit"
require 'erb'
require './../Generate.rb'

class TestSQLGen  < Test::Unit::TestCase
  def basicTable
    yaml = YAML.load(File.open(path))
    @types = Generation::GenerateSQL.types
    ERB.new(File.read("../table.sql.erb")).result(yaml[0])
    assert_equal(0,1)
    assert(true)
  end
end
