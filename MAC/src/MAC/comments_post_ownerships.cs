using System;
using MAC.Types;
using MAC.Types.User;
using MAC.Types.Internet;
using MAC.Models.Attributes;
using MAC.Models.Attributes.Validations;

namespace MAC.Models {
  [TableName("comments_post_ownerships")]
  [UrlName("comments_post_ownerships")]
  public partial class CommentsPostOwnerships : BaseModel<CommentsPostOwnerships> {
    

      
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
      
    

      
      [DatabaseField("comments")]
      public int CommentsId { get; set; }
      public virtual Comment A_Comments {
        get {
          return Comment.Get(CommentsId);
        }

        set {
          CommentsId = (int) value.Id;
        }
      }
      
    
  }

}
