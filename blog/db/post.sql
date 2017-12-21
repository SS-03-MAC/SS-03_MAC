CREATE TABLE posts (
  Id int IDENTITY(1,1) NOT NULL,
  CONSTRAINT PK_posts_ID PRIMARY KEY CLUSTERED (Id),
  
    
      Title nvarchar(MAX),
    
  
    
      Body nvarchar(MAX),
    
  
    
      PublishedAt datetime,
    
  

  CreatedAt DateTime,
  UpdatedAt DateTime
);
