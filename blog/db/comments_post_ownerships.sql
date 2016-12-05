CREATE TABLE comments_post_ownerships (
  Id int IDENTITY(1,1) NOT NULL,
  CONSTRAINT PK_comments_post_ownerships_ID PRIMARY KEY CLUSTERED (Id),
  
    
      PostId int,
      CONSTRAINT comments_post_ownerships_post FOREIGN KEY (PostId)
        REFERENCES post (Id)
          ON DELETE NO ACTION
          ON UPDATE NO ACTION,
    
  
    
      CommentsId int,
      CONSTRAINT comments_post_ownerships_comments FOREIGN KEY (CommentsId)
        REFERENCES comments (Id)
          ON DELETE NO ACTION
          ON UPDATE NO ACTION,
    
  

  CreatedAt DateTime,
  UpdatedAt DateTime
);
