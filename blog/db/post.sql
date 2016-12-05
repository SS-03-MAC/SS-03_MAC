CREATE TABLE posts (
  Id int NOT NULL,
  CONSTRAINT PK_posts_ID PRIMARY KEY CLUSTERED (Id),
  
    
      Title nvarchar,
    
  
    
      Body nvarchar,
    
  
    
      PublishedAt datetime,
    
  
);
