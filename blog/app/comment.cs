using System;
using Mac.Types;


[TableName("comments")]
public class comment : BaseModel {
  
    [DatabaseField("nvarchar")]
    public nvarchar FullName { get; set; }
  
    [DatabaseField("nvarchar")]
    public nvarchar Email { get; set; }
  
    [DatabaseField("nvarchar")]
    public nvarchar Website { get; set; }
  
    [DatabaseField("nvarchar")]
    public nvarchar Body { get; set; }
  
}
