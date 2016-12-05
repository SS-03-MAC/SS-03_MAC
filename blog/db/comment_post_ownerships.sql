CREATE TABLE comment_post_ownerships (
  Id int IDENTITY(1,1) NOT NULL,
  CONSTRAINT PK_comment_post_ownerships_ID PRIMARY KEY CLUSTERED (Id),
  
    
      PostId int,
      CONSTRAINT comment_post_ownerships_post FOREIGN KEY (PostId)
        REFERENCES post (Id)
          ON DELETE NO ACTION
          ON UPDATE NO ACTION,
    
  
    
      CommentId int,
      CONSTRAINT comment_post_ownerships_comment FOREIGN KEY (CommentId)
        REFERENCES comment (Id)
          ON DELETE NO ACTION
          ON UPDATE NO ACTION,
    
  

  CreatedAt DateTime,
  UpdatedAt DateTime
);
