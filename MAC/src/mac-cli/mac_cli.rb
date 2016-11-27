
# Mac CLI start
module MacCLI
  if ARGV.length.zero?
    puts 'Useage: mac-cli'
    exit
  end

  # Modules
  # TODO: Make this more rubish
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
