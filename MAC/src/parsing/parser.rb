require "yaml"

module Parser
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
end