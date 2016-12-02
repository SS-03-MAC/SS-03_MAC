using System;
using Mac.Types;


[TableName("users")]
public class User : BaseModel<User> {
  public int Id { get; set; }
  

    
    [DatabaseField("Password")]
    public MAC.User.Password Password { get; set; }
    
  

    
    [DatabaseField("FullName")]
    public string FullName { get; set; }
    
  

    
    [DatabaseField("City")]
    public string City { get; set; }
    
  
}
