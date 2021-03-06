require 'yaml'

# This module allows for us to recusively check thorugh a directory and
# all its chlidren, parsing all documents that are valid YAML (includeing JSON)
module Parser
  # checks if a file could be YAML and parses it
  def self.parse_file(path)
    # checks if the file is valid YAML (includes JSON), if not, returns nil
    accepted_formats = ['.yml', '.yaml', '.json']
    ext = File.extname(path)
    return nil unless accepted_formats.include?(ext)

    # tries to parse YAML, if something goes wrong, displays error, returns nil
    begin
      YAML.load(File.open(path))
    rescue ArgumentError
      puts 'Could not parse YAML from file #{path}'
      nil
    end
  end

  def self.parse_dir(path)
    path += '/' unless path[-1] == '/'
    parse_dir_recursive(path, '')
  end

  def self.add_dir_to_hash(base, path, hash)
    cur_dir_hash = parse_dir_recursive(base, path)
    hash.merge(cur_dir_hash)
  end

  def self.add_file_to_hash(base, path, hash)
    parsed_yaml = parse_file(base + path)
    hash[path] = parsed_yaml unless parsed_yaml.nil?
    hash
  end

  # finds all YAML files in a directory and parses them into a hash of Objects,
  # keys are file names, values are parsed YAML objects.
  # can and should initially be called with no second argument
  def self.parse_dir_recursive(base_dir, cur_dir = '')
    result = {}

    Dir.foreach(base_dir + cur_dir) do |item|
      # skips any other directories found, including '.' and '..'
      next if item == '.' || item == '..'
      if File.directory?(base_dir + cur_dir + item)
        # recursively calls parse_directory, adding more YAML to our hash
        result = add_dir_to_hash(base_dir, cur_dir + item + '/', result)
      else
        # tries to parse file, don't include if nil is returned
        result = add_file_to_hash(base_dir, cur_dir + item, result)
      end
    end

    result
  end
end
