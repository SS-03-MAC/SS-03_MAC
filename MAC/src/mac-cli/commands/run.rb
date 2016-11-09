require 'optparse'

module MacCLI
  ##
  # Mac CLI Run
  class Run
    OptionParser.new do |parser|
      parser.banner = 'Useage: mac-cli run [options]'
      parser.on('-p', '--port', 'Temporary port to listen on')
      parser.on('--ssl-port', 'Temporary port to bind SSL on')
      parser.on('--no-ssl', 'Ignores SSL bindings')
      parser.on('-h', '--help', 'Shows this help message.') do
        puts parser
        exit
      end
    end.parse!
  end
end
