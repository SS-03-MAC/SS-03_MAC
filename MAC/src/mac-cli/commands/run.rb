require 'optparse'

options = {}

OptionParser.new do |parser|
  parser.banner "Useage: mac-cli run [options]"
  parser.on("-p", "--port", "Temporary port to listen on")
  parser.on("--ssl-port", "Temporary port to bind SSL on")
  parser.on("--no-ssl", "Ignores SSL bindings")
end
