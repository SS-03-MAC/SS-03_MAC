require 'optparse'

module MacCLI
  # Init for Mac CLI. creates a directory as named and adds all nexessary subdirectories
  class Init
    def init(args)
      # get the name for the root directory
      root = args[0]

      # makes all the necesarry directories
      Dir.mkdir(root)
      # adds db directory for sql files
      Dir.mkdir(root + '/db')
      # adds directory for public facing code, including generated javascript
      Dir.mkdir(root + '/public')
      # adds application data folder, which holds generated C#
      Dir.mkdir(root + '/app')
      # adds config folder, which holds config files and model yaml
      Dir.mkdir(root + '/config')
      # subdirectory for yaml files
      Dir.mkdir(root + '/config/models')

      # TODO: add in default files
    end
  end
end
