CREATE TABLE comments (
  Id int IDENTITY(1,1) NOT NULL,
  CONSTRAINT PK_comments_ID PRIMARY KEY CLUSTERED (Id),
  
    
      FullName nvarchar(MAX),
    
  
    
      Email nvarchar(MAX),
    
  
    
      Website nvarchar(MAX),
    
  
    
      Body nvarchar(MAX),
    
  

  CreatedAt DateTime,
  UpdatedAt DateTime
);
