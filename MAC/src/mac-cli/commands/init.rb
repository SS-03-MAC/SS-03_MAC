require 'optparse'

module MacCLI
  ##
  # Mac CLI Run
  class Init
    def init(args)
      # get the name for the root directory
      root = args[0]

      # makes all the necesarry directories
      Dir.mkdir(root)
      Dir.mkdir(root + '/db')
      Dir.mkdir(root + '/public')
      Dir.mkdir(root + '/app')
      Dir.mkdir(root + '/config')
      Dir.mkdir(root + '/config/models')

      # add in default files
    end
  end
end
