##
# Mac CLI start
module MacCLI
  if ARGV.length.zero?
    puts 'Useage: mac-cli'
    exit
  end

  # Modules
  # TODO: Make this more rubish
  if ARGV[0] == 'build'
    require './commands/build'
    ARGV.shift
    build = Build.new
    build.build(ARGV, './models/js/', './models/csharp/', './models/sql/', './yaml')
    exit
  elsif ARGV[0] == 'init'
    require './commands/init'
    ARGV.shift
    init = Init.new
    init.option_parser(ARGV)
    exit
  elsif ARGV[0] == 'run'
    require './commands/run'
    ARGV.shift
    run = Run.new
    run.option_parser(ARGV)
    exit
  else
    puts 'Invalid command'
  end
end
