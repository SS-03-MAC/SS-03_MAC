CREATE TABLE comments_post_ownerships (
  Id int NOT NULL,
  CONSTRAINT PK_comments_post_ownerships_ID PRIMARY KEY CLUSTERED (Id)
  
    
      PostId int,
      CONSTRAINT comments_post_ownerships_post FOREIGN KEY (PostId)
        REFERENCES post (Id)
          ON DELETE CASCADE
          ON UPDATE CASCADE
    
  
    
      CommentsId int,
      CONSTRAINT comments_post_ownerships_comments FOREIGN KEY (CommentsId)
        REFERENCES comments (Id)
          ON DELETE CASCADE
          ON UPDATE CASCADE
    
  
);
