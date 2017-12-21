CREATE TABLE auths (
  Id int IDENTITY(1,1) NOT NULL,
  CONSTRAINT PK_auths_ID PRIMARY KEY CLUSTERED (Id),
  
    
      token nvarchar(MAX),
    
  
    
      OwnerId int_t,
    
  

  CreatedAt DateTime,
  UpdatedAt DateTime
);
