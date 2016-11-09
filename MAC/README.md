# mac-cli
## Overview

mac-cli is the developer interface to the MAC framework. This allows developers
to automatically generate the CRUD functionality of sites from basic
descriptions of the models.

## Setup
### BSD, Linux, Mac, Solaris, Windows

Please make sure Ruby 2.0 or later is installed. Please refer to the Ruby
[website](https://www.ruby-lang.org/en/) for documentation on how to install
Ruby for your operating system.

## Usage
### Help

When invoked with no arguments (or some variation on "help"), mac-cli output
usage text:

    mac-cli --help
        mac-cli v0.1.0
        Copyright (C) 2016 mac-cli Authors
        Licensed under the MIT License

        Usage:
        init         -- Create a new project in the current directory
        build        -- Builds the project
            --no-js      -- Does not update JavaScript models
            --no-cs      -- Does not update C# models
            --no-api     -- Does not update API definitions
        run          -- Launch the project
            --port       -- Temporary port to listen on
            --ssl-port   -- Temporary port to bind SSL on
            --no-ssl     -- Ignores SSL bindings

### Initialization

To set up a new project:

    proj="name_of_project"
    mkdir $proj
    cd $proj
    mac-cli init $proj

This will create a mac/ folder for FMDs and a build/ folder for generated code.

### Building

After defining the models:

    mac-cli build

This will update the generate code. See help for available options.

### Running

To run the web server:

    mac-cli run

This will start the server against the current code base.


Screen sketch: By Alex Scheel
Screen name: mac-cli usage
