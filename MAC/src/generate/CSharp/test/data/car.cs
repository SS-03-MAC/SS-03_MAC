using System;
using MAC.Types;
using MAC.Types.User;
using MAC.Types.Internet;
using MAC.Models.Attributes;
using MAC.Models.Attributes.Validations;

namespace MAC.Models {
  [TableName("cars")]
  [UrlName("cars")]
  public partial class Car : BaseModel<Car> {
    

      
      [DatabaseField("name")]
      public MAC.Types.String Name { get; set; }
      
    
  }

}
