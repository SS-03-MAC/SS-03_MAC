require "./../parser.rb"
require "test/unit"

include Parser

class TestParser < Test::Unit::TestCase

  def test_single_success
    expected = [{"name"=>"Billy Bob", "state"=>"Arkansas", "age"=>38}]
    path = "./data/example_yaml.yml"
    parsed = Parser::parse_file(path)
    assert_equal(parsed, expected)
  end

  def test_single_failure
    path = "./data/lorem_ipsum.txt"
    parsed = Parser::parse_file(path)
    assert_nil(parsed)
  end

end