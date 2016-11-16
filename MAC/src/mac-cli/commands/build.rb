require 'optparse'
require_relative './../../generate/Javascript/generate_js.rb'
require_relative './../../generate/SQL/generate_sql.rb'
require_relative './../../generate/CSharp/generate_csharp.rb'
require_relative './../../parsing/parser.rb'

module MacCLI
  # Build for MacCLI. Generates all models based off of the yaml
  # provided. has options for not doing certain languages.
  class Build
    include Generation
    include Parser

    # builds the things using provieed arguments and paths for things to go to
    def build(args, js_path, cs_path, sql_path, yml_path)
      opts = option_parser(args)
      model_hash = Parser.parse_dir(yml_path)

      build_js(js_path, model_hash) unless opts['js'] == false

      build_sql(sql_path, model_hash) unless opts['sql'] == false

      build_cs(cs_path, model_hash) unless opts['cs'] == false
    end

    # generates the JavaScript frontend endpoints for the provided models
    def build_js(path, models)
      gen = GenerateJavascript.new
      models.each_value do |type_list|
        type_list.each do |type|
          model_name = type['name']
          gen.write_class(type, path + model_name + '.js')
        end
      end
    end

    # genrates the C# backend endpoint for the provided models
    def build_cs(path, models)
      gen = GenerateCSharp.new
      models.each_value do |type_list|
        type_list.each do |type|
          model_name = type['name']
          gen.write_model(type, path + model_name + '.cs')
        end
      end
    end

    # generates the sql files for the provided models
    def build_sql(path, models)
      gen = GenerateSQL.new
      models.each_value do |type_list|
        type_list.each do |type|
          model_name = type['name']
          gen.write_table(type, path + model_name + '.sql')
        end
      end
    end

    # parses options. currently supports options for excluding javascript
    # excluding C#, excluding SQL, and shoing help
    def option_parser(args)
      flags = {}
      opt_parser = OptionParser.new do |opts|
        opts.banner = 'Useage: mac-cli build [options]'
        opts.on('--no-javascript', '--no-js', 'Does not update JavaScript models') do
          flags['js'] = false
        end
        opts.on('--no-sql', 'Does not update SQL table') do
          flags['sql'] = false
        end
        opts.on('--no-cs', 'Does not update C# models') do
          flags['js'] = false
        end
        opts.on('-h', '--help', 'Shows this help message.') do
          puts opt_parser
          exit
        end
      end

      opt_parser.parse!(args)
      flags
    end
  end
end
