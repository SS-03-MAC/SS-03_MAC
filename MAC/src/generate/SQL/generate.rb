require './../hash_generator.rb'

module Generation
  # This class alows us to generate SQL source files using an ERB template and
  # hashes we create from parsing YAML files
  class GenerateSQL
    attr_reader :types

    def initialize()
      @types = {
        'MAC.User.Password' => 'nvarchar',
        'MAC.User.Email' => 'nvarchar',
        'string' => 'nvarchar',
        'Boolean' => 'bit',
        'Currency' => 'money',
        'Date' => 'time',
        'DateTime' => 'datetime',
        'Email' => 'nvarchar',
        'Float' => 'float_t',
        'MAC.Internet.IPAddress' => 'nvarchar',
        'Integer' => 'int_t',
        'MAC.Internet.MACAddress' => 'nvarchar',
        'MAC.User.PhoneNummber' => 'nvarchar',
        'Time' => 'time',
        'Url' => 'nvarchar'
      }
    end

    def generate_table(yaml_hash)
      template_path = './table.sql.erb';
      template = File.read(template_path)
      composed_hash = compose_hash(yaml_hash)
      HashGenerator.render_from_hash(template, composed_hash)
    end

    def compose_hash(input_hash)
      output_hash = input_hash
      output_hash['fields'].each do |field|
        field['type'] = @types[field['type']]
      end
      output_hash
    end
  end
end
