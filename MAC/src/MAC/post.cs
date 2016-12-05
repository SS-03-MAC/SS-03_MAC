using System;
using MAC.Types;
using MAC.Types.User;
using MAC.Types.Internet;
using MAC.Models.Attributes;
using MAC.Models.Attributes.Validations;

namespace MAC.Models {
  [TableName("posts")]
  [UrlName("posts")]
  public partial class Post : BaseModel<Post> {
    

      
      [DatabaseField("Title")]
      public Types.String Title { get; set; }
      
    

      
      [DatabaseField("Body")]
      public Types.String Body { get; set; }
          

      
      [DatabaseField("PublishedAt")]
      public Types.DateTime PublishedAt { get; set; }
      
    
  }

}
