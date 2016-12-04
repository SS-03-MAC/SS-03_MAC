using System;
using MAC.Types;
using MAC.Types.User;
using MAC.Types.Internet;
using MAC.Models.Attributes;
using MAC.Models.Attributes.Validations;

namespace MAC.Models {
  [TableName("comments")]
  [UrlName("comments")]
  public partial class Comment : BaseModel<Comment> {
    

      
      [DatabaseField("FullName")]
      public nvarchar FullName { get; set; }
      
    

      
      [DatabaseField("Email")]
      public nvarchar Email { get; set; }
      
    

      
      [DatabaseField("Website")]
      public nvarchar Website { get; set; }
      
    

      
      [DatabaseField("Body")]
      public nvarchar Body { get; set; }
      
    
  }

}
