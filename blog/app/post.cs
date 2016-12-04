using System;
using Mac.Types;


[TableName("posts")]
public class post : BaseModel {
  
    [DatabaseField("nvarchar")]
    public nvarchar Title { get; set; }
  
    [DatabaseField("nvarchar")]
    public nvarchar Body { get; set; }
  
    [DatabaseField("datetime")]
    public datetime PublishedAt { get; set; }
  
}
