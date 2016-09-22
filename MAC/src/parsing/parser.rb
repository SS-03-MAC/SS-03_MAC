require 'yaml'

# This module allows for us to recusively check thorugh a directory and
# all its children, parsing all documents that are valid YAML (includeing JSON)
module Parser
  # checks if a file could be YAML and parses it
  def parse_file(path)
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

  # finds all YAML files in a directory and parses them into a hash of Objects,
  # keys are file names, values are parsed YAML objects.
  # can and should initially be called with no second argument
  def parse_directory(base_dir, child = '')
    result = {}

    base_dir += '/' unless base_dir[-1] == '/'
    child += '/' unless child == '' || child[-1] == '/'

    dir_path = base_dir + child
    Dir.foreach(dir_path) do |item|
      # adds the proper file location to item
      full_name = dir_path + item
      pretty_name = child + item
      # skips any other directories found, including '.' and '..'
      next if item == '.' || item == '..'
      if File.directory?(full_name)
        # recursively calls parse_directory, adding more YAML to our hash
        child_hash = parse_directory(base_dir, pretty_name)
        result = result.merge(child_hash)
      else
        # tries to parse file, don't include if nil is returned
        parsed_yaml = parse_file(full_name)
        presult[pretty_name] = parsed_yaml unless parsed_yaml.nil?
      end
    end

    result
  end
end
