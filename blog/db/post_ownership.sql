CREATE TABLE post_ownerships (
  Id int IDENTITY(1,1) NOT NULL,
  CONSTRAINT PK_post_ownerships_ID PRIMARY KEY CLUSTERED (Id),
  
    
      PostId int,
      CONSTRAINT post_ownerships_post FOREIGN KEY (PostId)
        REFERENCES post (Id)
          ON DELETE NO ACTION
          ON UPDATE NO ACTION,
    
  
    
      UserId int,
      CONSTRAINT post_ownerships_user FOREIGN KEY (UserId)
        REFERENCES user (Id)
          ON DELETE NO ACTION
          ON UPDATE NO ACTION,
    
  

  CreatedAt DateTime,
  UpdatedAt DateTime
);
