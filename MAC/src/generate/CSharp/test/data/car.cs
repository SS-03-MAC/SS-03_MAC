using System;
using Mac.Types;


[TableName("cars")]
public class Car : BaseModel<Car> {
  

    
    [DatabaseField("name")]
    public string Name { get; set; }
    
  
}
