var user = function(name, uses, fields){
  this.Password = Password;
  this.FullName = FullName;
  this.City = City;
  this.id = 0
  this.createdAt = Date.getTime();
  this.updatedAt = Date.getTime();


  this.Save(){
    //HTTP put request to /users/:id
  }

  this.Load(){
    //HTTP GET request to users/:id
  }

  this.Update(){
    //HTTP PATCH request to users/:id
  }

  this.Delete(){
    //HTTP DELETE request to users/:id
  }
};