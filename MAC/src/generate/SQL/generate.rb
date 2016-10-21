require './../hash_generator.rb'

module Generation
  # This class alows us to generate SQL source files using an ERB template and
  # hashes we create from parsing YAML files
  class GenerateSQL
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

    def generate_table(yaml_hash)
      template_path = './table.sql.erb';
      template = File.read(template_path)
      HashGenerator.generate_from_hash(template, yaml_hash)
    end
  end
end
