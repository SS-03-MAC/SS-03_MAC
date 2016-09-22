require 'optparse'

module MacCLI
  ##
  # Mac CLI Run
  class Init
    def option_parser
      OptionParser.new do |parser|
        parser.banner = 'Useage: mac-cli init [options]'
      end.parse!
    end
  end
end
