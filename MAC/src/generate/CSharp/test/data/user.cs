using System;
using MAC.Types;
using MAC.Types.User;
using MAC.Types.Internet;
using MAC.Models.Attributes;
using MAC.Models.Attributes.Validations;

namespace MAC.Models {
  [TableName("users")]
  [UrlName("users")]
  public partial class User : BaseModel<User> {
    

      
      [DatabaseField("Password")]
      public MAC.User.Password Password { get; set; }
      
    

      
      [DatabaseField("FullName")]
      public MAC.Types.String FullName { get; set; }
      
    

      
      [DatabaseField("City")]
      public MAC.Types.String City { get; set; }
      
    
  }

}
