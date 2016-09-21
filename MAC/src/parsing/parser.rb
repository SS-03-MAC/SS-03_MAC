require "yaml"

module Parser
  def parse_file path
    parsed = begin
      YAML.load(File.open(path))
    rescue ArgumentError => e
      puts "Could nor parse YAML: #{e.message}" 
    end

    return parsed
  end
end