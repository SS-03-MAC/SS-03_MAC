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
  #keys are file names, values are parsed YAML objects
  def parse_directory dir_path
    result = {}

    Dir.foreach(dir_path) do |item|
      #skips any other directories found, including '.' and '..'
      next if item == '.' or item == '..'
      if File.directory?(item)
        #recursively calls parse_directory, adding more YAML to our hash
      else
        #tries to parse file, if parse_file(item) returns nil, don't include value
      end
    end
  end
end