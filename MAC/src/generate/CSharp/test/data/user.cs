using System;
using Mac.Types;

public class user : BaseModel {
  
    [DatabaseField("MAC.User.Password")]
    public MAC.User.Password Password { get; set; }
  
    [DatabaseField("string")]
    public string FullName { get; set; }
  
    [DatabaseField("string")]
    public string City { get; set; }
  
}
