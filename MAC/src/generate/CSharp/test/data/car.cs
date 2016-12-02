using System;
using Mac.Types;


[TableName("cars")]
public class Car : BaseModel<Car> {
  public int Id { get; set; }
  

    
    [DatabaseField("name")]
    public string Name { get; set; }
    
  
}
