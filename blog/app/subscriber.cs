using System;
using MAC.Types;
using MAC.Types.User;
using MAC.Types.Internet;
using MAC.Models.Attributes;
using MAC.Models.Attributes.Validations;

namespace MAC.Models {
  [TableName("subscribers")]
  [UrlName("subscribers")]
  public partial class Subscriber : BaseModel<Subscriber> {
    

      
      [DatabaseField("Email")]
      public nvarchar Email { get; set; }
      
    
  }

}
