
# Mac CLI start
module MacCLI
  # Banner for usage. Displayed when no command are found, or if the first argument is help
  if ARGV.length.zero? or ARGV[0] == '--help' or ARGV[0] == '-h'
    puts 'Useage: mac-cli'
    puts 'init: creates the directory tree for a new MAC project'
    puts 'build: populates models in a MAC project'
    puts 'run: runs the current project'
    exit
  end

  # Modules
  # Each command has its own argument class. Details are fleshed out in their respective classes
  if ARGV[0] == 'build'
    require_relative './commands/build'
    ARGV.shift
    build = Build.new
    build.build(ARGV, './public/', './app/', './db/', './config/models/')
    exit
  elsif ARGV[0] == 'init'
    require_relative './commands/init'
    ARGV.shift
    init = Init.new
    init.init(ARGV)
    exit
  elsif ARGV[0] == 'run'
    require_relative './commands/run'
    ARGV.shift
    run = Run.new
    run.option_parser(ARGV)
    exit
  else
    puts 'Invalid command'
  end
end
