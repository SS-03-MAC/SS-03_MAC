require 'test/unit'
require 'erb'
require './../Generate'

class TestSQLGen < Test::Unit::TestCase
  def basicTable
    ymal = YAML.load(File.open(path))


  end
end
