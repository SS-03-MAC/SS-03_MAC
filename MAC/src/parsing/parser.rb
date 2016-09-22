require "yaml"

module Parser

  #checks if a file could be YAML and parses it
  def parse_file path
    #checks if the file is valid YAML (includes JSON), if not, returns nil
    accepted_formats = [".yml", ".yaml", ".json"]
    ext = File.extname(path)
    if !accepted_formats.include? ext
      return nil
    end

    #tries to parse YAML, if something goes wrong, displays error, returns nil 
    parsed = begin
      YAML.load(File.open(path))
    rescue ArgumentError => e
      puts "Could not parse YAML from file #{path}" 
      nil
    end
    return parsed
  end

  #finds all YAML files in a directory and parses them into a hash of Objects,
  #keys are file names, values are parsed YAML objects.
  #can and should initially be called with no second argument
  def parse_directory base_dir, child=""
    result = {}

    if base_dir[-1] != '/'
      base_dir += '/'
    end
    if child != "" and child[-1] != '/'
      child += '/'
    end
    dir_path = base_dir+child
    Dir.foreach(dir_path) do |item|
      #adds the proper file location to item
      full_name = dir_path + item
      pretty_name = child + item
      #skips any other directories found, including '.' and '..'
      next if item == '.' or item == '..'
      if File.directory?(full_name)
        #recursively calls parse_directory, adding more YAML to our hash
        child_hash = parse_directory(base_dir, pretty_name)
        result = result.merge(child_hash)
      else
        #tries to parse file, if parse_file(item) returns nil, don't include value
        parsed_yaml = parse_file(full_name)
        if !parsed_yaml.nil?
          result[pretty_name] = parsed_yaml
        end
      end
    end

    return result
  end
end