require_relative '../hash_generator.rb'

module Generation

  class GenerateJavascript
    # This method takes in a hash from one of our YAML files and generates
    # a string representing a Javascript class, storing data as required in the 
    # input
    def generate_class(yaml_hash)
      cur_directory_path = File.expand_path(File.dirname(__FILE__))
      template_path = File.join(cur_directory_path, 'template.js.erb')
      template = File.read(template_path)
      HashGenerator.render_from_hash(template, yaml_hash)
    end

    # Takes in a hash and an output destination, writes the class to 
    # the given file
    def write_class(yaml_hash, ouput_path)
      result = generate_file(yaml_hash)
      File.open(output_path, 'w') do |f|
        f.write(result)
      end
    end
  end
end