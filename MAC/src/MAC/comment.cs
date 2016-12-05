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
      public MAC.Types.String FullName { get; set; }
      
    

      
      [DatabaseField("Email")]
      public Email Email { get; set; }
      
    

      
      [DatabaseField("Website")]
      public Url Website { get; set; }
      
    

      
      [DatabaseField("Body")]
      public Types.String Body { get; set; }
      
    
  }

}
