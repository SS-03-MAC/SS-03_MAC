require 'optparse'

module MacCLI
  ##
  # Build for MacCLI
  class Build

    def option_parser(args)
      opt_parser = OptionParser.new do |opts|
        opts.banner = 'Useage: mac-cli build [options]'
        opts.on('--no-javascript', '--no-js', 'Does not update JavaScript models')
        opts.on('--no-sql', 'Does not update SQL table')
        opts.on('--no-cs', 'Does not update C# models')
        opts.on('--no-api', 'Does not update API definitions')
        opts.on('-h', '--help', 'Shows this help message.') do |v|
          puts opt_parser 
          exit
        end
      end

      opt_parser.parse!(args)
    end
  end
end
