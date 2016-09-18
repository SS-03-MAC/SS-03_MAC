require 'optparse'

options = {}

OptionParser.new do |parser|
  parser.banner "Useage: mac-cli build [options]"
  parser.on("--no-javascript", "--no-js", "Does not update JavaScript models")
  parser.on("--no-cs", "Does not update C# models")
  parser.on("--no-api", "-- Does not update API definitions")
  parser.on("-h", "--help", "Shows this help message.") { puts parser; exit}
end.parse!
