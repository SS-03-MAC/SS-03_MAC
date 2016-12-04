using System;
using MAC.Types;
using MAC.Types.User;
using MAC.Types.Internet;
using MAC.Models.Attributes;
using MAC.Models.Attributes.Validations;

namespace MAC.Models {
  [TableName("post_ownerships")]
  [UrlName("post_ownerships")]
  public partial class PostOwnership : BaseModel<PostOwnership> {
    

      
      [DatabaseField("post")]
      public int PostId { get; set; }
      public virtual Post A_Post {
        get {
          return Post.Get(PostId);
        }

        set {
          PostId = (int) value.Id;
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
