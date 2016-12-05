CREATE TABLE post_ownerships (
  Id int NOT NULL,
  CONSTRAINT PK_post_ownerships_ID PRIMARY KEY CLUSTERED (Id),
  
    
      PostId int,
      CONSTRAINT post_ownerships_post FOREIGN KEY (PostId)
        REFERENCES posts (Id),
    
  
    
      UserId int,
      CONSTRAINT post_ownerships_user FOREIGN KEY (UserId)
        REFERENCES Users (Id)
    
  
);
