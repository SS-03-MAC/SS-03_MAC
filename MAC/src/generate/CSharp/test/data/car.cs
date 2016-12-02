using System;
using Mac.Types;


[TableName("cars")]
public class Car : BaseModel {
  

    
    [DatabaseField("name")]
    public string Name { get; set; }
    
  
}
