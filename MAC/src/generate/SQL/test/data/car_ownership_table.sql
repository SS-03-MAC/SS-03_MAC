CREATE TABLE CarOwnerships (
Id int NOT NULL,
CONSTRAINT PK_car_ownerships_ID PRIMARY KEY CLUSTERED (Id),
  
    CarId int,
    CONSTRAINT car_ownerships_car FOREIGN KEY (CarId)
      REFERENCES Cars (Id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
  
  
    UserId int,
    CONSTRAINT car_ownerships_user FOREIGN KEY (UserId)
      REFERENCES Users (Id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
  
);
