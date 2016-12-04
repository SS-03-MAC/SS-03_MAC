using System;
using MAC.Types;
using MAC.Types.User;
using MAC.Types.Internet;
using MAC.Models.Attributes;
using MAC.Models.Attributes.Validations;

namespace MAC.Models {
  [TableName("car_ownerships")]
  [UrlName("car_ownerships")]
  public partial class CarOwnership : BaseModel<CarOwnership> {
    

      
      [DatabaseField("car")]
      public int CarId { get; set; }
      public virtual Car A_Car {
        get {
          return Car.Get(CarId);
        }

        set {
          CarId = (int) value.Id;
        }
      }
      
    

      
      [DatabaseField("user")]
      public int UserId { get; set; }
      public virtual User A_User {
        get {
          return User.Get(UserId);
        }

        set {
          UserId = (int) value.Id;
        }
      }
      
    
  }

}
