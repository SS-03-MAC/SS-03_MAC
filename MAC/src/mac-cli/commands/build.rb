require 'optparse'

module MacCLI
  ##
  # Build for MacCLI
  class Build
    def build(args, js_path, cs_path, sql_path)
      opts = option_parser(args)
      unless opts['js'] == false
        build_js(js_path)
      end

      unless opts['sql'] == false
        build_sql(sql_path)
      end

      unless opts['cs'] == false
        build_cs(cs_path)
      end
    end

    def build_js(path)
      puts "doing js"
    end

    def build_cs(path)
      puts "doing cs"
    end

    def build_sql(path)
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
