require_relative '../hash_generator.rb'

module Generation
  # This class alows us to generate javascript files for our framework
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
    def write_class(yaml_hash, output_path)
      refined_hash = add_fields_str(yaml_hash)
      result = generate_class(refined_hash)
      File.open(output_path, 'w') do |f|
        f.write(result)
      end
    end

    # creates a string of a comma seperated list of values in the field hash
    # used for constructor of javascript class
    def add_fields_str(in_hash)
      fields_str = ''
      in_hash['fields'].each do |type|
        fields_str += type['name'] + ', '
      end
      out_hash = in_hash
      out_hash['fields_str'] = fields_str[0..-3]
      out_hash
    end
  end
end
