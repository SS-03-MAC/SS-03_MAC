CREATE TABLE subscribers (
  Id int IDENTITY(1,1) NOT NULL,
  CONSTRAINT PK_subscribers_ID PRIMARY KEY CLUSTERED (Id),
  
    
      Email nvarchar(MAX),
    
  

  CreatedAt DateTime,
  UpdatedAt DateTime
);
