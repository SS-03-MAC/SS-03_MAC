require_relative '../hash_generator.rb'
require 'active_support/inflector'

module Generation
  # This class alows us to generate SQL source files using an ERB template and
  # hashes we create from parsing YAML files
  class GenerateSQL
    attr_reader :types

    def initialize
      @types = {
        'MAC.User.Password' => 'nvarchar(MAX)',
        'MAC.User.Email' => 'nvarchar(MAX)',
        'MAC.Types.String' => 'nvarchar(MAX)',
        'Boolean' => 'bit',
        'Currency' => 'money',
        'Date' => 'time',
        'DateTime' => 'datetime',
        'Email' => 'nvarchar(MAX)',
        'Float' => 'float_t',
        'MAC.Internet.IPAddress' => 'nvarchar(MAX)',
        'Integer' => 'int_t',
        'MAC.Internet.MACAddress' => 'nvarchar(MAX)',
        'MAC.User.PhoneNummber' => 'nvarchar(MAX)',
        'Time' => 'time',
        'Url' => 'nvarchar(MAX)'
      }
    end

    # This method takes in a hash from one of our YAML files and generates
    # a string representing a SQL table, storing data as required in the
    # input
    def generate_table(yaml_hash)
      cur_directory_path = File.expand_path(File.dirname(__FILE__))
      template_path = File.join(cur_directory_path, 'table.sql.erb')
      template = File.read(template_path)
      composed_hash = compose_hash(yaml_hash)
      HashGenerator.render_from_hash(template, composed_hash)
    end

    # This method takes a hash and for everything in the "fields" catagory,
    # will go through and change the type of each field from a MAC defined type
    # into a SQL type
    def compose_hash(input_hash)
      output_hash = input_hash
      output_hash['table_name'] = ActiveSupport::Inflector.tableize(input_hash['name'])
      output_hash['fields'].each do |field|
        field['type'] = @types[field['type']]
      end
      output_hash
    end

    # Takes in a hash and an output destination, writes the table to
    # the given file
    def write_table(yaml_hash, output_path)
      result = generate_table(yaml_hash)
      File.open(output_path, 'w') do |f|
        f.write(result)
      end
    end
  end
end
