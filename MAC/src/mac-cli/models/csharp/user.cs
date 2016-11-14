using System;
using Mac.Types;


[TableName("users")]
public class user : BaseModel {
  
    [DatabaseField("nvarchar")]
    public nvarchar Password { get; set; }
  
    [DatabaseField("nvarchar")]
    public nvarchar FullName { get; set; }
  
    [DatabaseField("nvarchar")]
    public nvarchar City { get; set; }
  
}
