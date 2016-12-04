CREATE TABLE post_ownerships (
  Id int NOT NULL,
  CONSTRAINT PK_post_ownerships_ID PRIMARY KEY CLUSTERED (Id)
  
    
      PostId int,
      CONSTRAINT post_ownerships_post FOREIGN KEY (PostId)
        REFERENCES post (Id)
          ON DELETE CASCADE
          ON UPDATE CASCADE
    
  
    
      UserId int,
      CONSTRAINT post_ownerships_user FOREIGN KEY (UserId)
        REFERENCES user (Id)
          ON DELETE CASCADE
          ON UPDATE CASCADE
    
  
);
