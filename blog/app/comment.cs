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
      public nvarchar(MAX) FullName { get; set; }
      
    

      
      [DatabaseField("Email")]
      public nvarchar(MAX) Email { get; set; }
      
    

      
      [DatabaseField("Website")]
      public nvarchar(MAX) Website { get; set; }
      
    

      
      [DatabaseField("Body")]
      public nvarchar(MAX) Body { get; set; }
      
    
  }

}
