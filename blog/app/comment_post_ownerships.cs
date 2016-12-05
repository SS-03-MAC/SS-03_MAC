using System;
using MAC.Types;
using MAC.Types.User;
using MAC.Types.Internet;
using MAC.Models.Attributes;
using MAC.Models.Attributes.Validations;

namespace MAC.Models {
  [TableName("comment_post_ownerships")]
  [UrlName("comment_post_ownerships")]
  public partial class CommentPostOwnerships : BaseModel<CommentPostOwnerships> {
    

      
      [DatabaseField("post")]
      public Integer PostId { get; set; }
      public virtual Post A_Post {
        get {
          return Post.Get(PostId);
        }

        set {
          PostId = (int) value.Id;
        }
      }
      
    

      
      [DatabaseField("comment")]
      public Integer CommentId { get; set; }
      public virtual Comment A_Comment {
        get {
          return Comment.Get(CommentId);
        }

        set {
          CommentId = (int) value.Id;
        }
      }
      
    
  }

}
