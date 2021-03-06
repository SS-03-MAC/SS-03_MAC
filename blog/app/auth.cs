using System;
using MAC.Types;
using MAC.Types.User;
using MAC.Types.Internet;
using MAC.Models.Attributes;
using MAC.Models.Attributes.Validations;

namespace MAC.Models {
  [TableName("auths")]
  [UrlName("auths")]
  public partial class Auth : BaseModel<Auth> {
    

      
      [DatabaseField("token")]
      public nvarchar(MAX) Token { get; set; }
      
    

      
      [DatabaseField("OwnerId")]
      public int_t OwnerId { get; set; }
      
    
  }

}
