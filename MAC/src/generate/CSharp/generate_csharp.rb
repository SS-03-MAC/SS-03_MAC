require_relative '../hash_generator.rb'

module Generation
  # This class alows us to generate C# source files using an ERB template and
  # hashes we create from parsing YAML files
  class GenerateCSharp
    attr_reader :types

    def initialize
    end

    # This method takes in a hash from one of our YAML files and generates
    # a string representing a CS Model, storing data as required in the
    # input
    def generate_model(yaml_hash)
      cur_directory_path = File.expand_path(File.dirname(__FILE__))
      template_path = File.join(cur_directory_path, 'template.cs.erb')
      template = File.read(template_path)
      composed_hash = compose_hash(yaml_hash)
      HashGenerator.render_from_hash(template, composed_hash)
    end

    # This method takes a hash and for everything in the "fields" catagory,
    # will go through and change the type of each field from a MAC defined type
    # into a SQL type
    def compose_hash(input_hash)
      output_hash = input_hash
      output_hash
    end

    # Takes in a hash and an output destination, writes the table to
    # the given file
    def write_model(yaml_hash, output_path)
      result = generate_model(yaml_hash)
      File.open(output_path, 'w') do |f|
        f.write(result)
      end
    end
  end
end
