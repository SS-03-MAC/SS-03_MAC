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

  def test_empty_dir
    path = "./data/empty_dir"
    all_parsed = Parser::parse_directory(path)
    assert_equal(all_parsed.length, 0)
  end

  def test_full_dir
    path = "./data/yaml_dir/"
    all_parsed = Parser::parse_directory(path)
    assert_equal(all_parsed.length, 2)
  end

  def test_recusive_dir
    path = "./data"
    all_parsed = Parser::parse_directory(path)
    assert_equal(all_parsed.length, 3)
    assert(all_parsed.has_key?("example_yaml.yml"))
    assert(all_parsed.has_key?("yaml_dir/teammates.yml"))
    assert(all_parsed.has_key?("yaml_dir/example_yaml.yml"))
  end

end