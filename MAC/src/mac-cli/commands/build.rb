require 'optparse'
require_relative './../../generate/Javascript/generate_js.rb'
require_relative './../../generate/SQL/generate_sql.rb'
require_relative './../../generate/CSharp/generate_csharp.rb'
require_relative './../../parsing/parser.rb'

module MacCLI
  ##
  # Build for MacCLI
  class Build
    include Generation
    include Parser
    def build(args, js_path, cs_path, sql_path, yml_path)
      opts = option_parser(args)
      model_hash = Parser.parse_dir(yml_path)
      unless opts['js'] == false
        build_js(js_path, model_hash)
      end

      unless opts['sql'] == false
        build_sql(sql_path, model_hash)
      end

      unless opts['cs'] == false
        build_cs(cs_path, model_hash)
      end
    end

    def build_js(path, models)
      gen = GenerateJavascript.new
      models.each_value do |type_list|
        type_list.each do |type|
          model_name = type['name']
          gen.write_class(type, path + model_name + '.js')
        end
      end
    end

    def build_cs(path, models)
      puts "doing cs"
    end

    def build_sql(path, models)
      puts "doing SQL"
    end
    
    def option_parser(args)
      flags = {}
      opt_parser = OptionParser.new do |opts|
        opts.banner = 'Useage: mac-cli build [options]'
        opts.on('--no-javascript', '--no-js', 'Does not update JavaScript models') do |v|
          flags['js'] = false
        end
        opts.on('--no-sql', 'Does not update SQL table') do |v|
          flags['sql'] = false
        end
        opts.on('--no-cs', 'Does not update C# models') do |v|
          flags['js'] = false
        end
        opts.on('--no-api', 'Does not update API definitions')
        opts.on('-h', '--help', 'Shows this help message.') do |v|
          puts opt_parser 
          exit
        end
      end

      opt_parser.parse!(args)
      flags
    end
  end
end
