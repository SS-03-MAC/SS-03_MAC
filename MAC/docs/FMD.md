# Framework Model Definitions (FMD)
## Overview

Framework Model Definitions (FMDs) are created by the developer to describe the
various models required of the web application. Each model can have multiple
attributes and inherit from various built-in Framework Model Classes (FMCs).
These built-in FMCs include common classes like users and locations, and
include methods to validate specific input.

The design language for the FMDs is YAML (YAML Ain't Markup Language): this
allows for a clean design focused on the contents of the model and not the
syntax.

## Model Contents

There MUST be at least one base key and MAY be more than one base key in the
model definition file. Base elements are named according to the desired name of
the class. Example:

    user:

A base element MAY contain a "using" key which has an array of namespaced FMCs
used by the model. Example:

    user:
      using:
        - MAC.user
        - MAC.location

A base element MUST contain a "fields" key which contains an array of model
fields. Each field MUST contain a "name" key; this name MUST contain only
alphanumeric characters. Each field MUST contain a "type" key; allowed values
are "string", "int", "float", "bool", and any other type defined in an FMC.

Each field MAY have a "validations" key. The validations MAY include a "regex"
field; this defines a regular expression to be used when validating the input.
The validations MAY include a "required" field; this defaults to false except if
overridden by a complex FMC type.

Each field MAY contain a "acl". The acl MUST contain a "read" key; this defines
an array of allowed groups to read the field. The acl MUST contain a "write"
key; this defines an array of allowed groups to write values to the field.
Example:

    user:
      uses:
        - MAC.user
        - MAC.location
      fields:
        -
          name: FullName
          type: string
          validations:
            required: true
          acl:
            read: MAC.self, admin, MAC.signed, MAC.Public
            write: MAC.self, admin


Screen sketch: By Alex Scheel
Screen name: FMD definition
