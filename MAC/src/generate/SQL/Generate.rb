module SSSaaS
  class Generate
    @types = {
      'Mac.User.Password' => 'nvarchar',
      'Mac.User.Email' => 'nvarchar',
      'String' => 'nvarchar',
      'Boolean' => 'bit',
      'Currency' => 'money',
      'Date' => 'time',
      'DateTime' => 'datetime',
      'Email' => 'nvarchar',
      'Float' => 'float_t',
      'Mac.Internet.IPAddress' => 'nvarchar',
      'Integer' => 'int_t',
      'MACAddress' => 'nvarchar',
      'Mac.User.PhoneNummber' => 'nvarchar',
      'Time' => 'time',
      'Url' => 'nvarchar'
    }
  end
end
