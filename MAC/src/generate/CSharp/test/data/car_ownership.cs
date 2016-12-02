using System;
using Mac.Types;


[TableName("car_ownerships")]
public class CarOwnership : BaseModel {
  

    
    [DatabaseField("car")]
    public int CarId { get; set; }
    public virtual Car Car {
      get {
        return Car.Get(carId);
      }

      set {
        CarId = value.Id;
      }
    }
    
  

    
    [DatabaseField("user")]
    public int UserId { get; set; }
    public virtual User User {
      get {
        return User.Get(userId);
      }

      set {
        UserId = value.Id;
      }
    }
    
  
}
