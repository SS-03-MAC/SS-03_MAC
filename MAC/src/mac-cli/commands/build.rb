require 'optparse'

module MacCLI
  ##
  # Build for MacCLI
  class Build
    def option_parser
      OptionParser.new do |parser|
        parser.banner = 'Useage: mac-cli build [options]'
        parser.on('--no-javascript', '--no-js', 'Does not update
                                                      JavaScript models')
        parser.on('--no-cs', 'Does not update C# models')
        parser.on('--no-api', 'Does not update API definitions')
        parser.on('-h', '--help', 'Shows this help message.') { run_help }
      end.parse!
    end

    

    private

    def run_help
      puts parser
      exit
    end
  end
end
